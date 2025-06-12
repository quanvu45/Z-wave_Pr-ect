/**
 * Z-Wave Certified Application Power Strip
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "MfgTokens.h"
#include "DebugPrintConfig.h"
//#define DEBUGPRINT
#include "DebugPrint.h"
#include "AppTimer.h"
#include "ZW_system_startup_api.h"
#include "CC_BinarySwitch.h"
#include "CC_MultilevelSwitch_Support.h"
#include "CC_Notification.h"
#include "cc_notification_config_api.h"
#include "ZAF_Common_helper.h"
#include "ZAF_Common_interface.h"
#include "ZAF_network_learn.h"
#include "events.h"
#include "zpal_watchdog.h"
#include "app_hw.h"
#include "board_indicator.h"
#include "zw_region_config.h"
#include "ZAF_ApplicationEvents.h"
#include "zaf_event_distributor_soc.h"
#include "zpal_misc.h"
#include "zaf_protocol_config.h"
#ifdef DEBUGPRINT
#include "ZAF_PrintAppInfo.h"
#endif

#ifdef SL_CATALOG_ZW_CLI_COMMON_PRESENT
#include "zw_cli_common.h"
#endif

#if (!defined(SL_CATALOG_SILICON_LABS_ZWAVE_APPLICATION_PRESENT) && !defined(UNIT_TEST))
#include "app_hw.h"
#endif

static ESwTimerStatus notificationOverLoadTimerStatus = ESWTIMER_STATUS_FAILED;
// Timer
static SSwTimer NotificationTimer;

static bool notificationOverLoadActiveState =  false;
static uint8_t notification_to_trigger = 0;

static int32_t level_change_direction = 1;

uint8_t supportedEvents = NOTIFICATION_EVENT_POWER_MANAGEMENT_OVERLOADED_DETECTED;

#ifdef DEBUGPRINT
static uint8_t m_aDebugPrintBuffer[96];
#endif

void ApplicationTask(SApplicationHandles* pAppHandles);
void ZCB_JobStatus(TRANSMISSION_RESULT * pTransmissionResult);
void ZCB_NotificationTimerCallback(SSwTimer *pTimer);
static void notificationToggle(void);

void
zaf_event_distributor_app_zw_command_status(SZwaveCommandStatusPackage *Status)
{
  switch (Status->eStatusType) {
    case EZWAVECOMMANDSTATUS_LEARN_MODE_STATUS:
      DPRINTF("Learn status %d\r\n", Status->Content.LearnModeStatus.Status);
      if (ELEARNSTATUS_ASSIGN_COMPLETE == Status->Content.LearnModeStatus.Status) {
        if ((EINCLUSIONSTATE_EXCLUDED == ZAF_GetInclusionState())) {
          if (ESWTIMER_STATUS_FAILED != notificationOverLoadTimerStatus) {
            TimerStop(&NotificationTimer);
            notificationOverLoadTimerStatus = ESWTIMER_STATUS_FAILED;
          }
        }
      }
      break;

    default:
      break;
  }
}

/*
 * See description for function prototype in ZW_basis_api.h.
 */
ZW_APPLICATION_STATUS
ApplicationInit(__attribute__((unused)) zpal_reset_reason_t eResetReason)
{
  SRadioConfig_t* RadioConfig;

  DPRINT("Enabling watchdog\n");
  zpal_enable_watchdog(true);

#ifdef DEBUGPRINT
  DebugPrintConfig(m_aDebugPrintBuffer, sizeof(m_aDebugPrintBuffer), zpal_debug_output);
  DebugPrintf("ApplicationInit eResetReason = %d\n", eResetReason);
#endif

  RadioConfig = zaf_get_radio_config();

  // Read Rf region from MFG_ZWAVE_COUNTRY_FREQ
  zpal_radio_region_t regionMfg;
  ZW_GetMfgTokenDataCountryFreq((void*) &regionMfg);
  if (isRfRegionValid(regionMfg)) {
    RadioConfig->eRegion = regionMfg;
  } else {
    ZW_SetMfgTokenDataCountryRegion((void*) &RadioConfig->eRegion);
  }

  /*************************************************************************************
  * CREATE USER TASKS  -  ZW_ApplicationRegisterTask() and ZW_UserTask_CreateTask()
  *************************************************************************************
  * Register the main APP task function.
  *
  * ATTENTION: This function is the only task that can call ZAF API functions!!!
  * Failure to follow guidelines will result in undefined behavior.
  *
  * Furthermore, this function is the only way to register Event Notification
  * Bit Numbers for associating to given event handlers.
  *
  * ZW_UserTask_CreateTask() can be used to create additional tasks.
  * @see zwave_soc_sensor_pir example for more info.
  *************************************************************************************/
  __attribute__((unused)) bool bWasTaskCreated = ZW_ApplicationRegisterTask(
    ApplicationTask,
    EAPPLICATIONEVENT_ZWRX,
    EAPPLICATIONEVENT_ZWCOMMANDSTATUS,
    zaf_get_protocol_config()
    );
  assert(bWasTaskCreated);

  return(APPLICATION_RUNNING);
}

