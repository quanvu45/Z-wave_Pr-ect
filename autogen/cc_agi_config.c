/**
 * @file
 * Command Class Association Group Information
 * @remarks This file is auto generated
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include <cc_agi_config_api.h>
#include <SizeOf.h>

static const char GROUP_NAME_ENDPOINT_1_GROUP_2[] = "Alarm EP 1";
static const ccc_pair_t COMMANDS_ENDPOINT_1_GROUP_2[] = {
  {
    .cmdClass = COMMAND_CLASS_NOTIFICATION_V3,
    .cmd = NOTIFICATION_REPORT_V3
  },
};
static const char GROUP_NAME_ENDPOINT_1_GROUP_3[] = "BTN2";
static const ccc_pair_t COMMANDS_ENDPOINT_1_GROUP_3[] = {
  {
    .cmdClass = COMMAND_CLASS_BASIC,
    .cmd = BASIC_SET
  },
};
static const char GROUP_NAME_ENDPOINT_2_GROUP_2[] = "Alarm EP 2";
static const ccc_pair_t COMMANDS_ENDPOINT_2_GROUP_2[] = {
  {
    .cmdClass = COMMAND_CLASS_NOTIFICATION_V3,
    .cmd = NOTIFICATION_REPORT_V3
  },
};
static const char GROUP_NAME_ENDPOINT_2_GROUP_3[] = "BTN3";
static const ccc_pair_t COMMANDS_ENDPOINT_2_GROUP_3[] = {
  {
    .cmdClass = COMMAND_CLASS_BASIC,
    .cmd = BASIC_SET
  },
};
static const char GROUP_NAME_ENDPOINT_3_GROUP_2[] = "Alarm EP 3";
static const ccc_pair_t COMMANDS_ENDPOINT_3_GROUP_2[] = {
  {
    .cmdClass = COMMAND_CLASS_NOTIFICATION_V3,
    .cmd = NOTIFICATION_REPORT_V3
  },
};
static const char GROUP_NAME_ENDPOINT_3_GROUP_3[] = "BTN4";
static const ccc_pair_t COMMANDS_ENDPOINT_3_GROUP_3[] = {
  {
    .cmdClass = COMMAND_CLASS_BASIC,
    .cmd = BASIC_SET
  },
};
static const char GROUP_NAME_ENDPOINT_4_GROUP_2[] = "Alarm EP 4";
static const ccc_pair_t COMMANDS_ENDPOINT_4_GROUP_2[] = {
  {
    .cmdClass = COMMAND_CLASS_NOTIFICATION_V3,
    .cmd = NOTIFICATION_REPORT_V3
  },
};

static const cc_agi_group_t ROOT_DEVICE_GROUPS[] =
{
  {
    .name = GROUP_NAME_ENDPOINT_1_GROUP_2,
    .name_length = sizeof(GROUP_NAME_ENDPOINT_1_GROUP_2),
    .profile = {
      .profile_MS = ASSOCIATION_GROUP_INFO_REPORT_AGI_PROFILE_NOTIFICATION,
      .profile_LS = NOTIFICATION_REPORT_POWER_MANAGEMENT_V4
    },
    .ccc_pairs = COMMANDS_ENDPOINT_1_GROUP_2,
    .ccc_pair_count = sizeof_array(COMMANDS_ENDPOINT_1_GROUP_2),
  },
  {
    .name = GROUP_NAME_ENDPOINT_1_GROUP_3,
    .name_length = sizeof(GROUP_NAME_ENDPOINT_1_GROUP_3),
    .profile = {
      .profile_MS = 32,
      .profile_LS = 1
    },
    .ccc_pairs = COMMANDS_ENDPOINT_1_GROUP_3,
    .ccc_pair_count = sizeof_array(COMMANDS_ENDPOINT_1_GROUP_3),
  },
  {
    .name = GROUP_NAME_ENDPOINT_2_GROUP_2,
    .name_length = sizeof(GROUP_NAME_ENDPOINT_2_GROUP_2),
    .profile = {
      .profile_MS = ASSOCIATION_GROUP_INFO_REPORT_AGI_PROFILE_NOTIFICATION,
      .profile_LS = NOTIFICATION_REPORT_POWER_MANAGEMENT_V4
    },
    .ccc_pairs = COMMANDS_ENDPOINT_2_GROUP_2,
    .ccc_pair_count = sizeof_array(COMMANDS_ENDPOINT_2_GROUP_2),
  },
  {
    .name = GROUP_NAME_ENDPOINT_2_GROUP_3,
    .name_length = sizeof(GROUP_NAME_ENDPOINT_2_GROUP_3),
    .profile = {
      .profile_MS = 32,
      .profile_LS = 1
    },
    .ccc_pairs = COMMANDS_ENDPOINT_2_GROUP_3,
    .ccc_pair_count = sizeof_array(COMMANDS_ENDPOINT_2_GROUP_3),
  },
  {
    .name = GROUP_NAME_ENDPOINT_3_GROUP_2,
    .name_length = sizeof(GROUP_NAME_ENDPOINT_3_GROUP_2),
    .profile = {
      .profile_MS = ASSOCIATION_GROUP_INFO_REPORT_AGI_PROFILE_NOTIFICATION,
      .profile_LS = NOTIFICATION_REPORT_POWER_MANAGEMENT_V4
    },
    .ccc_pairs = COMMANDS_ENDPOINT_3_GROUP_2,
    .ccc_pair_count = sizeof_array(COMMANDS_ENDPOINT_3_GROUP_2),
  },
  {
    .name = GROUP_NAME_ENDPOINT_3_GROUP_3,
    .name_length = sizeof(GROUP_NAME_ENDPOINT_3_GROUP_3),
    .profile = {
      .profile_MS = 32,
      .profile_LS = 1
    },
    .ccc_pairs = COMMANDS_ENDPOINT_3_GROUP_3,
    .ccc_pair_count = sizeof_array(COMMANDS_ENDPOINT_3_GROUP_3),
  },
  {
    .name = GROUP_NAME_ENDPOINT_4_GROUP_2,
    .name_length = sizeof(GROUP_NAME_ENDPOINT_4_GROUP_2),
    .profile = {
      .profile_MS = ASSOCIATION_GROUP_INFO_REPORT_AGI_PROFILE_NOTIFICATION,
      .profile_LS = NOTIFICATION_REPORT_POWER_MANAGEMENT_V4
    },
    .ccc_pairs = COMMANDS_ENDPOINT_4_GROUP_2,
    .ccc_pair_count = sizeof_array(COMMANDS_ENDPOINT_4_GROUP_2),
  },
};


static const cc_agi_group_t ENDPOINT_1_GROUPS[] =
{
  {
    .name = GROUP_NAME_ENDPOINT_1_GROUP_2,
    .name_length = sizeof(GROUP_NAME_ENDPOINT_1_GROUP_2),
    .profile = {
      .profile_MS = ASSOCIATION_GROUP_INFO_REPORT_AGI_PROFILE_NOTIFICATION,
      .profile_LS = NOTIFICATION_REPORT_POWER_MANAGEMENT_V4
    }, 
    .ccc_pairs = COMMANDS_ENDPOINT_1_GROUP_2,
    .ccc_pair_count = sizeof_array(COMMANDS_ENDPOINT_1_GROUP_2),
  },
  {
    .name = GROUP_NAME_ENDPOINT_1_GROUP_3,
    .name_length = sizeof(GROUP_NAME_ENDPOINT_1_GROUP_3),
    .profile = {
      .profile_MS = 32,
      .profile_LS = 1
    }, 
    .ccc_pairs = COMMANDS_ENDPOINT_1_GROUP_3,
    .ccc_pair_count = sizeof_array(COMMANDS_ENDPOINT_1_GROUP_3),
  },
};
static const cc_agi_group_t ENDPOINT_2_GROUPS[] =
{
  {
    .name = GROUP_NAME_ENDPOINT_2_GROUP_2,
    .name_length = sizeof(GROUP_NAME_ENDPOINT_2_GROUP_2),
    .profile = {
      .profile_MS = ASSOCIATION_GROUP_INFO_REPORT_AGI_PROFILE_NOTIFICATION,
      .profile_LS = NOTIFICATION_REPORT_POWER_MANAGEMENT_V4
    }, 
    .ccc_pairs = COMMANDS_ENDPOINT_2_GROUP_2,
    .ccc_pair_count = sizeof_array(COMMANDS_ENDPOINT_2_GROUP_2),
  },
  {
    .name = GROUP_NAME_ENDPOINT_2_GROUP_3,
    .name_length = sizeof(GROUP_NAME_ENDPOINT_2_GROUP_3),
    .profile = {
      .profile_MS = 32,
      .profile_LS = 1
    }, 
    .ccc_pairs = COMMANDS_ENDPOINT_2_GROUP_3,
    .ccc_pair_count = sizeof_array(COMMANDS_ENDPOINT_2_GROUP_3),
  },
};
static const cc_agi_group_t ENDPOINT_3_GROUPS[] =
{
  {
    .name = GROUP_NAME_ENDPOINT_3_GROUP_2,
    .name_length = sizeof(GROUP_NAME_ENDPOINT_3_GROUP_2),
    .profile = {
      .profile_MS = ASSOCIATION_GROUP_INFO_REPORT_AGI_PROFILE_NOTIFICATION,
      .profile_LS = NOTIFICATION_REPORT_POWER_MANAGEMENT_V4
    }, 
    .ccc_pairs = COMMANDS_ENDPOINT_3_GROUP_2,
    .ccc_pair_count = sizeof_array(COMMANDS_ENDPOINT_3_GROUP_2),
  },
  {
    .name = GROUP_NAME_ENDPOINT_3_GROUP_3,
    .name_length = sizeof(GROUP_NAME_ENDPOINT_3_GROUP_3),
    .profile = {
      .profile_MS = 32,
      .profile_LS = 1
    }, 
    .ccc_pairs = COMMANDS_ENDPOINT_3_GROUP_3,
    .ccc_pair_count = sizeof_array(COMMANDS_ENDPOINT_3_GROUP_3),
  },
};
static const cc_agi_group_t ENDPOINT_4_GROUPS[] =
{
  {
    .name = GROUP_NAME_ENDPOINT_4_GROUP_2,
    .name_length = sizeof(GROUP_NAME_ENDPOINT_4_GROUP_2),
    .profile = {
      .profile_MS = ASSOCIATION_GROUP_INFO_REPORT_AGI_PROFILE_NOTIFICATION,
      .profile_LS = NOTIFICATION_REPORT_POWER_MANAGEMENT_V4
    }, 
    .ccc_pairs = COMMANDS_ENDPOINT_4_GROUP_2,
    .ccc_pair_count = sizeof_array(COMMANDS_ENDPOINT_4_GROUP_2),
  },
};

static const cc_agi_config_t config[] = {
  {
    .groups = ROOT_DEVICE_GROUPS,
    .group_count = sizeof_array(ROOT_DEVICE_GROUPS)
  },
  {
    .groups = ENDPOINT_1_GROUPS,
    .group_count = sizeof_array(ENDPOINT_1_GROUPS)
  },
  {
    .groups = ENDPOINT_2_GROUPS,
    .group_count = sizeof_array(ENDPOINT_2_GROUPS)
  },
  {
    .groups = ENDPOINT_3_GROUPS,
    .group_count = sizeof_array(ENDPOINT_3_GROUPS)
  },
  {
    .groups = ENDPOINT_4_GROUPS,
    .group_count = sizeof_array(ENDPOINT_4_GROUPS)
  },
};

const cc_agi_config_t * cc_agi_get_config(void)
{
  return config;
}

uint8_t cc_agi_config_get_group_count_by_endpoint(uint8_t endpoint)
{
  if (endpoint > sizeof_array(config)) {
    return 0;
  }
  return config[endpoint].group_count;
}

const cc_agi_group_t * cc_agi_get_rootdevice_groups(void)
{
  return ROOT_DEVICE_GROUPS;
}
