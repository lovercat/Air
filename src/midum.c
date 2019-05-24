#define Rol_fu 0
#define Pit_fu 0
#define Yaw_fu 0
#define Rol_ACC_fu 0
#define Pit_ACC_fu 0
#define Yaw_ACC_fu 0
extern char plane_ready;
extern int angle_Rol,angle_Pit;
int GyroAccBaseRol,GyroAccBasePit,GyroAccBaseYaw,GyroBaseCnt,GyroBaseYaw;
extern int GyroBaseRol,GyroBasePit,GyroAccBasePit;
int GYROBASECNT ,GYROBASECNTl;
extern int GyroRol,GyroYaw,GyroAccRol,GyroAccPit,GyroAccYaw;
extern int  Reading_IntegralGyroNick,Reading_IntegralGyroRoll;
extern int GyroPitI,GyroYawI,GyroPit;
int  GyroRo1I, ReadingNetRoll,ReadingNetNick;
int Gyro_Acc_Filter_1(char flitercnt);
void Gyro_ACC_Read(void);
void plane_test()
{
    int angle_Rol,angle_Pit;

    READ_ADXL345();
    Gyro_Acc_Filter_1(10);
    Gyro_ACC_Read();
    angle_Rol=labs(GyroAccBaseRol);
    angle_Pit=labs(GyroAccBasePit);
    if(angle_Rol>25 || angle_Pit >25)
    {
        plane_ready=0;
    }
    else 
        plane_ready=1;
}

void Base_Test()
{
    Gyro_Acc_Filter_1(4);
    Gyro_ACC_Read();

    plane_test();

    GyroBaseCnt=GYROBASECNT;
    GyroBaseRol=GyroRol;
    GyroBasePit=GyroPit;
    GyroBaseYaw=GyroYaw;
    GyroAccBaseRol+=GyroAccRol;
    GyroAccBasePit+=GyroAccPit;
    GyroAccBaseYaw+=GyroAccYaw;

    for(GyroBaseCnt=GYROBASECNT;GyroBaseCnt>0;GyroBaseCnt--)
    {
        Gyro_Acc_Filter_1(10);
        GyroBaseRol+=GyroRol;
        GyroBasePit+=GyroPit;
        GyroBaseYaw+=GyroYaw;
        GyroAccBaseRol+=GyroAccRol;
        GyroAccBasePit+=GyroAccPit;
        GyroAccBaseYaw+=GyroAccYaw;
        if(GyroBaseCnt==1)
        {
            GyroBaseRol=GyroBaseRol/GYROBASECNT;
            GyroBasePit=GyroBasePit/GYROBASECNT;
            GyroBaseYaw=GyroBaseYaw/GYROBASECNT;

            GyroAccBaseRol/=GYROBASECNT;
            GyroAccBasePit/=GYROBASECNT;
            GyroAccBaseYaw/=GYROBASECNT;

        }
    }

    for(GyroBaseCnt=0;GyroBaseCnt<GYROBASECNTl;GyroBaseCnt++)
    {
        MotorContRol_kalman(0);
        ReadingNetNick+=Reading_IntegralGyroNick;
        ReadingNetRoll=Reading_IntegralGyroRoll;
        if(GyroBaseCnt==GYROBASECNT)
        {
            ReadingNetNick/=GYROBASECNT;
            ReadingNetRoll/=GYROBASECNT;
        }
    }
    GyroRo1I=GyroPitI=GyroYawI=0;
}

void Gyro_ACC_Read(void)
{
    Gyro_Acc_Filter_1(2);

    GyroRol-=GyroBaseRol;
    GyroPit-=GyroBasePit;
    GyroYaw-=GyroBaseYaw;

    GyroAccRol-=GyroAccBaseRol;
    GyroAccPit-=GyroAccBasePit;
    GyroAccYaw-=GyroAccBaseYaw;
    
    if(Rol_fu)
        GyroRol=-GyroRol;
    if(Pit_fu)
        GyroPit=-GyroPit;
    if(Yaw_fu)
        GyroYaw=-GyroYaw;

    if(Rol_ACC_fu)
        GyroAccRol=-GyroAccRol;
    if(Pit_ACC_fu)
        GyroAccPit=-GyroAccPit;
    if(Yaw_ACC_fu)
        GyroAccYaw=-GyroAccYaw;
}