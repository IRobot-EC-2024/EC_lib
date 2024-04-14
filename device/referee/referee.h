/**
 * @Author       : Specific_Cola specificcola@proton.me
 * @Date         : 2024-04-07 00:48:03
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-13 04:48:20
 * @Description  :
 * @Filename     : referee.h
 * @
 */
#ifndef REFEREE_RECEIVER_H__
#define REFEREE_RECEIVER_H__

#include "Client_UI.h"
#include "bsp_usart.h"
#include "crc16.h"
#include "crc8.h"
#include "fifo.h"
#include "referee_info.h"

typedef struct {
    game_state_t game_state;        // 0x0001
    game_result_t game_result;      // 0x0002
    game_robot_HP_t game_robot_HP;  // 0x0003

    event_data_t event_data;                                  // 0x0101
    ext_supply_projectile_action_t supply_projectile_action;  // 0x0102
    referee_warning_t referee_warning;                        // 0x0104
    dart_info_t dart_info;                                    // 0x0105

    robot_status_t robot_status;                    // 0x0201
    power_heat_data_t power_heat_data;              // 0x0202
    robot_pos_t robot_pos;                          // 0x0203
    buff_t buff;                                    // 0x0204
    air_support_data_t air_support_data;            // 0x0205
    hurt_data_t hurt_data;                          // 0x0206
    shoot_data_t shoot_data;                        // 0x0207
    projectile_allowance_t projectile_allowance;    // 0x0208
    rfid_status_t rfid_status;                      // 0x0209
    dart_client_cmd_t dart_client_cmd;              // 0x020A
    ground_robot_position_t ground_robot_position;  // 0x020B
    radar_mark_data_t radar_mark_data;              // 0x020C
    sentry_info_t sentry_info;                      // 0x020D
    radar_info_t radar_info;                        // 0x020E

    robot_interaction_data_t robot_interaction_data;  // 0x0301
    custom_robot_data_t custom_robot_data;            // 0x0302:图传
    map_command_t map_command;                        // 0x0303
    remote_control_t remote_control;                  // 0x0304:图传
    map_robot_data_t map_robot_data;                  // 0x0305
    custom_client_data_t custom_client_data;          // 0x0306
    map_data_t map_data;                              // 0x0307
    custom_info_t custom_info;                        // 0x0308

} Referee_info_t;

typedef struct {
    uint8_t state;
    Usart_Device_t* usart_info;
    Usart_Device_t* vision_info;

    // 裁判系统接收
    frame_header_struct_t referee_header;
    Referee_info_t referee_info;
    unpack_data_t referee_unpack_obj;
    fifo_s_t referee_receive_fifo;
    uint32_t receive_time_stemp[4][16];

    // 裁判系统发送
    uint8_t seq;
    fifo_t referee_figure_fifo;  // 图像队列
    fifo_s_t referee_send_fifo;  // 所有信息汇总
} Referee_t;

Referee_t* refereeReceiverAdd(UART_HandleTypeDef* huart1, UART_HandleTypeDef* huart2);
void referee_data_solve(uint8_t* frame);
Referee_t* refereeReceiverGet(void);

void refereeInteractionPush(robot_interaction_data_t* interaction_data, uint8_t user_data_length);
void refereeInteractionSend(void);
uint32_t refereeInteractionRemain(void);
void refereeFigurePush(interaction_figure_t* interaction_figure);
void refereeFigure2Interaction(void);

#endif  // !REFEREE_RECEIVER_H__
