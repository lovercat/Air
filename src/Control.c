unsigned char controls;
void Yaw(int speed);
void Balance(int Rol,int Pit,int Yaw);
void PWM_out_500(unsigned char ch, int period, unsigned char mode);
void MotorContRol_kalman(void);
int GyroRolI,GyroPitI,GyroYawI;
int Motor1,Motor2,Motor3,Motor4;
void Thr(int speed);
void Control()
{
    controls=1;
    MotorContRol_kalman();
    Balance(GyroRolI,GyroPitI,GyroYawI);
    PWM_out_500(1,Motor1,1);
    PWM_out_500(2,Motor2,1);
    PWM_out_500(3,Motor3,1);
    PWM_out_500(4,Motor4,1);
    MotorContRol_kalman();
    if(-100<GyroRolI & GyroRolI<100 & GyroPitI<-100 & GyroPitI>100 & GyroYawI>-100 & GyroYawI<100)
    {
        Thr(25);
        delay(1000);
        delay(1000);
        MotorContRol_kalman();
        Balance(GyroRolI,GyroPitI,GyroYawI);
        PWM_out_500(1,Motor1,1);
        PWM_out_500(2,Motor2,1);
        PWM_out_500(3,Motor3,1);
        PWM_out_500(4,Motor4,1);
        Ele(150);
        delay(1000);
        delay(1000);
        MotorContRol_kalman();
        Balance(GyroRolI,GyroPitI,GyroYawI);
        PWM_out_500(1,Motor1,1);
        PWM_out_500(2,Motor2,1);
        PWM_out_500(3,Motor3,1);
        PWM_out_500(4,Motor4,1);
        delay(1000);
        MotorContRol_kalman();
        Balance(GyroRolI,GyroPitI,GyroYawI);
        Yaw1(100);
        delay(5);
        MotorContRol_kalman();
        Balance(GyroRolI,GyroPitI,GyroYawI);
        Ele(150);
        Ele(-150);
        MotorContRol_kalman();
        Balance(GyroRolI,GyroPitI,GyroYawI);
        Yaw1(100);
        delay(5);
        MotorContRol_kalman();
        Balance(GyroRolI,GyroPitI,GyroYawI);
        Ele(150);
        delay(1000);
        MotorContRol_kalman();
        Balance(GyroRolI,GyroPitI,GyroYawI);
        controls=0;
    }
}