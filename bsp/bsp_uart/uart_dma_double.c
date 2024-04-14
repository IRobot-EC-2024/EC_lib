/**
 * @Author       : H0pefu12 573341043@qq.com
 * @Date         : 2024-04-08 12:12:57
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-08 14:53:53
 * @Description  :
 * @Filename     : uart_dma_double.c
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#include "uart_dma_double.h"

#if defined(STM32H723xx)
/**
 * @brief  End ongoing Rx transfer on UART peripheral (following error detection
 * or Reception completion).
 * @param  huart UART handle.
 * @retval None
 */
static void UART_EndRxTransfer(UART_HandleTypeDef* huart) {
    /* Disable RXNE, PE and ERR (Frame error, noise error, overrun error)
     * interrupts */
    ATOMIC_CLEAR_BIT(huart->Instance->CR1,
                     (USART_CR1_RXNEIE_RXFNEIE | USART_CR1_PEIE));
    ATOMIC_CLEAR_BIT(huart->Instance->CR3, (USART_CR3_EIE | USART_CR3_RXFTIE));

    /* In case of reception waiting for IDLE event, disable also the IDLE IE
     * interrupt source */
    if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE) {
        ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);
    }

    /* At end of Rx process, restore huart->RxState to Ready */
    huart->RxState = HAL_UART_STATE_READY;
    huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

    /* Reset RxIsr function pointer */
    huart->RxISR = NULL;
}

/**
 * @brief  End ongoing Tx transfer on UART peripheral (following error detection
 * or Transmit completion).
 * @param  huart UART handle.
 * @retval None
 */
static void UART_EndTxTransfer(UART_HandleTypeDef* huart) {
    /* Disable TXEIE, TCIE, TXFT interrupts */
    ATOMIC_CLEAR_BIT(huart->Instance->CR1,
                     (USART_CR1_TXEIE_TXFNFIE | USART_CR1_TCIE));
    ATOMIC_CLEAR_BIT(huart->Instance->CR3, (USART_CR3_TXFTIE));

    /* At end of Tx process, restore huart->gState to Ready */
    huart->gState = HAL_UART_STATE_READY;
}

/**
 * @brief DMA UART receive process complete callback.
 * @param hdma DMA handle.
 * @retval None
 */
static void UART_DMAReceiveCplt(DMA_HandleTypeDef* hdma) {
    UART_HandleTypeDef* huart = (UART_HandleTypeDef*)(hdma->Parent);

    /* DMA Normal mode */
    if (hdma->Init.Mode != DMA_CIRCULAR) {
        huart->RxXferCount = 0U;

        /* Disable PE and ERR (Frame error, noise error, overrun error)
         * interrupts */
        ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_PEIE);
        ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

        /* Disable the DMA transfer for the receiver request by resetting the
           DMAR bit in the UART CR3 register */
        ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAR);

        /* At end of Rx process, restore huart->RxState to Ready */
        huart->RxState = HAL_UART_STATE_READY;

        /* If Reception till IDLE event has been selected, Disable IDLE
         * Interrupt */
        if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE) {
            ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);
        }
    }

    /* Initialize type of RxEvent that correspond to RxEvent callback execution;
       In this case, Rx Event type is Transfer Complete */
    huart->RxEventType = HAL_UART_RXEVENT_TC;

    /* Check current reception Mode :
       If Reception till IDLE event has been selected : use Rx Event callback */
    if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE) {
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
        /*Call registered Rx Event callback*/
        huart->RxEventCallback(huart, huart->RxXferSize);
#else
        /*Call legacy weak Rx Event callback*/
        HAL_UARTEx_RxEventCallback(huart, huart->RxXferSize);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
    } else {
        /* In other cases : use Rx Complete callback */
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
        /*Call registered Rx complete callback*/
        huart->RxCpltCallback(huart);
#else
        /*Call legacy weak Rx complete callback*/
        HAL_UART_RxCpltCallback(huart);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
    }
}

/**
 * @brief DMA UART receive process half complete callback.
 * @param hdma DMA handle.
 * @retval None
 */
static void UART_DMARxHalfCplt(DMA_HandleTypeDef* hdma) {
    UART_HandleTypeDef* huart = (UART_HandleTypeDef*)(hdma->Parent);

    /* Initialize type of RxEvent that correspond to RxEvent callback execution;
       In this case, Rx Event type is Half Transfer */
    huart->RxEventType = HAL_UART_RXEVENT_HT;

    /* Check current reception Mode :
       If Reception till IDLE event has been selected : use Rx Event callback */
    if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE) {
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
        /*Call registered Rx Event callback*/
        huart->RxEventCallback(huart, huart->RxXferSize / 2U);
#else
        /*Call legacy weak Rx Event callback*/
        HAL_UARTEx_RxEventCallback(huart, huart->RxXferSize / 2U);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
    } else {
        /* In other cases : use Rx Half Complete callback */
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
        /*Call registered Rx Half complete callback*/
        huart->RxHalfCpltCallback(huart);
#else
        /*Call legacy weak Rx Half complete callback*/
        HAL_UART_RxHalfCpltCallback(huart);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
    }
}

/**
 * @brief DMA UART communication error callback.
 * @param hdma DMA handle.
 * @retval None
 */
