/**
 ******************************************************************************
 * @file    Servo.hpp
 * @brief   舵机驱动接口（TIM8_CH2 -> PI6，TIM8_CH3 -> PI7，50Hz PWM）
 *
 * 依赖的定时器配置（CubeMX 中已配好）：
 *   - TIM8 时钟 168MHz，Prescaler = 168-1  -> 计数频率 1MHz（1 计数 = 1us）
 *   - Period = 20000-1                     -> PWM 周期 20ms（50Hz）
 ******************************************************************************
 */
#ifndef SERVO_HPP
#define SERVO_HPP

#include <stdint.h>
#include "tim.h"

/* 定时器实例与通道（宏里已含 &，使用时不要再加 &） */
#define SERVO1_TIM (&htim8)
#define SERVO1_CHANNEL TIM_CHANNEL_2
#define SERVO2_TIM (&htim8)
#define SERVO2_CHANNEL TIM_CHANNEL_3

/* 舵机脉宽标定（us）。不同型号舵机行程可能不同，可按实测微调 */
#define SERVO_PULSE_MIN_US 500.0f  /* 0 度对应脉宽 */
#define SERVO_PULSE_MAX_US 2500.0f /* 180 度对应脉宽 */
#define SERVO_PULSE_MID_US 1500.0f /* 中位脉宽（360 度连续旋转舵机的停止点） */
#define SERVO_ANGLE_MAX 180.0f     /* 最大角度（度） */
#define SERVO_INIT_ANGLE 0.0f      /* 上电初始角度 */

#ifdef __cplusplus
extern "C"
{
#endif

  /* 舵机编号 */
  typedef enum
  {
    SERVO_1 = 0, /* PI6 / TIM8_CH2 */
    SERVO_2 = 1, /* PI7 / TIM8_CH3 */
    SERVO_NUM
  } Servo_Id_t;

  /**
   * @brief  初始化舵机：启动 PWM 并回到初始角度（在 MX_TIM8_Init 之后调用一次）
   */
  void Servo_Init(void);

  /**
   * @brief  启动 PWM 输出（舵机恢复保持力矩）
   */
  void Servo_Start(void);

  /**
   * @brief  停止 PWM 输出（舵机失去保持力矩，可自由转动）
   */
  void Servo_Stop(void);

  /**
   * @brief  直接按脉宽控制
   * @param  id: 舵机编号 SERVO_1 / SERVO_2
   * @param  pulse_us: 高电平脉宽，单位 us，自动限制在
   *         [SERVO_PULSE_MIN_US, SERVO_PULSE_MAX_US] 内
   * @note   若使用 360 度连续旋转舵机，中点 1500us 为停止，
   *         偏离中点的差值决定转速和方向
   */
  void Servo_SetPulseUs(Servo_Id_t id, float pulse_us);

  /**
   * @brief  按角度控制（0~180 度普通舵机）
   * @param  id: 舵机编号 SERVO_1 / SERVO_2
   * @param  angle: 目标角度，单位度，自动限制在 [0, SERVO_ANGLE_MAX]
   */
  void Servo_SetAngle(Servo_Id_t id, float angle);

  /**
   * @brief  获取最近一次设置的目标角度
   * @param  id: 舵机编号 SERVO_1 / SERVO_2
   * @retval 角度，单位度
   */
  float Servo_GetAngle(Servo_Id_t id);

#ifdef __cplusplus
}
#endif

#endif /* SERVO_HPP */
