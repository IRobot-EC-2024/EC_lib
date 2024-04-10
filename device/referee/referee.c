/**
 * @Author       : Specific_Cola specificcola@proton.me
 * @Date         : 2024-04-08 12:12:57
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-09 01:21:48
 * @Description  :
 * @Filename     : referee.c
 * @
 */
#include "referee.h"

#define REFEREE_FIFO_BUF_LENGTH 1024
#define REFEREE_UI_FIFO_ELEMENTS 32
#define REFEREE_UI_ELEMENT_SIZE 15

static Referee_t* referee_instance;

uint8_t referee_receive_fifo_buf[REFEREE_FIFO_BUF_LENGTH];
uint8_t referee_ui_fifo_buf[REFEREE_UI_FIFO_ELEMENTS * REFEREE_UI_ELEMENT_SIZE];

// 裁判系统通信接收
static void refereeReceiverCallback(Usart_Device_t* usart) {
    referee_instance->state = STATE_ONLINE;
    fifo_s_puts(&referee_instance->referee_receive_fifo,
                (char*)usart->rx_buff2[usart->rx_info.rx_buff_select],
                usart->rx_info.this_time_rx_len);
}

static void refereeOfflineCallback(Usart_Device_t* usart) {
    if (usart == NULL || usart->parent == NULL) return;
    Referee_t* referee = (Referee_t*)usart->parent;

    referee->state = STATE_OFFLINE;
    memset(&referee->referee_info, 0, sizeof(Referee_info_t));
}

Referee_t* refereeReceiverAdd(UART_HandleTypeDef* huart1,
                              UART_HandleTypeDef* huart2) {
    Referee_t* referee = (Referee_t*)malloc(sizeof(Referee_t));
    memset(referee, 0, sizeof(Referee_t));

    Usart_Register_t usart_reg;
    memset(&usart_reg, 0, sizeof(Usart_Register_t));
    usart_reg.usart_handle = huart1;
    usart_reg.rx_buff_num = 1;
    usart_reg.rx_len = 256;
    usart_reg.usart_device_callback = refereeReceiverCallback;
    usart_reg.usart_device_offline_callback = refereeOfflineCallback;
    usart_reg.parent = referee;
    usart_reg.offline_threshold = 100;
    referee->usart_info = usartDeviceRegister(&usart_reg);

    if (huart2 != NULL) {
        memset(&usart_reg, 0, sizeof(Usart_Register_t));
        usart_reg.usart_handle = huart2;
        usart_reg.rx_buff_num = 1;
        usart_reg.rx_len = 256;
        usart_reg.usart_device_callback = refereeReceiverCallback;
        usart_reg.usart_device_offline_callback = refereeOfflineCallback;
		usart_reg.parent = referee;
        usart_reg.offline_threshold = 100;
        referee->vision_info = usartDeviceRegister(&usart_reg);
    }

    fifo_s_init(&referee->referee_receive_fifo, referee_receive_fifo_buf,
                REFEREE_FIFO_BUF_LENGTH);

    uint8_t ui_size = sizeof(interaction_figure_t);
    fifo_init(&referee->referee_ui_fifo, referee_ui_fifo_buf,
              REFEREE_UI_ELEMENT_SIZE, REFEREE_UI_FIFO_ELEMENTS);

    referee->state = STATE_ONLINE;
    referee_instance = referee;
    return referee;
}

void refereeDrawUI(interaction_figure_t* interaction_figure) {
    fifo_put(&referee_instance->referee_ui_fifo, interaction_figure);
}

Referee_t* refereeReceiverGet() { return referee_instance; }

