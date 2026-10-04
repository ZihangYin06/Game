/**
 ******************************************************************************
 * @file    Relay.cpp
 * @brief   继电器开关封装实现（GPIO 输出控制）
 ******************************************************************************
 */
#include "Relay.hpp"

/* Relay1：CubeMX 标签 Relay1_Pin / Relay1_GPIO_Port */
void Relay1_On(void)
{
    HAL_GPIO_WritePin(Relay1_GPIO_Port, Relay1_Pin, GPIO_PIN_SET);
}

void Relay1_Off(void)
{
    HAL_GPIO_WritePin(Relay1_GPIO_Port, Relay1_Pin, GPIO_PIN_RESET);
}

/* Relay2：CubeMX 标签 Relay2_Pin / Relay2_GPIO_Port */
void Relay2_On(void)
{
    HAL_GPIO_WritePin(Relay2_GPIO_Port, Relay2_Pin, GPIO_PIN_SET);
}

void Relay2_Off(void)
{
    HAL_GPIO_WritePin(Relay2_GPIO_Port, Relay2_Pin, GPIO_PIN_RESET);
}