static void UART_DMAError(DMA_HandleTypeDef* hdma) {
    UART_HandleTypeDef* huart = (UART_HandleTypeDef*)(hdma->Parent);

    const HAL_UART_StateTypeDef gstate = huart->gState;
    const HAL_UART_StateTypeDef rxstate = huart->RxState;

    /* Stop UART DMA Tx request if ongoing */
    if ((HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAT)) &&
        (gstate == HAL_UART_STATE_BUSY_TX)) {
        huart->TxXferCount = 0U;
        UART_EndTxTransfer(huart);
    }

    /* Stop UART DMA Rx request if ongoing */
    if ((HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR)) &&
        (rxstate == HAL_UART_STATE_BUSY_RX)) {
        huart->RxXferCount = 0U;
        UART_EndRxTransfer(huart);
    }

    huart->ErrorCode |= HAL_UART_ERROR_DMA;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    /*Call registered error callback*/
    huart->ErrorCallback(huart);
#else
    /*Call legacy weak error callback*/
    HAL_UART_ErrorCallback(huart);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
}

/**
 * @brief  模仿hal库实现开始DMA双缓冲区接受
 * @note   This function could be called by all HAL UART API providing reception
 * in DMA mode.
 * @note   When calling this function, parameters validity is considered as
 * already checked, i.e. Rx State, buffer address, ... UART Handle is assumed as
 * Locked.
 * @param  huart UART handle.
 * @param  pData Pointer to data buffer (u8 or u16 data elements).
 * @param  Size  Amount of data elements (u8 or u16) to be received.
 * @retval HAL status
 */
HAL_StatusTypeDef UART_Start_Receive_DMA_double(UART_HandleTypeDef* huart,
                                                uint8_t* pData, uint8_t* pData1,
                                                uint16_t Size) {
    huart->pRxBuffPtr = pData;
    huart->RxXferSize = Size;

    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->RxState = HAL_UART_STATE_BUSY_RX;

    if (huart->hdmarx != NULL) {
        /* Set the UART DMA transfer complete callback */
        huart->hdmarx->XferCpltCallback = UART_DMAReceiveCplt;
        huart->hdmarx->XferM1CpltCallback = UART_DMAReceiveCplt;

        /* Set the UART DMA Half transfer complete callback */
        huart->hdmarx->XferHalfCpltCallback = UART_DMARxHalfCplt;
        huart->hdmarx->XferM1HalfCpltCallback = UART_DMARxHalfCplt;

        /* Set the DMA error callback */
        huart->hdmarx->XferErrorCallback = UART_DMAError;

        /* Set the DMA abort callback */
        huart->hdmarx->XferAbortCallback = NULL;

        /* Enable the DMA channel */
        if (HAL_DMAEx_MultiBufferStart_IT(
                huart->hdmarx, (uint32_t)&huart->Instance->RDR, (uint32_t)pData,
                (uint32_t)pData1, Size) != HAL_OK) {
            /* Set error code to DMA */
            huart->ErrorCode = HAL_UART_ERROR_DMA;

            /* Restore huart->RxState to ready */
            huart->RxState = HAL_UART_STATE_READY;

            return HAL_ERROR;
        }
    }

    /* Enable the UART Parity Error Interrupt */
    if (huart->Init.Parity != UART_PARITY_NONE) {
        ATOMIC_SET_BIT(huart->Instance->CR1, USART_CR1_PEIE);
    }

    /* Enable the UART Error Interrupt: (Frame error, noise error, overrun
     * error) */
    ATOMIC_SET_BIT(huart->Instance->CR3, USART_CR3_EIE);

    /* Enable the DMA transfer for the receiver request by setting the DMAR bit
    in the UART CR3 register */
    ATOMIC_SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);

    return HAL_OK;
}

/**
 * @brief 模仿hal库实现使用DMA双缓冲区接受，并开启空闲中断
 * @param huart UART handle.
 * @param pData Pointer to data buffer (uint8_t or uint16_t data elements).
 * @param Size  Amount of data elements (uint8_t or uint16_t) to be received.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_DMA_double(UART_HandleTypeDef* huart,
                                                      uint8_t* pData,
                                                      uint8_t* pData1,
                                                      uint16_t Size) {
    HAL_StatusTypeDef status;

    /* Check that a Rx process is not already ongoing */
    if (huart->RxState == HAL_UART_STATE_READY) {
        if ((pData == NULL) || (Size == 0U)) {
            return HAL_ERROR;
        }

        /* Set Reception type to reception till IDLE Event*/
        huart->ReceptionType = HAL_UART_RECEPTION_TOIDLE;
        huart->RxEventType = HAL_UART_RXEVENT_TC;

        status = UART_Start_Receive_DMA_double(huart, pData, pData1, Size);

        /* Check Rx process has been successfully started */
        if (status == HAL_OK) {
            if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE) {
                __HAL_UART_CLEAR_FLAG(huart, UART_CLEAR_IDLEF);
                ATOMIC_SET_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);
            } else {
                /* In case of errors already pending when reception is started,
                   Interrupts may have already been raised and lead to reception
                   abortion. (Overrun error for instance). In such case
                   Reception Type has been reset to HAL_UART_RECEPTION_STANDARD.
                 */
                status = HAL_ERROR;
            }
        }

        return status;
    } else {
        return HAL_BUSY;
    }
}
#elif defined(STM32F427xx) || defined(STM32F407xx)
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_DMA_double(UART_HandleTypeDef* huart,
                                                      uint8_t* pData,
                                                      uint8_t* pData1,
                                                      uint16_t Size) {
    return HAL_ERROR;
}
#endif
