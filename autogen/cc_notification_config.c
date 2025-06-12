/**
 * @file
 * Command Class Notification Configuration
 * @remarks This file is auto generated
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include <cc_notification_config_api.h>
#include <CC_Notification.h>
#include "cc_notification_events.h"
#include <SizeOf.h>
#include <assert.h>

static const notification_event_state STATES_EVENTS_EP1_NOTIFICATION_TYPE_POWER_MANAGEMENT[] = {
  NOTIFICATION_EVENT_POWER_MANAGEMENT_OVERLOADED_DETECTED,
};
static const notification_event_state STATES_EVENTS_EP2_NOTIFICATION_TYPE_POWER_MANAGEMENT[] = {
  NOTIFICATION_EVENT_POWER_MANAGEMENT_OVERLOADED_DETECTED,
};
static const notification_event_state STATES_EVENTS_EP3_NOTIFICATION_TYPE_POWER_MANAGEMENT[] = {
  NOTIFICATION_EVENT_POWER_MANAGEMENT_OVERLOADED_DETECTED,
};
static const notification_event_state STATES_EVENTS_EP4_NOTIFICATION_TYPE_POWER_MANAGEMENT[] = {
  NOTIFICATION_EVENT_POWER_MANAGEMENT_OVERLOADED_DETECTED,
};

static cc_notification_t notifications[] = {
  {
    .type = NOTIFICATION_TYPE_POWER_MANAGEMENT,
    .endpoint = 1,
    .agi_profile.profile_MS = ASSOCIATION_GROUP_INFO_REPORT_AGI_PROFILE_NOTIFICATION,
    .agi_profile.profile_LS = NOTIFICATION_REPORT_POWER_MANAGEMENT_V4,
    .events = STATES_EVENTS_EP1_NOTIFICATION_TYPE_POWER_MANAGEMENT,
    .event_count = sizeof_array(STATES_EVENTS_EP1_NOTIFICATION_TYPE_POWER_MANAGEMENT),
    .current_event = NOTIFICATION_EVENT_NO_EVENT,
    .status        = NOTIFICATION_STATUS_UNSOLICIT_ACTIVATED,
  },
  {
    .type = NOTIFICATION_TYPE_POWER_MANAGEMENT,
    .endpoint = 2,
    .agi_profile.profile_MS = ASSOCIATION_GROUP_INFO_REPORT_AGI_PROFILE_NOTIFICATION,
    .agi_profile.profile_LS = NOTIFICATION_REPORT_POWER_MANAGEMENT_V4,
    .events = STATES_EVENTS_EP2_NOTIFICATION_TYPE_POWER_MANAGEMENT,
    .event_count = sizeof_array(STATES_EVENTS_EP2_NOTIFICATION_TYPE_POWER_MANAGEMENT),
    .current_event = NOTIFICATION_EVENT_NO_EVENT,
    .status        = NOTIFICATION_STATUS_UNSOLICIT_ACTIVATED,
  },
  {
    .type = NOTIFICATION_TYPE_POWER_MANAGEMENT,
    .endpoint = 3,
    .agi_profile.profile_MS = ASSOCIATION_GROUP_INFO_REPORT_AGI_PROFILE_NOTIFICATION,
    .agi_profile.profile_LS = NOTIFICATION_REPORT_POWER_MANAGEMENT_V4,
    .events = STATES_EVENTS_EP3_NOTIFICATION_TYPE_POWER_MANAGEMENT,
    .event_count = sizeof_array(STATES_EVENTS_EP3_NOTIFICATION_TYPE_POWER_MANAGEMENT),
    .current_event = NOTIFICATION_EVENT_NO_EVENT,
    .status        = NOTIFICATION_STATUS_UNSOLICIT_ACTIVATED,
  },
  {
    .type = NOTIFICATION_TYPE_POWER_MANAGEMENT,
    .endpoint = 4,
    .agi_profile.profile_MS = ASSOCIATION_GROUP_INFO_REPORT_AGI_PROFILE_NOTIFICATION,
    .agi_profile.profile_LS = NOTIFICATION_REPORT_POWER_MANAGEMENT_V4,
    .events = STATES_EVENTS_EP4_NOTIFICATION_TYPE_POWER_MANAGEMENT,
    .event_count = sizeof_array(STATES_EVENTS_EP4_NOTIFICATION_TYPE_POWER_MANAGEMENT),
    .current_event = NOTIFICATION_EVENT_NO_EVENT,
    .status        = NOTIFICATION_STATUS_UNSOLICIT_ACTIVATED,
  },
};

_Static_assert((sizeof_array(notifications) > 0), "STATIC_ASSERT_FAILED_size_mismatch");

cc_notification_t * cc_notification_get_config(void) {
  return notifications;
}

uint8_t cc_notification_get_config_length(void) {
  return sizeof_array(notifications);
}

cc_notification_t* cc_notification_get(uint8_t index) {
  if(index >= sizeof_array(notifications)) {
    return NULL;
  }
  return &notifications[index];
}

int8_t cc_notification_get_index_by_type_and_endpoint(notification_type_t type, uint8_t endpoint) {
  for (uint8_t i = 0; i < sizeof_array(notifications); i++) {
    if (type == notifications[i].type && endpoint == notifications[i].endpoint) {
      return (int8_t)i;
    }
  }
  return -1;
}

notification_type_t cc_notification_get_type(uint8_t index) {
  return notifications[index].type;
}

notification_event_state cc_notification_get_current_event(uint8_t index) {
  return notifications[index].current_event;
}

agi_profile_t cc_notification_get_agi_profile(uint8_t index) {
  return notifications[index].agi_profile;
}

uint8_t cc_notification_get_endpoint(uint8_t index) {
  return notifications[index].endpoint;
}

NOTIFICATION_STATUS cc_notification_get_status(uint8_t index) {
  return notifications[index].status;
}

bool cc_notification_is_type_supported(notification_type_t type) {
  for (uint8_t i = 0; i < sizeof_array(notifications); i++) {
    if (type == notifications[i].type) {
      return true;
    }
  }
  return false;
}

int8_t cc_notification_find_event(uint8_t event, uint8_t index)
{
  for (uint8_t i = 0; i < notifications[index].event_count; i++) {
    if (event == notifications[index].events[i]) {
      return (int8_t)i;
    }
  }
  return -1;
}

uint8_t cc_notification_config_get_number_of_events(uint8_t index)
{
  assert(index < sizeof_array(notifications));
  return notifications[index].event_count;
}

ZAF_CC_REGISTER_CONFIG(COMMAND_CLASS_NOTIFICATION_V8, &notifications[0], 0);
ZAF_CC_REGISTER_CONFIG(COMMAND_CLASS_NOTIFICATION_V8, &notifications[1], 1);
ZAF_CC_REGISTER_CONFIG(COMMAND_CLASS_NOTIFICATION_V8, &notifications[2], 2);
ZAF_CC_REGISTER_CONFIG(COMMAND_CLASS_NOTIFICATION_V8, &notifications[3], 3);
