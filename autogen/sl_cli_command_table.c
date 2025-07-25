/***************************************************************************//**
 * @file sl_cli_command_table.c
 * @brief Declarations of relevant command structs for cli framework.
 * @version x.y.z
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include <stdlib.h>

#include "sl_cli_config.h"
#include "sl_cli_command.h"
#include "sl_cli_arguments.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *****************************   TEMPLATED FILE   ******************************
 ******************************************************************************/

/*******************************************************************************
 * Example syntax (.slcc or .slcp) for populating this file:
 *
 *   template_contribution:
 *     - name: cli_command          # Register a command
 *       value:
 *         name: status             # Name of command
 *         handler: status_command  # Function to be called. Must be defined
 *         help: "Prints status"    # Optional help description
 *         shortcuts:               # Optional shorcut list
 *           - name: st
 *         argument:                # Argument list, if apliccable
 *           - type: uint8          # Variable type
 *             help: "Channel"      # Optional description
 *           - type: string
 *             help: "Text"
 *     - name: cli_group            # Register a group
 *       value:
 *         name: shell              # Group name
 *         help: "Shell commands"   # Optional help description
 *         shortcuts:               # Optional shorcuts
 *           - name: sh
 *     - name: cli_command
 *       value:
 *         name: repeat
 *         handler: repeat_cmd
 *         help: "Repeat commands"
 *         shortcuts:
 *           - name: r
 *           - name: rep
 *         group: shell            # Associate command with group
 *         argument:
 *           - type: string
 *             help: "Text"
 *           - type: additional
 *             help: "More text"
 *
 * For subgroups, an optional unique id can be used to allow a particular name to
 * be used more than once. In the following case, from the command line the
 * following commands are available:
 *
 * >  root_1 shell status
 * >  root_2 shell status
 *
 *     - name: cli_group            # Register a group
 *       value:
 *         name: root_1             # Group name
 *
 *     - name: cli_group            # Register a group
 *       value:
 *         name: root_2             # Group name
 *
 *    - name: cli_group             # Register a group
 *       value:
 *         name: shell              # Group name
 *         id: shell_root_1         # Optional unique id for group
 *         group: root_1            # Add group to root_1 group
 *
 *    - name: cli_group             # Register a group
 *       value:
 *         name: shell              # Group name
 *         id: shell_root_2         # Optional unique id for group
 *         group: root_2            # Add group to root_1 group
 *
 *    - name: cli_command           # Register a command
 *       value:
 *         name: status
 *         handler: status_1
 *         group: shell_root_1      # id of subgroup
 *
 *    - name: cli_command           # Register a command
 *       value:
 *         name: status
 *         handler: status_2
 *         group: shell_root_2      # id of subgroup
 *
 ******************************************************************************/

// Provide function declarations
void button_press_from_cli(sl_cli_command_arg_t *arguments);
void button_hold_from_cli(sl_cli_command_arg_t *arguments);
void button_release_from_cli(sl_cli_command_arg_t *arguments);
void cli_set_learn_mode(sl_cli_command_arg_t *arguments);
void cli_factory_reset(sl_cli_command_arg_t *arguments);
void cli_get_dsk(sl_cli_command_arg_t *arguments);
void cli_get_region(sl_cli_command_arg_t *arguments);
void cli_toggle_endpoint(sl_cli_command_arg_t *arguments);
void cli_dim_endpoint(sl_cli_command_arg_t *arguments);
void cli_toggle_notification_sending(sl_cli_command_arg_t *arguments);
void cli_get_rgb_values(sl_cli_command_arg_t *arguments);
void cli_get_led_state(sl_cli_command_arg_t *arguments);

// Command structs. Names are in the format : cli_cmd_{command group name}_{command name}
// In order to support hyphen in command and group name, every occurence of it while
// building struct names will be replaced by "_hyphen_"
static const sl_cli_command_info_t cli_cmd_button_press = \
  SL_CLI_COMMAND(button_press_from_cli,
                 "Emulating a button press",
                  "Button: 0: BTN0, 1+: BTN1" SL_CLI_UNIT_SEPARATOR "Press and hold duration: 0 - short, 1- medium, 2 - long, 3+ - verylong" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_button_hold = \
  SL_CLI_COMMAND(button_hold_from_cli,
                 "Emulates pressing and holding a button.",
                  "Button: 0: BTN0, 1+: BTN1" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_button_release = \
  SL_CLI_COMMAND(button_release_from_cli,
                 "Emulates releasing a button.",
                  "Button: 0: BTN0, 1+: BTN1" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd__set_learn_mode = \
  SL_CLI_COMMAND(cli_set_learn_mode,
                 "Include / exclude the device into / from a z-wave network",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd__factory_reset = \
  SL_CLI_COMMAND(cli_factory_reset,
                 "Factory reset the device",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd__get_dsk = \
  SL_CLI_COMMAND(cli_get_dsk,
                 "Read the DSK, stored in the manufacturing token",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd__get_region = \
  SL_CLI_COMMAND(cli_get_region,
                 "Get the used region",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd__toggle_endpoint = \
  SL_CLI_COMMAND(cli_toggle_endpoint,
                 "Toggle the endpoint 1 or 2. Possible values are 1 or 2",
                  "Endpoint number (1 or 2)" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd__dim_endpoint = \
  SL_CLI_COMMAND(cli_dim_endpoint,
                 "Dim the endpoint 2",
                  "New dimming level, it can be minimum 0 and maximum 99" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd__toggle_notification_sending = \
  SL_CLI_COMMAND(cli_toggle_notification_sending,
                 "Send Overload detected notification, for more information, see the application README",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd__get_rgb_values = \
  SL_CLI_COMMAND(cli_get_rgb_values,
                 "Get rgb LED values",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd__get_led_state = \
  SL_CLI_COMMAND(cli_get_led_state,
                 "Get LED1 state from the expansion header",
                  "",
                 {SL_CLI_ARG_END, });


// Create group command tables and structs if cli_groups given
// in template. Group name is suffixed with _group_table for tables
// and group commands are cli_cmd_grp_( group name )
static const sl_cli_command_entry_t button_group_table[] = {
  { "press", &cli_cmd_button_press, false },
  { "p", &cli_cmd_button_press, true },
  { "hold", &cli_cmd_button_hold, false },
  { "h", &cli_cmd_button_hold, true },
  { "release", &cli_cmd_button_release, false },
  { "r", &cli_cmd_button_release, true },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_button = \
  SL_CLI_COMMAND_GROUP(button_group_table, "Emulating button events (various type of button presses).");

// Create root command table
const sl_cli_command_entry_t sl_cli_default_command_table[] = {
  { "set_learn_mode", &cli_cmd__set_learn_mode, false },
  { "factory_reset", &cli_cmd__factory_reset, false },
  { "get_dsk", &cli_cmd__get_dsk, false },
  { "get_region", &cli_cmd__get_region, false },
  { "toggle_endpoint", &cli_cmd__toggle_endpoint, false },
  { "dim_endpoint", &cli_cmd__dim_endpoint, false },
  { "toggle_notification_sending", &cli_cmd__toggle_notification_sending, false },
  { "get_rgb_values", &cli_cmd__get_rgb_values, false },
  { "get_led_state", &cli_cmd__get_led_state, false },
  { "button", &cli_cmd_grp_button, false },
  { "btn", &cli_cmd_grp_button, true },
  { "b", &cli_cmd_grp_button, true },
  { NULL, NULL, false },
};


#ifdef __cplusplus
}
#endif
