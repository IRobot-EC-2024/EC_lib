#include "referee.h"

#define REFEREE_FIFO_BUF_LENGTH 1024

static Referee_Receiver_t *referee_instance;

uint8_t referee_fifo_buf[REFEREE_FIFO_BUF_LENGTH];

//裁判系统通信接收
static void refereeReceiverCallback(Usart_Device_t *usart)
{
	fifo_s_puts(&referee_instance->referee_fifo, (char*)usart->rx_buff2[usart->rx_info.rx_buff_select], usart->rx_info.this_time_rx_len);
}

Referee_Receiver_t *refereeReceiverAdd(UART_HandleTypeDef *huart1,UART_HandleTypeDef *huart2)
{
    Referee_Receiver_t *receiver = (Referee_Receiver_t*)malloc(sizeof(Referee_Receiver_t));
    Usart_Register_t usart_reg;
    memset(receiver,0,sizeof(Referee_Receiver_t));
    usart_reg.usart_handle = huart1;
    usart_reg.rx_buff_num = 1;
    usart_reg.rx_len = 256;
    usart_reg.usart_device_callback = refereeReceiverCallback;
    receiver->usart_info = usartDeviceRegister(&usart_reg);
	
	
    memset(receiver,0,sizeof(Referee_Receiver_t));
    usart_reg.usart_handle = huart2;
    usart_reg.rx_buff_num = 1;
    usart_reg.rx_len = 256;
    usart_reg.usart_device_callback = refereeReceiverCallback;
    receiver->vision_info = usartDeviceRegister(&usart_reg);
	
	
    fifo_s_init(&receiver->referee_fifo, referee_fifo_buf, REFEREE_FIFO_BUF_LENGTH);
	
	referee_instance = receiver;
    return receiver;

}

Referee_Receiver_t *refereeReceiverGet(){
	return referee_instance;
}

void referee_data_solve(uint8_t *frame)
{
    uint16_t cmd_id = 0;

    uint8_t index = 0;

    memcpy(&referee_instance->referee_header, frame, sizeof(frame_header_struct_t));

    index += sizeof(frame_header_struct_t);

    memcpy(&cmd_id, frame + index, sizeof(uint16_t));
    index += sizeof(uint16_t);
	
	referee_instance->status[cmd_id>>8][cmd_id&0x0f] = 1;
	referee_instance->offline_counter[cmd_id>>8][cmd_id&0x0f] = 0;
	
    switch (cmd_id)
    {
        case GAME_STATE_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.game_state, frame + index, sizeof(game_state_t));
//						EnQueue(&SendBuffer[0], send_game_status(),11);
        }
        break;
        case GAME_RESULT_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.game_result, frame + index, sizeof(game_result_t));
        }
        break;
        case GAME_ROBOT_HP_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.game_robot_HP, frame + index, sizeof(game_robot_HP_t));
//						EnQueue(&SendBuffer[1], send_enemy_information(),11);
        }
        break;
        case EVENT_DATA_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.event_data, frame + index, sizeof(event_data_t));
        }
        break;
        case SUPPLY_PROJECTILE_ACTION_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.supply_projectile_action, frame + index, sizeof(ext_supply_projectile_action_t));
        }
        break;
        case REFEREE_WARNING_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.referee_warning, frame + index, sizeof(referee_warning_t));
        }
        break;
		case DART_INFO_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.dart_info, frame + index, sizeof(dart_info_t));
        }
        break;

        case ROBOT_STATE_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.robot_status, frame + index, sizeof(robot_status_t));
//						EnQueue(&SendBuffer[1], send_bullet_limit(),33);
//						EnQueue(&SendBuffer[1], send_robot_information(),11);
        }
        break;
        case POWER_HEAT_DATA_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.power_heat_data, frame + index, sizeof(power_heat_data_t));
//						EnQueue(&SendBuffer[0], send_power_heat_data(),22);
        }
        break;
        case ROBOT_POS_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.robot_pos, frame + index, sizeof(robot_pos_t));
        }
        break;
        case BUFF_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.buff, frame + index, sizeof(buff_t));
        }
        break;
        case AIR_SUPPORT_DATA_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.air_support_data, frame + index, sizeof(air_support_data_t));
        }
        break;
        case HURT_DATA_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.hurt_data, frame + index, sizeof(hurt_data_t));
        }
        break;
        case SHOOT_DATA_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.shoot_data, frame + index, sizeof(shoot_data_t));
//						EnQueue(&SendBuffer[0], send_bullet_speed(),11);
        }
        break;
        case PROJECTILE_ALLOWANCE_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.projectile_allowance, frame + index, sizeof(projectile_allowance_t));
        }
        break;
		case RFID_STATUS_CMD_ID:
		{
			memcpy(&referee_instance->referee_info.rfid_status, frame + index, sizeof(rfid_status_t));
		}
		break;
		case DART_CLIENT_CMD_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.dart_client_cmd, frame + index, sizeof(dart_client_cmd_t));
        }
        break;
		case GROUND_ROBOT_POSITION_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.ground_robot_position, frame + index, sizeof(ground_robot_position_t));
        }
        break;
		case RADAR_MARK_DATA_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.radar_mark_data, frame + index, sizeof(radar_mark_data_t));
        }
        break;
		case SENTRY_INFO_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.sentry_info, frame + index, sizeof(sentry_info_t));
        }
        break;
		case RADAR_INFO_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.radar_info, frame + index, sizeof(radar_info_t));
        }
        break;
		case ROBOT_INTERACTION_DATA_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.robot_interaction_data, frame + index, sizeof(robot_interaction_data_t));
        }
        break;
		case CUSTOM_ROBOT_DATA_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.custom_robot_data, frame + index, sizeof(custom_robot_data_t));
        }
        break;
		case MAP_COMMAND_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.map_command, frame + index, sizeof(map_command_t));
        }
        break;
		case REMOTE_CONTROL_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.remote_control, frame + index, sizeof(remote_control_t));
        }
        break;
		case MAP_ROBOT_DATA_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.map_robot_data, frame + index, sizeof(map_robot_data_t));
        }
        break;
		case MAP_DATA_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.map_data, frame + index, sizeof(map_data_t));
        }
        break;
		case CUSTOM_INFO_CMD_ID:
        {
            memcpy(&referee_instance->referee_info.custom_info, frame + index, sizeof(custom_info_t));
        }
        break;
        default:
        {
            break;
        }
    }
}


//裁判系统通信发送

void referee_status_updata(void){
	uint8_t i=0,j=0;
	
	for(i=0;i<4;i++){
		for(j=0;j<16;j++){
			if(referee_instance->status[i][j]){
				referee_instance->offline_counter[i][j]++;
				if(referee_instance->offline_counter[i][j]>1000){
					referee_instance->status[i][j]=0;
				}
			}
		}
	}
}
