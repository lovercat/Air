#include<defines_num.h>
#include<IIC.h>
//#define TA0CCR1 M1
//#define TA0CCR2 M2
//#define TA0CCR3 M3
//#define TA0CCR4 M4 

void main()
{
    PWM_ININT_500();
    plane_test();
    Base_Test();
    while(1)
    {
        if(plane_ready==1)
        {
            if(Controls==0)
            {
                MotorContRol_kalman();
                Balance(GyroRolI,GyroPitI,GyroYawI);
                PWM_out_500(1,Motor1,1);
                PWM_out_500(2,Motor2,1);
                PWM_out_500(3,Motor3,1);
                PWM_out_500(4,Motor4,1);
            }

            if(Controls==1)
            {
                MotorContRol_kalman();
                Balance(GyroRolI,GyroPitI,GyroYawI);
                Control();
            }
            
        }
     
    }

}
