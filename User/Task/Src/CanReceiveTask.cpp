#include "CanReceiveTask.hpp"

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) // CAN1
{
    static CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_buff[8];
    HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rx_header, rx_buff);
    switch (rx_header.StdId)
    {
    default:
        break;
    }
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan) // CAN2
{
    static CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_buff[8];
    HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO1, &rx_header, rx_buff);
    switch (rx_header.StdId)
    {
    default:
        break;
    }
}