void referee_data_solve(uint8_t* frame) {
    uint16_t cmd_id = 0;

    uint8_t index = 0;

    memcpy(&referee_instance->referee_header, frame,
           sizeof(frame_header_struct_t));

    index += sizeof(frame_header_struct_t);

    memcpy(&cmd_id, frame + index, sizeof(uint16_t));
    index += sizeof(uint16_t);

    referee_instance->status[cmd_id >> 8][cmd_id & 0x0f] = 1;
    referee_instance->offline_counter[cmd_id >> 8][cmd_id & 0x0f] = 0;

    switch (cmd_id) {
        case GAME_STATE_CMD_ID: {
            memcpy(&referee_instance->referee_info.game_state, frame + index,
                   sizeof(game_state_t));
        } break;
        case GAME_RESULT_CMD_ID: {
            memcpy(&referee_instance->referee_info.game_result, frame + index,
                   sizeof(game_result_t));
        } break;
        case GAME_ROBOT_HP_CMD_ID: {
            memcpy(&referee_instance->referee_info.game_robot_HP, frame + index,
                   sizeof(game_robot_HP_t));
        } break;
        case EVENT_DATA_CMD_ID: {
            memcpy(&referee_instance->referee_info.event_data, frame + index,
                   sizeof(event_data_t));
        } break;
        case SUPPLY_PROJECTILE_ACTION_CMD_ID: {
            memcpy(&referee_instance->referee_info.supply_projectile_action,
                   frame + index, sizeof(ext_supply_projectile_action_t));
        } break;
        case REFEREE_WARNING_CMD_ID: {
            memcpy(&referee_instance->referee_info.referee_warning,
                   frame + index, sizeof(referee_warning_t));
        } break;
        case DART_INFO_CMD_ID: {
            memcpy(&referee_instance->referee_info.dart_info, frame + index,
                   sizeof(dart_info_t));
        } break;

        case ROBOT_STATE_CMD_ID: {
            memcpy(&referee_instance->referee_info.robot_status, frame + index,
                   sizeof(robot_status_t));
        } break;
        case POWER_HEAT_DATA_CMD_ID: {
            memcpy(&referee_instance->referee_info.power_heat_data,
                   frame + index, sizeof(power_heat_data_t));
        } break;
        case ROBOT_POS_CMD_ID: {
            memcpy(&referee_instance->referee_info.robot_pos, frame + index,
                   sizeof(robot_pos_t));
        } break;
        case BUFF_CMD_ID: {
            memcpy(&referee_instance->referee_info.buff, frame + index,
                   sizeof(buff_t));
        } break;
        case AIR_SUPPORT_DATA_CMD_ID: {
            memcpy(&referee_instance->referee_info.air_support_data,
                   frame + index, sizeof(air_support_data_t));
        } break;
        case HURT_DATA_CMD_ID: {
            memcpy(&referee_instance->referee_info.hurt_data, frame + index,
                   sizeof(hurt_data_t));
        } break;
        case SHOOT_DATA_CMD_ID: {
            memcpy(&referee_instance->referee_info.shoot_data, frame + index,
                   sizeof(shoot_data_t));
        } break;
        case PROJECTILE_ALLOWANCE_CMD_ID: {
            memcpy(&referee_instance->referee_info.projectile_allowance,
                   frame + index, sizeof(projectile_allowance_t));
        } break;
        case RFID_STATUS_CMD_ID: {
            memcpy(&referee_instance->referee_info.rfid_status, frame + index,
                   sizeof(rfid_status_t));
        } break;
        case DART_CLIENT_CMD_CMD_ID: {
            memcpy(&referee_instance->referee_info.dart_client_cmd,
                   frame + index, sizeof(dart_client_cmd_t));
        } break;
        case GROUND_ROBOT_POSITION_CMD_ID: {
            memcpy(&referee_instance->referee_info.ground_robot_position,
                   frame + index, sizeof(ground_robot_position_t));
        } break;
        case RADAR_MARK_DATA_CMD_ID: {
            memcpy(&referee_instance->referee_info.radar_mark_data,
                   frame + index, sizeof(radar_mark_data_t));
        } break;
        case SENTRY_INFO_CMD_ID: {
            memcpy(&referee_instance->referee_info.sentry_info, frame + index,
                   sizeof(sentry_info_t));
        } break;
        case RADAR_INFO_CMD_ID: {
            memcpy(&referee_instance->referee_info.radar_info, frame + index,
                   sizeof(radar_info_t));
        } break;
        case ROBOT_INTERACTION_DATA_CMD_ID: {
            memcpy(&referee_instance->referee_info.robot_interaction_data,
                   frame + index, sizeof(robot_interaction_data_t));
        } break;
        case CUSTOM_ROBOT_DATA_CMD_ID: {
            memcpy(&referee_instance->referee_info.custom_robot_data,
                   frame + index, sizeof(custom_robot_data_t));
        } break;
        case MAP_COMMAND_CMD_ID: {
            memcpy(&referee_instance->referee_info.map_command, frame + index,
                   sizeof(map_command_t));
        } break;
        case REMOTE_CONTROL_CMD_ID: {
            memcpy(&referee_instance->referee_info.remote_control,
                   frame + index, sizeof(remote_control_t));
        } break;
        case MAP_ROBOT_DATA_CMD_ID: {
            memcpy(&referee_instance->referee_info.map_robot_data,
                   frame + index, sizeof(map_robot_data_t));
        } break;
        case MAP_DATA_CMD_ID: {
            memcpy(&referee_instance->referee_info.map_data, frame + index,
                   sizeof(map_data_t));
        } break;
        case CUSTOM_INFO_CMD_ID: {
            memcpy(&referee_instance->referee_info.custom_info, frame + index,
                   sizeof(custom_info_t));
        } break;
        default: {
            break;
        }
    }
}

