/**
 ******************************************************************************
 * @file    Relay.hpp
 * @brief   继电器开关封装（CubeMX 标签 Relay1 / Relay2 对应的 GPIO 输出）
 ******************************************************************************
 */
#ifndef _RELAY_HPP
#define _RELAY_HPP

#include "main.h"

/* 以下函数直接控制对应引脚输出电平：
 * On  = 输出高电平（GPIO_PIN_SET）
 * Off = 输出低电平（GPIO_PIN_RESET）
 * 继电器实际吸合极性取决于所接模块（高电平吸合 / 低电平吸合），
 * 接线时注意确认，避免上电默认电平误触发 */

void Relay1_On(void);
void Relay1_Off(void);
void Relay2_On(void);
void Relay2_Off(void);

#endif
