#include "CanReceiveTask.hpp"

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) // CAN1
{
    static CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_buff[8];
    HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rx_header, rx_buff);

    /* CAN1 当前未挂电机，收到帧直接丢弃 */
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan) // CAN2
{
    static CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_buff[8];
    HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO1, &rx_header, rx_buff);

    /*
     * 反馈帧 ID 由各电机对象自己报（RxId），电机身份仍然只在
     * DJI_Motor.cpp 的登记表设一遍；这里不做 switch/case，
     * 因为 RxId() 是运行期值，不能做 case 标签。
     */
    uint16_t rx_id = rx_header.StdId;
    if (rx_id == LF_Motor.RxId())
    {
        LF_Motor.GetInfo(rx_buff);
    }
    else if (rx_id == LB_Motor.RxId())
    {
        LB_Motor.GetInfo(rx_buff);
    }
    else if (rx_id == RF_Motor.RxId())
    {
        RF_Motor.GetInfo(rx_buff);
    }
    else if (rx_id == RB_Motor.RxId())
    {
        RB_Motor.GetInfo(rx_buff);
    }
}
