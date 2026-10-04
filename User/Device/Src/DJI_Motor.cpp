/**
 ******************************************************************************
 * @file    DJI_Motor.cpp
 * @brief   大疆电机（GM6020 / M3508）驱动实现
 ******************************************************************************
 */
#include "DJI_Motor.hpp"

/* 每帧最多 4 台电机，每台占 2 字节（大端）：[id1_H,id1_L,id2_H,id2_L,...] */
static const uint8_t MOTOR_NUM_PER_FRAME = 4U;

/* 电流指令发送缓存（各型号一帧，上电全 0 = 不输出） */
static uint8_t GM6020_Current[8];
static uint8_t M3508_Current[8];

// 全局电机对象定义
DJIMotor LF_Motor;
DJIMotor LB_Motor;
DJIMotor RF_Motor;
DJIMotor RB_Motor;

void DJIMotor::GetInfo(uint8_t *rx_buff)
{
    last_encoder = encoder;

    encoder = (rx_buff[0] << 8) | rx_buff[1];
    speed = (rx_buff[2] << 8) | rx_buff[3];
    current = (rx_buff[4] << 8) | rx_buff[5];
    temperature = rx_buff[6]; /* rx_buff[7] 为保留字节 */

    /*
     * 过零换圈：encoder/last_encoder 为 uint16_t，相减提升为 int，
     * 结果范围 -65535~65535。正转跨 8191->0 时差值约 -8191，
     * 反转跨 0->8191 时差值约 +8191，以半圈 4096 为阈值判方向。
     */
    if (encoder - last_encoder < -4096)
        circle_number++;
    else if (encoder - last_encoder > 4096)
        circle_number--;

    accumulate_angle = (float)(circle_number * 8192 + encoder) / 8192.0f * 360.0f;
}

void DJIMotor::SetCurrent(MotorModel model, uint8_t id, int16_t cmd_current)
{
    if (id < 1U || id > MOTOR_NUM_PER_FRAME)
    {
        return; /* id 超出一帧容量，写入会越界，直接忽略 */
    }

    uint8_t index = (id - 1U) * 2U;

    if (model == MotorModel::GM6020)
    {
        GM6020_Current[index] = cmd_current >> 8;
        GM6020_Current[index + 1] = cmd_current & 0xFF;
    }
    else if (model == MotorModel::M3508)
    {
        M3508_Current[index] = cmd_current >> 8;
        M3508_Current[index + 1] = cmd_current & 0xFF;
    }
}

void DJIMotor::StartMotor(MotorModel model, CAN_HandleTypeDef *phcan)
{
    if (model == MotorModel::GM6020)
    {
        CANSend(phcan, GM6020_TX_ID, GM6020_Current, 8);
    }
    else if (model == MotorModel::M3508)
    {
        CANSend(phcan, M3508_TX_ID, M3508_Current, 8);
    }
}