/**
 * A pointer to this function is passed to ZW_ApplicationRegisterTask() making it the FreeRTOS
 * application task.
 *
 * The function must be treated as a static function, but is left non-static for the purpose
 * of unit testing.
 */
void
ApplicationTask(SApplicationHandles* pAppHandles)
{
  uint32_t unhandledEvents = 0;
  ZAF_Init(xTaskGetCurrentTaskHandle(), pAppHandles);

#ifdef DEBUGPRINT
  ZAF_PrintAppInfo();
#endif

#if (!defined(SL_CATALOG_SILICON_LABS_ZWAVE_APPLICATION_PRESENT) && !defined(UNIT_TEST))
  /* This preprocessor statement can be deleted from the source code */
  app_hw_init();
#endif

  AppTimerRegister(&NotificationTimer, true, ZCB_NotificationTimerCallback);

  /* Enter SmartStart*/
  /* Protocol will commence SmartStart only if the node is NOT already included in the network */
  ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);

  // Wait for and process events
  DPRINT("PowerStrip Event processor Started\r\n");
  for (;; ) {
    unhandledEvents = zaf_event_distributor_distribute();
    if (0 != unhandledEvents) {
      DPRINTF("Unhandled Events: 0x%08lx\n", unhandledEvents);
#ifdef UNIT_TEST
      return;
#endif
    }
  }
}

/**
 * @brief The core state machine of this sample application.
 * @param event The event that triggered the call of zaf_event_distributor_app_event_manager.
 */
void
zaf_event_distributor_app_event_manager(const uint8_t event)
{
  DPRINTF("zaf_event_distributor_app_event_manager Ev: %d\r\n", event);
  cc_multilevel_switch_t *switches;

  switch (event) {
    case EVENT_APP_OUTLET1_TOGGLE:
    {
      cc_binary_switch_t * p_binary_switches = cc_binary_switch_get_config();
      cc_binary_switch_t * p_binary_switch = &p_binary_switches[0];

      if (cc_binary_switch_get_current_value(p_binary_switch) > 0) {
        cc_binary_switch_set(p_binary_switch, 0);
      } else {
        cc_binary_switch_set(p_binary_switch, 0xFF); // 0xFF for last on value.
      }
      break;
    }
    case EVENT_APP_OUTLET2_TOGGLE:
    {
      cc_binary_switch_t * p_binary_switches = cc_binary_switch_get_config();
      cc_binary_switch_t * p_binary_switch = &p_binary_switches[1];

      if (cc_binary_switch_get_current_value(p_binary_switch) > 0) {
        cc_binary_switch_set(p_binary_switch, 0);
      } else {
        cc_binary_switch_set(p_binary_switch, 0xFF); // 0xFF for last on value.
      }
      break;
    }
    case EVENT_APP_OUTLET3_TOGGLE:
    {
      cc_binary_switch_t * p_binary_switches = cc_binary_switch_get_config();
      cc_binary_switch_t * p_binary_switch = &p_binary_switches[2];

      if (cc_binary_switch_get_current_value(p_binary_switch) > 0) {
        cc_binary_switch_set(p_binary_switch, 0);
      } else {
        cc_binary_switch_set(p_binary_switch, 0xFF); // 0xFF for last on value.
      }
      break;
    }
    case EVENT_APP_OUTLET2_DIMMER_SHORT_PRESS:
      DPRINT("\nDimmer press");
      switches = cc_multilevel_switch_support_config_get_switches();
      cc_multilevel_switch_stop_level_change(&switches[0]);

      if (cc_multilevel_switch_get_current_value(&switches[0]) > 0) {
        cc_multilevel_switch_set(&switches[0], 0, 0); // Turn it off
      } else {
        cc_multilevel_switch_set(&switches[0], 0xFF, 0); // 0xFF for last on value.
      }
      break;
    case EVENT_APP_OUTLET2_DIMMER_RELEASE:
      DPRINT("\nDimmer up");
      switches = cc_multilevel_switch_support_config_get_switches();
      cc_multilevel_switch_stop_level_change(&switches[0]);
      break;

    case EVENT_APP_OUTLET2_DIMMER_HOLD:
      DPRINT("\nDimmer hold");
      switches = cc_multilevel_switch_support_config_get_switches();
      cc_multilevel_switch_start_level_change(&switches[0], (level_change_direction > 0 ? false : true), true, 0, 10);
      if (-1 == level_change_direction) {
        level_change_direction = 1;
      } else if (1 == level_change_direction) {
        level_change_direction = -1;
      }
      DPRINTF("\ndir: %d", level_change_direction);
      break;
    case EVENT_APP_NOTIFICATION_TOGGLE:
      /*
       * Pressing the NOTIFICATION_TOGGLE_BTN key will toggle the overload timer.
       * This timer will transmit a notification every 30th second.
       */
      notificationToggle();
      break;
    default:
      break;
  }

#ifdef SL_CATALOG_ZW_CLI_COMMON_PRESENT
  cli_log_system_events(event);
#endif
}

