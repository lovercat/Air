//卡尔曼滤波参数
#define BALANCE_NUMBER 25
#define GyroAccTrim 3.9
#define GyroAccFactor 3.9
#define ACC_AMPLIFY 8
#define TurnOver180Roll 12.5
#define TurnOver180Nick 12.5

//PID误差参数
extern int Error_GyroRol;
extern int Error_GyrolI;
extern int Error_GyroRolD;
extern int Error_GyroRolold;

//PID误差参数
extern int Error_GyroPit;
extern int Error_GyroPitI;
extern int Error_GyroPitD;
extern int Error_GyroPitold;

//电机参数
extern int Motor1;
extern int Motor2;
extern int Motor3;
extern int Motor4;

//输入操作参数
extern int Ail_cal;
extern int Ele_cal;
extern int Thr_cal;
extern int Rud_cal;

//PID参数
#define Kp 0.14 
#define Ki 0.045
#define Kd 0.004
#define KYaw 0.09
#define KYawI 0.003

//控制平衡
extern unsigned char contorls=0;
#define FALSE 0

