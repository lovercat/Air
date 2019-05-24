#define Kp 0.14 
#define Ki 0.045
#define Kd 0.004
#define KYaw 0.09
#define KYawI 0.003
int MotorLimitValue(int v);
int Error_GyroRol,Error_GyroRolI,Error_GyroRolD,Error_GyroRolold;
int Error_GyroPit,Error_GyroPitI,Error_GyroPitD,Error_GyroPitold;
int Thr_cal,RxRud;
extern int Ail_cal,Ele_cal,Yaw_cal,Rud_cal;
extern int Motor1,Motor2,Motor3,Motor4;
extern int GyroRol,GyroRolI,GyroPit,GyroPitI,GyroYaw,GyroYawI;
void PID(unsigned char Ail_cal,unsigned char Ele_cal,unsigned Rud_cal)
{
    Error_GyroRol=Ail_cal+GyroRol;
    Error_GyroRolI=Ail_cal+GyroRolI/16;
    Error_GyroRolD=Error_GyroRol-Error_GyroRolold;
    Error_GyroRolold=Error_GyroRol;

    Error_GyroPit=Ele_cal+GyroPit;
    Error_GyroPitI=Ele_cal+GyroPitI/16;
    Error_GyroPitD=Error_GyroPit-Error_GyroPitold;
    Error_GyroPitold=Error_GyroPit;

    Ail_cal=(int)(Kp*Error_GyroRol+Ki*Error_GyroRolI+Kd*Error_GyroRolD);
    Ele_cal=(int)(Kp*Error_GyroPit+Ki*Error_GyroPitI+Kd*Error_GyroPitD);
    Rud_cal=(int)(-RxRud/4+KYaw*GyroYaw+KYawI*GyroYawI);

    Motor1=MotorLimitValue(Thr_cal-Ail_cal+Ele_cal+Rud_cal);
    Motor2=MotorLimitValue(Thr_cal-Ail_cal-Ele_cal-Rud_cal);
    Motor3=MotorLimitValue(Thr_cal+Ail_cal+Ele_cal-Rud_cal);
    Motor4=MotorLimitValue(Thr_cal+Ail_cal-Ele_cal+Rud_cal);
}