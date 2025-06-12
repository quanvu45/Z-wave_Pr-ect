/**
 * @file
 * Command Class Zwave Plusinfo Configuration
 * @remarks This file is auto generated
 * @copyright 2022 Silicon Laboratories Inc.
 */ 

#include <cc_zwave_plus_info_config_api.h>
#include <ZW_product_id_enum.h>
#include "SizeOf.h"
#include "zaf_config.h"
#include <assert.h>
#include "DebugPrint.h"


zw_plus_info_config_icons_t endpoint_configs[] = {
  {
    .installer_icon_type = ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH,
    .user_icon_type = ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH,
    .endpoint = 1
  },
  {
    .installer_icon_type = ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH,
    .user_icon_type = ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH,
    .endpoint = 2
  },
  {
    .installer_icon_type = ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH,
    .user_icon_type = ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH,
    .endpoint = 3
  },
  {
    .installer_icon_type = ICON_TYPE_GENERIC_LIGHT_DIMMER_SWITCH,
    .user_icon_type = ICON_TYPE_GENERIC_LIGHT_DIMMER_SWITCH,
    .endpoint = 4
  },
};

/* These functions override the weak functions in CC_Zwaveplusinfo.c */

uint8_t cc_zwave_plus_info_config_get_endpoint_count(void)
{
  return 4;
}

zw_plus_info_config_icons_t * cc_zwave_plus_info_config_get_endpoint_entry(uint8_t endpoint)
{
  for (uint8_t i = 0; i < sizeof_array(endpoint_configs); i++)
  {
    if (endpoint == endpoint_configs[endpoint - 1].endpoint)
    {
      return &endpoint_configs[endpoint - 1];
    }
  }
  DPRINTF("Missing CC Z-Wave Plus Info Configuration for the given endpoint: %d\n", endpoint);
  assert(0);
  return NULL;
}
