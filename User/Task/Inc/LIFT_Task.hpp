#ifndef _LIFT_TASK_HPP
#define _LIFT_TASK_HPP

#include "Relay.hpp"
#include "DJI_Motor.hpp"
#include "PID.hpp"
#include "define.h"

void LIFT_Init(void);
bool Chassis_High(void);
bool Chassis_Low(void);
void LIFT_Standby(void);

#endif
