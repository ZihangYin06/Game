/**
 ******************************************************************************
 * @file    DJI_Motor.hpp
 * @brief   大疆电机（GM6020 / M3508）驱动：CAN 反馈解析 + 电流指令发送
 *
 * 发送模型说明（重要）：
 *   同一型号电机的电流指令共用一帧 CAN（8 字节，每台电机占 2 字节大端），
 *   存放在 .cpp 内的全局发送缓存中。SetCurrent() 只是把当前对象的指令
 *   写入缓存中 id 对应的槽位，StartMotor() 把整帧缓存发出——
 *   由哪个电机对象调用二者效果相同，缓存按 id 索引而非按对象区分。
 ******************************************************************************
 */
#ifndef DJI_MOTOR_HPP_
#define DJI_MOTOR_HPP_

#include <stdint.h>
#include "bsp_can.h"
#include "define.h"

/* 电机型号：决定电流指令帧的 CAN ID 与协议 */
enum class MotorModel : uint8_t
{
    GM6020,
    M3508
};

struct DJIMotor
{
    /* ---- 反馈数据（由 GetInfo 解析 CAN 反馈帧更新） ---- */
    uint16_t encoder = 0;       /* 机械角度原始值 0~8191（一圈 8192） */
    int16_t speed = 0;          /* 转速 rpm */
    int16_t current = 0;        /* 实际转矩电流反馈 */
    uint8_t temperature = 0;    /* 电机温度 ℃ */

    /* ---- 多圈角度累计 ---- */
    uint16_t last_encoder = 0;      /* 上一拍机械角度，用于过零检测 */
    int32_t circle_number = 0;      /* 累计圈数，正转为正、反转为负 */
    float accumulate_angle = 0.0f;  /* 多圈累计角度（度），可超出 0~360、可为负 */

    /**
     * @brief  解析 8 字节 CAN 反馈帧，更新本对象全部反馈字段
     * @param  rx_buff: 反馈帧数据（GM6020 为 0x205+id-1，M3508 为 0x201+id-1）
     * @note   过零换圈假设相邻两拍角度变化小于半圈（控制周期足够短）
     */
    void GetInfo(uint8_t *rx_buff);

    /**
     * @brief  将电流指令写入对应型号发送缓存中 id 所在的槽位
     * @param  model: 电机型号
     * @param  id: 总线上电机编号 1~4（超出范围直接忽略，防止越界）
     * @param  current: 电流指令（M3508 范围 -16384~16384）
     */
    void SetCurrent(MotorModel model, uint8_t id, int16_t current);

    /**
     * @brief  将对应型号的整帧电流缓存作为一帧 CAN 发送
     * @param  model: 电机型号
     * @param  phcan: 目标总线（如 &hcan2，见 define.h）
     * @note   需先对所有电机调用 SetCurrent 再调用本函数，
     *         否则未更新的槽位会把旧值/0 发出去
     */
    void StartMotor(MotorModel model, CAN_HandleTypeDef *phcan);
};

// 全局电机对象声明（定义在 .cpp 中）
extern DJIMotor LF_Motor;
extern DJIMotor LB_Motor;
extern DJIMotor RF_Motor;
extern DJIMotor RB_Motor;

#endif
