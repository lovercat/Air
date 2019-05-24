#ifndef _DEFINES_NUM_
#define _DEFINES_NUM_
//卡尔曼滤波参数
#define BALANCE_NUMBER 25
#define GyroAccTrim 3.9
#define GyroAccFactor 3.9
#define ACC_AMPLIFY 8
#define TurnOver180Roll 12.5
#define TurnOver180Nick 12.5

//PID误差参数
int Error_GyroRol;
int Error_GyrolI;
int Error_GyroRolD;
int Error_GyroRolold;

//PID误差参数
int Error_GyroPit;
int Error_GyroPitI;
int Error_GyroPitD;
int Error_GyroPitold;

//电机参数
int Motor1;
int Motor2;
int Motor3;
int Motor4;

//输入操作参数
int Ail_cal;
int Ele_cal;
int Thr_cal;
int Rud_cal;

//PID参数
#define Kp 0.14 
#define Ki 0.045
#define Kd 0.004
#define KYaw 0.09
#define KYawI 0.003

//控制平衡
char contorls=0;
#define FALSE 0

#endif