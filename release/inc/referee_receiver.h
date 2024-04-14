#ifndef REFEREE_RECEIVER_H__
#define REFEREE_RECEIVER_H__

#include "bsp_usart.h"
#include "fifo.h"
#include "referee_info.h"

typedef struct{
	game_state_t game_state;									//0x0001
	game_result_t game_result;									//0x0002
	game_robot_HP_t game_robot_HP;								//0x0003

	event_data_t event_data;									//0x0101
	ext_supply_projectile_action_t supply_projectile_action;	//0x0102
	referee_warning_t referee_warning;							//0x0104
	dart_info_t dart_info;										//0x0105
	
	robot_status_t robot_status;								//0x0201
	power_heat_data_t power_heat_data;							//0x0202
	robot_pos_t robot_pos;										//0x0203
	buff_t buff;												//0x0204
	air_support_data_t air_support_data;						//0x0205
	hurt_data_t hurt_data;										//0x0206
	shoot_data_t shoot_data;									//0x0207
	projectile_allowance_t projectile_allowance;				//0x0208
	rfid_status_t rfid_status;									//0x0209
	dart_client_cmd_t dart_client_cmd;							//0x020A
	ground_robot_position_t ground_robot_position;				//0x020B
	radar_mark_data_t radar_mark_data;							//0x020C
	sentry_info_t sentry_info;									//0x020D
	radar_info_t radar_info;									//0x020E
	
	robot_interaction_data_t robot_interaction_data;			//0x0301
	custom_robot_data_t custom_robot_data;						//0x0302:图传
	map_command_t map_command;									//0x0303
	remote_control_t remote_control;							//0x0304:图传
	map_robot_data_t map_robot_data;							//0x0305
	custom_client_data_t custom_client_data;					//0x0306
	map_data_t map_data;										//0x0307
	custom_info_t custom_info;									//0x0308
	
}Referee_info_t;

typedef struct{
	uint8_t status[4][16];
	uint32_t offline_counter[4][16];
	Usart_Device_t *usart_info;
	Usart_Device_t *vision_info;
	fifo_s_t referee_fifo;
	frame_header_struct_t referee_header;
	Referee_info_t referee_info;
}Referee_Receiver_t;

Referee_Receiver_t *refereeReceiverAdd(UART_HandleTypeDef *huart1,UART_HandleTypeDef *huart2);
void referee_data_solve(uint8_t *frame);   
Referee_Receiver_t *refereeReceiverGet(void);

void referee_status_updata(void);

#endif // !REFEREE_RECEIVER_H__
