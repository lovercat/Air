int MotorLimitValue(int v);
void PWM_out_500(unsigned char ch, int period, unsigned char mode);
extern int Motor1,Motor2,Motor3,Motor4;
void inint_speed()
{
    PWM_out_500(1,1,1);
    PWM_out_500(2,1,1);
    PWM_out_500(3,1,1);
    PWM_out_500(4,1,1);
}
void Thr(int speed)
{
    extern int Motor1,Motor2,Motor3,Motor4;
    Motor1=MotorLimitValue(speed);
    Motor2=MotorLimitValue(speed);
    Motor3=MotorLimitValue(speed);
    Motor4=MotorLimitValue(speed);
    PWM_out_500(1,Motor1,1);
    PWM_out_500(2,Motor2,1);
    PWM_out_500(3,Motor3,1);
    PWM_out_500(4,Motor4,1);
}

void Ail(int speed)
{
    if(speed<0)
    {
        speed=-speed;
        Motor1=MotorLimitValue(speed);
        Motor3=MotorLimitValue(speed);
        PWM_out_500(1,Motor1,1);
        PWM_out_500(3,Motor3,1);
    }
    else
    {
        Motor2=MotorLimitValue(speed);
        Motor4=MotorLimitValue(speed);
        PWM_out_500(2,Motor2,1);
        PWM_out_500(4,Motor4,1);
    }
    
}
void Ele(int speed)
{
    if(speed<0)
    {
        speed=-speed;
        Motor2=MotorLimitValue(speed);
        Motor4=MotorLimitValue(speed);
        PWM_out_500(2,Motor2,1);
        PWM_out_500(4,Motor4,1);
    }
    else
    {
        Motor1=MotorLimitValue(speed);
        Motor2=MotorLimitValue(speed);
        PWM_out_500(1,Motor1,1);
        PWM_out_500(2,Motor2,1);
    }
    
}

void Yaw1(int speed)
{
    if(speed<0)
    {
        speed=-speed;
        Motor2=MotorLimitValue(speed);
        Motor3=MotorLimitValue(speed);
        PWM_out_500(2,Motor2,1);
        PWM_out_500(3,Motor3,1);
    }
    else
    {
        Motor1=MotorLimitValue(speed);
        Motor4=MotorLimitValue(speed);
        PWM_out_500(1,Motor1,1);
        PWM_out_500(4,Motor4,1);
    }
    
}