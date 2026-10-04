/**
 ******************************************************************************
 * @file    Servo.cpp
 * @brief   舵机驱动实现（TIM8_CH2 -> PI6，TIM8_CH3 -> PI7，50Hz PWM）
 ******************************************************************************
 */
#include "Servo.hpp"

/* 各舵机对应的定时器实例与通道 */
static const struct
{
  TIM_HandleTypeDef *tim;
  uint32_t channel;
} s_servo_cfg[SERVO_NUM] = {
    {SERVO1_TIM, SERVO1_CHANNEL},
    {SERVO2_TIM, SERVO2_CHANNEL},
};

/* 每个舵机最近一次设定的目标角度 */
static float s_current_angle[SERVO_NUM] = {SERVO_INIT_ANGLE, SERVO_INIT_ANGLE};

static float Servo_Clampf(float v, float min, float max)
{
  if (v < min)
  {
    return min;
  }
  if (v > max)
  {
    return max;
  }
  return v;
}

/* 由角度换算成比较寄存器值（1 计数 = 1us，故 CCR 值 = 脉宽 us 数） */
static uint16_t Servo_AngleToPulse(float angle)
{
  angle = Servo_Clampf(angle, 0.0f, SERVO_ANGLE_MAX);
  float pulse = SERVO_PULSE_MIN_US +
                (SERVO_PULSE_MAX_US - SERVO_PULSE_MIN_US) * angle / SERVO_ANGLE_MAX;
  return (uint16_t)(pulse + 0.5f);
}

void Servo_Init(void)
{
  Servo_Start();
  Servo_SetAngle(SERVO_1, SERVO_INIT_ANGLE);
  Servo_SetAngle(SERVO_2, SERVO_INIT_ANGLE);
}

void Servo_Start(void)
{
  HAL_TIM_PWM_Start(SERVO1_TIM, SERVO1_CHANNEL);
  HAL_TIM_PWM_Start(SERVO2_TIM, SERVO2_CHANNEL);
}

void Servo_Stop(void)
{
  HAL_TIM_PWM_Stop(SERVO1_TIM, SERVO1_CHANNEL);
  HAL_TIM_PWM_Stop(SERVO2_TIM, SERVO2_CHANNEL);
}

void Servo_SetPulseUs(Servo_Id_t id, float pulse_us)
{
  if ((uint8_t)id >= SERVO_NUM)
  {
    return;
  }
  pulse_us = Servo_Clampf(pulse_us, SERVO_PULSE_MIN_US, SERVO_PULSE_MAX_US);
  /* 计数周期 20000us，脉宽不会溢出 ARR */
  __HAL_TIM_SET_COMPARE(s_servo_cfg[id].tim, s_servo_cfg[id].channel, (uint32_t)(pulse_us + 0.5f));
}

void Servo_SetAngle(Servo_Id_t id, float angle)
{
  if ((uint8_t)id >= SERVO_NUM)
  {
    return;
  }
  angle = Servo_Clampf(angle, 0.0f, SERVO_ANGLE_MAX);
  s_current_angle[id] = angle;
  __HAL_TIM_SET_COMPARE(s_servo_cfg[id].tim, s_servo_cfg[id].channel, Servo_AngleToPulse(angle));
}

float Servo_GetAngle(Servo_Id_t id)
{
  if ((uint8_t)id >= SERVO_NUM)
  {
    return 0.0f;
  }
  return s_current_angle[id];
}
