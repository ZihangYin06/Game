#include "LIFT_Task.hpp"

static PID LF_Speed_PID;
static PID LF_Angle_PID;
static PID LB_Speed_PID;
static PID LB_Angle_PID;
static PID RF_Speed_PID;
static PID RF_Angle_PID;
static PID RB_Speed_PID;
static PID RB_Angle_PID;

void LIFT_Init(void)
{
    LF_Angle_PID.SetParams(0, 0, 0, 0, 0);
    LF_Speed_PID.SetParams(0, 0, 0, 0, 0);
    LB_Angle_PID.SetParams(0, 0, 0, 0, 0);
    LB_Speed_PID.SetParams(0, 0, 0, 0, 0);
    RF_Angle_PID.SetParams(0, 0, 0, 0, 0);
    RF_Speed_PID.SetParams(0, 0, 0, 0, 0);
    RB_Angle_PID.SetParams(0, 0, 0, 0, 0);
    RB_Speed_PID.SetParams(0, 0, 0, 0, 0);
    Relay1_Off();
    Relay2_Off();
}

void StartMotor(void)
{
    LF_Motor.StartMotor(MotorModel::M3508, LF_LIFT_CAN);
    LB_Motor.StartMotor(MotorModel::M3508, LB_LIFT_CAN);
    RF_Motor.StartMotor(MotorModel::M3508, RF_LIFT_CAN);
    RB_Motor.StartMotor(MotorModel::M3508, RB_LIFT_CAN);
}

bool Chassis_High(void)
{
    Relay1_On();
    Relay2_On();
    LF_Angle_PID.AngleCalc(LF_Speed_PID, 0, LF_Motor.accumulate_angle, LF_Motor.speed);
    LB_Angle_PID.AngleCalc(LB_Speed_PID, 0, LB_Motor.accumulate_angle, LB_Motor.speed);
    RF_Angle_PID.AngleCalc(RF_Speed_PID, 0, RF_Motor.accumulate_angle, RF_Motor.speed);
    RB_Angle_PID.AngleCalc(RB_Speed_PID, 0, RB_Motor.accumulate_angle, RB_Motor.speed);
    LF_Motor.SetCurrent(MotorModel::M3508, LF_LIFT_CAN, LF_LIFT_ID, (int16_t)LF_Speed_PID.GetOutput());
    LB_Motor.SetCurrent(MotorModel::M3508, LB_LIFT_CAN, LB_LIFT_ID, (int16_t)LB_Speed_PID.GetOutput());
    RF_Motor.SetCurrent(MotorModel::M3508, RF_LIFT_CAN, RF_LIFT_ID, (int16_t)RF_Speed_PID.GetOutput());
    RB_Motor.SetCurrent(MotorModel::M3508, RB_LIFT_CAN, RB_LIFT_ID, (int16_t)RB_Speed_PID.GetOutput());
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
    LF_Angle_PID.AngleCalc(LF_Speed_PID, 0, LF_Motor.accumulate_angle, LF_Motor.speed);
    LB_Angle_PID.AngleCalc(LB_Speed_PID, 0, LB_Motor.accumulate_angle, LB_Motor.speed);
    RF_Angle_PID.AngleCalc(RF_Speed_PID, 0, RF_Motor.accumulate_angle, RF_Motor.speed);
    RB_Angle_PID.AngleCalc(RB_Speed_PID, 0, RB_Motor.accumulate_angle, RB_Motor.speed);
    LF_Motor.SetCurrent(MotorModel::M3508, LF_LIFT_CAN, LF_LIFT_ID, (int16_t)LF_Speed_PID.GetOutput());
    LB_Motor.SetCurrent(MotorModel::M3508, LB_LIFT_CAN, LB_LIFT_ID, (int16_t)LB_Speed_PID.GetOutput());
    RF_Motor.SetCurrent(MotorModel::M3508, RF_LIFT_CAN, RF_LIFT_ID, (int16_t)RF_Speed_PID.GetOutput());
    RB_Motor.SetCurrent(MotorModel::M3508, RB_LIFT_CAN, RB_LIFT_ID, (int16_t)RB_Speed_PID.GetOutput());
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
    LF_Motor.SetCurrent(MotorModel::M3508, LF_LIFT_CAN, LF_LIFT_ID, 0);
    LB_Motor.SetCurrent(MotorModel::M3508, LB_LIFT_CAN, LB_LIFT_ID, 0);
    RF_Motor.SetCurrent(MotorModel::M3508, RF_LIFT_CAN, RF_LIFT_ID, 0);
    RB_Motor.SetCurrent(MotorModel::M3508, RB_LIFT_CAN, RB_LIFT_ID, 0);
    StartMotor();
}