void
ZCB_JobStatus(TRANSMISSION_RESULT * pTransmissionResult)
{
  DPRINTF("\r\nTX CB for N %u", pTransmissionResult->nodeId);

  if (TRANSMISSION_RESULT_FINISHED == pTransmissionResult->isFinished) {
    zaf_event_distributor_enqueue_app_event(EVENT_APP_FINISH_EVENT_JOB);
  }
}

/**
 * @brief Called every time the notification timer triggers.
 */
void
ZCB_NotificationTimerCallback(__attribute__((unused)) SSwTimer *pTimer)
{
  JOB_STATUS jobStatus;

  DPRINT("\r\nNtfctn timer");

  uint8_t *pEventParameters;
  uint8_t eventParamLength;
  uint8_t event;

  // Trigger all notifications
  if (false == notificationOverLoadActiveState) {
    DPRINTF("\r\nNtfctn[%u] enable", notification_to_trigger);

    notificationOverLoadActiveState = true;
    event = NOTIFICATION_EVENT_POWER_MANAGEMENT_OVERLOADED_DETECTED;
    pEventParameters = NULL;
    eventParamLength = 0;
  } else {
    DPRINTF("\r\nNtfctn[%u] disable", notification_to_trigger);

    notificationOverLoadActiveState = false;
    event = NOTIFICATION_EVENT_POWER_MANAGEMENT_NO_EVENT;
    pEventParameters = &supportedEvents;
    eventParamLength = 1;
  }

  jobStatus = CC_Notification_TriggerAndTransmit(
    notification_to_trigger,
    event,
    pEventParameters,
    eventParamLength,
    ZCB_JobStatus,
    true);

  if (false == notificationOverLoadActiveState) {
    /*Find new notification in the list of defined notifications to trigger */
    if (++notification_to_trigger >= cc_notification_get_config_length()) {
      notification_to_trigger = 0;
    }
  }

  if (JOB_STATUS_SUCCESS != jobStatus) {
    TRANSMISSION_RESULT transmissionResult;

    DPRINTF("\r\nX%u", jobStatus);

    transmissionResult.status = false;
    transmissionResult.nodeId = 0;
    transmissionResult.isFinished = TRANSMISSION_RESULT_FINISHED;

    ZCB_JobStatus(&transmissionResult);
  }
}

/**
 * @brief Toggles the notification timer.
 */
static void notificationToggle(void)
{
  DPRINT("\r\nNtfctn toggle");

  if (ESWTIMER_STATUS_FAILED == notificationOverLoadTimerStatus) {
    DPRINT("\r\nNtfctn start");

    notificationOverLoadActiveState = false;

    notificationOverLoadTimerStatus = TimerStart(&NotificationTimer, 30 * 1000);

    /*
     * The timer will transmit the first notification in 30 seconds. We
     * call the callback function directly to transmit the first
     * notification right now.
     */
    ZCB_NotificationTimerCallback(NULL);
  } else {
    DPRINT("\r\nNtfctn stop");
    /* Deactivate overload timer */
    TimerStop(&NotificationTimer);
    notificationOverLoadTimerStatus = ESWTIMER_STATUS_FAILED;
  }
}
