#include "io430.h"
//电机驱动限幅
//v=TACCRX,PWM_MAX=TAXCCR0
int MotorLimitValue(int v)
{
    int PWM_MAX=250;
    if(v>PWM_MAX)
    {
        return PWM_MAX;
    }
    if(v<0)
    {
        return 1;
    }
    return v;
}

//init PWM
void PWM_Inint_500(void)
{
    TA0CTL |=MC_1;

    TA0CCTL1 |= OUTMOD_7;
    TA0CCTL2 |= OUTMOD_7;
    TA0CCTL3 |= OUTMOD_7;
    TA0CCTL4 |= OUTMOD_7;
    //TA0CTL |= ID_3;      //四分频
    TA0CTL =TASSEL_2 |MC_1 | ID_2 |TACLR;
    TA0CTL |= ID_3;
    TA0CTL |= 2500;
}

//占空比输入，通道、占空比、触发模式
void PWM_out_500(unsigned char ch, int period, unsigned char mode)
{
    period*=10;
    if(mode==0) //低电平触发mos管
    {
        period=2500-period;
    }

    if(period>2400)
    {
        period=2400;
    }

    if(period<5)
    {
        period=5;
    }

    switch(ch)
    {
        case 1:
            TA0CCR1=period;
            break;
        case 2:
            TA0CCR2=period;
            break;
        case 3:
            TA0CCR3=period;
            break;
        case 4:
            TA0CCR4=period;
            break;
        default:break;
    }
}