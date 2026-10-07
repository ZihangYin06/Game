#include "LIFT_Task.hpp"

void LIFT_Init(void)
{
    LF_Motor.angle_pid.SetParams(0, 0, 0, 0, 0);
    LF_Motor.speed_pid.SetParams(0, 0, 0, 0, 0);
    LB_Motor.angle_pid.SetParams(0, 0, 0, 0, 0);
    LB_Motor.speed_pid.SetParams(0, 0, 0, 0, 0);
    RF_Motor.angle_pid.SetParams(0, 0, 0, 0, 0);
    RF_Motor.speed_pid.SetParams(0, 0, 0, 0, 0);
    RB_Motor.angle_pid.SetParams(0, 0, 0, 0, 0);
    RB_Motor.speed_pid.SetParams(0, 0, 0, 0, 0);
    Relay1_Off();
    Relay2_Off();
}

/* 每周期所有电机的电流指令写完后，统一发整帧 */
void StartMotor(void)
{
    LF_Motor.StartMotor();
    LB_Motor.StartMotor();
    RF_Motor.StartMotor();
    RB_Motor.StartMotor();
}

bool Chassis_High(void)
{
    Relay1_On();
    Relay2_On();
    LF_Motor.AngleControl(0);
    LB_Motor.AngleControl(0);
    RF_Motor.AngleControl(0);
    RB_Motor.AngleControl(0);
    StartMotor();
    if (LF_Motor.current < 100 && LB_Motor.current < 100 && RF_Motor.current < 100 && RB_Motor.current < 100)
    {
        Relay1_Off();
        Relay2_Off();
        return true;
    }
    return false;
}

bool Chassis_Low(void)
{
    Relay1_On();
    Relay2_On();
    LF_Motor.AngleControl(0);
    LB_Motor.AngleControl(0);
    RF_Motor.AngleControl(0);
    RB_Motor.AngleControl(0);
    StartMotor();
    if (LF_Motor.current < 100 && LB_Motor.current < 100 && RF_Motor.current < 100 && RB_Motor.current < 100)
    {
        Relay1_Off();
        Relay2_Off();
        return true;
    }
    return false;
}

void LIFT_Standby(void)
{
    LF_Motor.StopCurrent();
    LB_Motor.StopCurrent();
    RF_Motor.StopCurrent();
    RB_Motor.StopCurrent();
    StartMotor();
}