/**
 * @brief          单字节解包
 * @param[in]      void
 * @retval         none
 */
void referee_unpack_fifo_data(void) {
    uint8_t byte = 0;
    uint8_t sof = HEADER_SOF;
    unpack_data_t* p_obj = &referee_instance->referee_unpack_obj;

    while (fifo_s_used(&referee_instance->referee_receive_fifo)) {
        byte = fifo_s_get(&referee_instance->referee_receive_fifo);
        switch (p_obj->unpack_step) {
            case STEP_HEADER_SOF: {
                if (byte == sof) {
                    p_obj->unpack_step = STEP_LENGTH_LOW;
                    p_obj->protocol_packet[p_obj->index++] = byte;
                } else {
                    p_obj->index = 0;
                }
            } break;

            case STEP_LENGTH_LOW: {
                p_obj->data_len = byte;
                p_obj->protocol_packet[p_obj->index++] = byte;
                p_obj->unpack_step = STEP_LENGTH_HIGH;
            } break;

            case STEP_LENGTH_HIGH: {
                p_obj->data_len |= (byte << 8);
                p_obj->protocol_packet[p_obj->index++] = byte;

                if (p_obj->data_len <
                    (REF_PROTOCOL_FRAME_MAX_SIZE - REF_HEADER_CRC_CMDID_LEN)) {
                    p_obj->unpack_step = STEP_FRAME_SEQ;
                } else {
                    p_obj->unpack_step = STEP_HEADER_SOF;
                    p_obj->index = 0;
                }
            } break;
            case STEP_FRAME_SEQ: {
                p_obj->protocol_packet[p_obj->index++] = byte;
                p_obj->unpack_step = STEP_HEADER_CRC8;
            } break;

            case STEP_HEADER_CRC8: {
                p_obj->protocol_packet[p_obj->index++] = byte;

                if (p_obj->index == REF_PROTOCOL_HEADER_SIZE) {
                    if (crc_8(p_obj->protocol_packet,
                              REF_PROTOCOL_HEADER_SIZE)) {
                        p_obj->unpack_step = STEP_DATA_CRC16;
                    } else {
                        p_obj->unpack_step = STEP_HEADER_SOF;
                        p_obj->index = 0;
                    }
                }
            } break;

            case STEP_DATA_CRC16: {
                if (p_obj->index <
                    (REF_HEADER_CRC_CMDID_LEN + p_obj->data_len)) {
                    p_obj->protocol_packet[p_obj->index++] = byte;
                }
                if (p_obj->index >=
                    (REF_HEADER_CRC_CMDID_LEN + p_obj->data_len)) {
                    p_obj->unpack_step = STEP_HEADER_SOF;
                    p_obj->index = 0;

                    if (crc_16(p_obj->protocol_packet,
                               REF_HEADER_CRC_CMDID_LEN + p_obj->data_len)) {
                        referee_data_solve(p_obj->protocol_packet);
                    }
                }
            } break;

            default: {
                p_obj->unpack_step = STEP_HEADER_SOF;
                p_obj->index = 0;
            } break;
        }
    }
}

// 裁判系统通信发送

void referee_status_updata(void) {
    uint8_t i = 0, j = 0;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 16; j++) {
            if (referee_instance->status[i][j]) {
                referee_instance->offline_counter[i][j]++;
                if (referee_instance->offline_counter[i][j] > 1000) {
                    referee_instance->status[i][j] = 0;
                }
            }
        }
    }
}
