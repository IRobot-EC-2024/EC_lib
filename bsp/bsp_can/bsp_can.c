/**
 * @Author       : Specific-Cola specificcola@proton.me
 * @Date         : 2024-03-22 23:03:00
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-15 02:04:14
 * @Description  :
 * @Filename     : bsp_can.c
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#include "bsp_can.h"

#include <stdlib.h>
#include <string.h>

#include "main.h"

static Can_Device_t* can_devices[CAN_MX_REGISTER_CNT] = {NULL};
static uint8_t id_cnt;  // 全局CAN实例索引,每次有新的模块注册会自增

static void canOfflineCallback(Monitor_Device_t* monitor_device) {
    if (monitor_device == NULL || monitor_device->device == NULL) return;

    Can_Device_t* can_device = monitor_device->device;

    can_device->state = STATE_OFFLINE;
    if (can_device->can_device_offline_callback != NULL) {
        can_device->can_device_offline_callback(can_device);
    }
}

void canFilterConfig(Can_Device_t* device) {
    // todo:后面滤波器配置一下，保证can稳定传输
#if defined(CAN_DEVICE)

    CAN_FilterTypeDef can_filter_config;
    can_filter_config.FilterActivation = ENABLE;
    can_filter_config.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filter_config.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter_config.FilterIdHigh = 0x0000;
    can_filter_config.FilterIdLow = 0x0000;
    can_filter_config.FilterMaskIdHigh = 0x0000;
    can_filter_config.FilterMaskIdLow = 0x0000;
    can_filter_config.FilterBank = 0;
    can_filter_config.FilterFIFOAssignment = CAN_RX_FIFO0;
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_config);

    can_filter_config.SlaveStartFilterBank = 14;
    can_filter_config.FilterBank = 14;
    HAL_CAN_ConfigFilter(&hcan2, &can_filter_config);

#elif defined(FDCAN_DEVICE)

    FDCAN_FilterTypeDef can_filter_config;
    if (device->can_handle == &hfdcan1)
        can_filter_config.FilterIndex = 0;  // 滤波器索引
    else if (device->can_handle == &hfdcan2)
        can_filter_config.FilterIndex = 1;  // 滤波器索引
    else if (device->can_handle == &hfdcan3)
        can_filter_config.FilterIndex = 2;  // 滤波器索引

    can_filter_config.IdType = FDCAN_STANDARD_ID;  // 标准ID
    can_filter_config.FilterType = FDCAN_FILTER_MASK;
    can_filter_config.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;  // 过滤器0关联到FIFO0
    can_filter_config.FilterID1 = 0;                           // 接收filter
    can_filter_config.FilterID2 = 0;                           // 接收mask

    HAL_FDCAN_ConfigFilter(device->can_handle, &can_filter_config);
    // HAL_FDCAN_ConfigFifoWatermark(device->can_handle, FDCAN_CFG_RX_FIFO0, 1);

#endif
}

Can_Device_t* canDeviceRegister(Can_Register_t* reg) {
    if (!id_cnt) {
        canOnInit();
    }
    if (id_cnt > CAN_MX_REGISTER_CNT) {
        Error_Handler();  // 后面希望定义一个全局变量来展示错误类型
    }

    for (uint8_t i = 0; i < id_cnt; i++) {
        if (can_devices[i]->rx_id == reg->rx_id && can_devices[i]->can_handle == reg->can_handle &&
            can_devices[i]->tx_id == reg->tx_id) {
            Error_Handler();
        }
    }
    canOnDeactivate();

    Can_Device_t* instance = (Can_Device_t*)malloc(sizeof(Can_Device_t));  // 分配空间
    memset(instance, 0, sizeof(Can_Device_t));  // 分配的空间未必是0,所以要先清空

    // 进行发送报文的配置
#if defined(CAN_DEVICE)
    instance->tx_config.StdId = reg->tx_id;  // 发送id
    instance->tx_config.IDE = CAN_ID_STD;    // 使用标准id,扩展id则使用CAN_ID_EXT(目前没有需求)
    instance->tx_config.RTR = CAN_RTR_DATA;  // 发送数据帧
    instance->tx_config.DLC = reg->tx_dlc;   // 默认发送长度为8
#elif defined(FDCAN_DEVICE)
    instance->tx_config.Identifier = reg->tx_id;                  // 发送id
    instance->tx_config.IdType = FDCAN_STANDARD_ID;               // 使用标准id
    instance->tx_config.FDFormat = FDCAN_CLASSIC_CAN;             // 普通CAN格式
    instance->tx_config.DataLength = reg->tx_dlc << 16;           // 发送数据长度
    instance->tx_config.ErrorStateIndicator = FDCAN_ESI_ACTIVE;   // 设置错误状态指示
    instance->tx_config.BitRateSwitch = FDCAN_BRS_OFF;            // 不开启可变波特率
    instance->tx_config.TxEventFifoControl = FDCAN_NO_TX_EVENTS;  // 用于发送事件FIFO控制, 不存储
    instance->tx_config.MessageMarker = 0x00;  // 用于复制到TX EVENT FIFO的消息Maker来识别消息状态，范围0到0xFF
#endif

    // 设置回调函数和接收发送id
    instance->can_handle = reg->can_handle;
    instance->tx_id = reg->tx_id;  // 好像没用,可以删掉
    instance->rx_id = reg->rx_id;
    instance->can_device_callback = reg->can_device_callback;
    instance->can_device_offline_callback = reg->can_device_offline_callback;

    instance->parent = reg->parent;

    Monitor_Register_t monitor_reg;
    monitor_reg.device = instance;
    monitor_reg.offlineCallback = canOfflineCallback;
    monitor_reg.offline_threshold = reg->offline_threshold;
    instance->monitor_handle = monitorInit(&monitor_reg);

    canFilterConfig(instance);         // 添加CAN过滤器规则
    can_devices[id_cnt++] = instance;  // 将实例保存到can_instance中

    canOnActivate();

    return instance;  // 返回can实例指针
}

void canOnInit(void) {
#if defined(CAN_DEVICE)
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
#elif defined(FDCAN_DEVICE)
    HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_REJECT, DISABLE, DISABLE);
    HAL_FDCAN_ConfigGlobalFilter(&hfdcan2, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_REJECT, DISABLE, DISABLE);
    HAL_FDCAN_ConfigGlobalFilter(&hfdcan3, FDCAN_ACCEPT_IN_RX_FIFO0, FDCAN_REJECT, DISABLE, DISABLE);
    HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
    HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
    HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
#endif
}

void canOnActivate(void) {
#if defined(CAN_DEVICE)
    HAL_CAN_Start(&hcan1);
    HAL_CAN_Start(&hcan2);
#elif defined(FDCAN_DEVICE)
    HAL_FDCAN_Start(&hfdcan1);  // 开启FDCAN
    HAL_FDCAN_Start(&hfdcan2);
    HAL_FDCAN_Start(&hfdcan3);
#endif
}

void canOnDeactivate(void) {
#if defined(CAN_DEVICE)
    HAL_CAN_Stop(&hcan1);
    HAL_CAN_Stop(&hcan2);
#elif defined(FDCAN_DEVICE)
    HAL_FDCAN_Stop(&hfdcan1);  // 开启FDCAN
    HAL_FDCAN_Stop(&hfdcan2);
    HAL_FDCAN_Stop(&hfdcan3);
#endif
}

Return_t canSendMessage(Can_Device_t* instance, uint8_t* message) {
#if defined(CAN_DEVICE)
    memcpy(instance->tx_buff, message, instance->tx_config.DLC);
    if (HAL_CAN_AddTxMessage(instance->can_handle, &instance->tx_config, message, &instance->tx_mailbox) == HAL_ERROR)
        return RETURN_ERROR;
    return RETURN_SUCCESS;
#elif defined(FDCAN_DEVICE)
    memcpy(instance->tx_buff, message, instance->tx_config.DataLength >> 16);
    if (HAL_FDCAN_AddMessageToTxFifoQ(instance->can_handle, &instance->tx_config, message) == HAL_ERROR)
        return RETURN_ERROR;
    return RETURN_SUCCESS;
#endif
}

#if defined(CAN_DEVICE)
static void canReceiveMessage(CAN_HandleTypeDef* hcan) {
    static CAN_RxHeaderTypeDef rx_config;
    static uint8_t can_rx_buff[8];

    // FIFO不为空,有可能在其他中断时有多帧数据进入
    while (HAL_CAN_GetRxFifoFillLevel(hcan, CAN_RX_FIFO0)) {
        // 从FIFO中获取数据
        HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_config, can_rx_buff);

        // 两者相等说明这是要找的实例
        for (uint8_t i = 0; i < id_cnt; i++) {
            if (hcan == can_devices[i]->can_handle && rx_config.StdId == can_devices[i]->rx_id) {
                can_devices[i]->state = STATE_ONLINE;
                monitorRefresh(can_devices[i]->monitor_handle);

                // 回调函数不为空就调用
                if (can_devices[i]->can_device_callback != NULL) {
                    // 保存接收到的数据长度
                    can_devices[i]->rx_len = rx_config.DLC;
                    // 消息拷贝到对应实例
                    memcpy(can_devices[i]->rx_buff, can_rx_buff, can_devices[i]->rx_len);
                    // 触发回调进行数据解析和处理
                    can_devices[i]->can_device_callback(can_devices[i]);
                }

                monitorRefresh(can_devices[i]->monitor_handle);
                can_devices[i]->state = STATE_ONLINE;
                break;
            }
        }
    }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) { canReceiveMessage(hcan); }

#elif defined(FDCAN_DEVICE)
static void canReceiveMessage(FDCAN_HandleTypeDef* hfdcan) {
    static FDCAN_RxHeaderTypeDef rx_config;
    static uint8_t can_rx_buff[8];
    while (HAL_FDCAN_GetRxFifoFillLevel(hfdcan, FDCAN_RX_FIFO0))  // FIFO不为空,有可能在其他中断时有多帧数据进入
    {
        HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rx_config,
                               can_rx_buff);    // 从FIFO中获取数据
        for (uint8_t i = 0; i < id_cnt; i++) {  // 两者相等说明这是要找的实例
            if (hfdcan == can_devices[i]->can_handle && rx_config.Identifier == can_devices[i]->rx_id) {
                can_devices[i]->state = STATE_ONLINE;
                monitorRefresh(can_devices[i]->monitor_handle);

                // 回调函数不为空就调用
                if (can_devices[i]->can_device_callback != NULL) {
                    // 保存接收到的数据长度
                    can_devices[i]->rx_len = rx_config.DataLength >> 16;
                    // 消息拷贝到对应实例
                    memcpy(can_devices[i]->rx_buff, can_rx_buff, can_devices[i]->rx_len);
                    // 触发回调进行数据解析和处理
                    can_devices[i]->can_device_callback(can_devices[i]);
                }

                monitorRefresh(can_devices[i]->monitor_handle);
                can_devices[i]->state = STATE_ONLINE;
                break;
            }
        }
    }
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef* hfdcan, uint32_t RxFifo0ITs) {
    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET) {
        canReceiveMessage(hfdcan);
    }
}
#endif
