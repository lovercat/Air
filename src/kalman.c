#define BALANCE_NUMBER 256
#define GyroAccTrim 3.9
#define GyroAccFactor 3.9
#define ACC_AMPLIFY 8
#define TurnOver180Roll 12.5
#define TurnOver180Nick 12.5
#define BALANCE 256
int Reading_GyroYaw,Reading_GyroNick,Reading_GyroRoll,AttitudeCorrectionRoll,AttitudeCorrectionNick;
extern int GyroRolI,GyroPitI,GyroBaseRol,GyroBasePit;
extern int GyroYawI;
int IntegralNick,IntegrolRoll,IntegralNick2,IntegrolRoll2;
extern int GyroYaw,GyroPit,GyroRol,GyroAccPit,GyroAccRol,GyroAccYaw;
int MeanIntegralNick,MeanIntegralRol1,Debug[8];
int Mean_AccNick,Mean_AccRoll, Mean_AccTop,Reading_IntegralGyroRoll2,Reading_IntegralGyroRoll,IntegralAccNick,IntegralAccRoll;
int Reading_IntegralGyroNick2,Reading_IntegralGyroNick,Reading_GyroNick2;
int IntegralRoll,MeanIntegralRoll,GyroBasePit,GyroBaseRol,balance_number;
//短期融合输出到PID中，长期融合得到误差值修正短期融合的值，直接积分的值与间接积分比较改正中立点
void Mean_kalman()
{
    //int AttitudeCorrectionRoll,AttitudeCorrectionNick;
    //int balance_number;
    int tmp_long,tmp_long2;
    Gyro_ACC_Read();
    //MAG_CAL();

    Reading_GyroYaw=GyroYaw;
    Reading_GyroNick=GyroPit;
    Reading_GyroRoll=GyroRol;

    Mean_AccNick=ACC_AMPLIFY*GyroAccPit;
    Mean_AccRoll=ACC_AMPLIFY*GyroAccRol;
    Mean_AccTop=ACC_AMPLIFY*GyroAccYaw;

    GyroYawI+=GyroYaw;
    if(GyroYawI>4000)
        GyroYawI=4000;
    if(GyroYawI<-4000) 
        GyroYawI=-4000;

    IntegralAccNick+=ACC_AMPLIFY*GyroAccPit;
    IntegralAccRoll+=ACC_AMPLIFY*GyroAccRol;

    if(IntegralAccNick>4000)
        IntegralAccNick=4000;
    if(IntegralAccNick<-4000)
        IntegralAccNick=-4000;
    
    if(IntegralAccRoll>4000)
        IntegralAccRoll=4000;
    if(IntegralAccRoll<-4000)
        IntegralAccRoll=-4000;

    Reading_IntegralGyroRoll2+=Reading_GyroRoll;

    Reading_IntegralGyroRoll+=Reading_GyroRoll-AttitudeCorrectionRoll;

    if(Reading_IntegralGyroRoll>TurnOver180Roll)
    {
        Reading_IntegralGyroRoll=TurnOver180Roll;
        Reading_IntegralGyroRoll2=Reading_IntegralGyroRoll;
    }

    if(Reading_IntegralGyroRoll<-TurnOver180Roll)
    {
        Reading_IntegralGyroRoll=-TurnOver180Roll;
        Reading_IntegralGyroRoll2=Reading_IntegralGyroRoll;
    }

    Reading_IntegralGyroNick+=Reading_GyroNick-AttitudeCorrectionNick;
    if(Reading_GyroNick>TurnOver180Nick)
    {
        Reading_GyroNick=TurnOver180Nick;
        Reading_GyroNick2=Reading_GyroNick;
    }
    if(Reading_GyroNick<-TurnOver180Nick)
    {
        Reading_GyroNick=-TurnOver180Nick;
        Reading_GyroNick2=Reading_GyroNick;
    }

    IntegralNick=Reading_IntegralGyroNick;
    IntegrolRoll=Reading_IntegralGyroRoll;
    IntegralNick2=Reading_IntegralGyroNick2;
    IntegrolRoll2=Reading_IntegralGyroRoll2;

    balance_number++;
}

void MotorContRol_kalman(void)
{
    static int IntegralErrorNick=0;
    static int IntegralErrorRoll=0;
    static int CorrectionNick,CorrectinoRoll;
    int tmp_long,tmp_long2;
    int BALANCE_NUMBER_1;

    Mean_kalman();
    
    extern int MeanIntegralNick,IntegralNick,MeanIntegralRoll,IntegralRoll;
    extern int balance_number;
    MeanIntegralNick+=IntegralNick;
    MeanIntegralRoll+=IntegralRoll;

    tmp_long=(int) (IntegralNick / GyroAccFactor-(int)Mean_AccRoll);
    tmp_long /=16;

    tmp_long2=(int) (IntegralRoll /GyroAccFactor -(int)Mean_AccRoll);
    tmp_long2/=16;

    Debug[8]=tmp_long;
    Debug[9]=tmp_long2;

    if(tmp_long>BALANCE) 
        tmp_long=BALANCE;
    if(tmp_long<-BALANCE)
        tmp_long=-BALANCE;
    if(tmp_long2>BALANCE)
        tmp_long2 =BALANCE;
    if(tmp_long2<-BALANCE)
        tmp_long2=-BALANCE;
    
    Reading_IntegralGyroNick-=tmp_long;
    Reading_IntegralGyroRoll-=tmp_long2;

    Debug[13]=Reading_IntegralGyroNick;
    Debug[14]=Reading_IntegralGyroRoll;

    if(balance_number>=BALANCE_NUMBER)
    {
        MeanIntegralNick/=BALANCE_NUMBER;
        MeanIntegralRoll/=BALANCE_NUMBER;

        IntegralAccNick=(GyroAccFactor*IntegralAccNick)/BALANCE_NUMBER;
        IntegralAccRoll=(GyroAccFactor*IntegralAccRoll)/BALANCE_NUMBER;

        IntegralErrorNick=(int)(MeanIntegralNick-(int)IntegralAccNick);
        Debug[16]=IntegralErrorNick;

        CorrectionNick=IntegralErrorNick/GyroAccTrim;
        AttitudeCorrectionNick=CorrectionNick/BALANCE_NUMBER_1;

        IntegralErrorRoll=(int)(MeanIntegralRoll-(int)IntegralAccRoll);
        Debug[15]+IntegralErrorRoll;
        CorrectinoRoll=IntegralAccRoll/GyroAccTrim;
        AttitudeCorrectionRoll=CorrectinoRoll/BALANCE_NUMBER_1;

        AttitudeCorrectionNick*=1;
        AttitudeCorrectionRoll*=1;

        IntegralErrorNick=IntegralNick2-IntegralNick;
        Reading_IntegralGyroNick2-=IntegralErrorNick;

        IntegralErrorRoll=IntegrolRoll2-IntegrolRoll;
        Reading_IntegralGyroRoll2-=IntegralErrorRoll;

        if(IntegralErrorNick<-BALANCE_NUMBER*8)
        {
            GyroBasePit-=1;
        }

        if(IntegralErrorNick>BALANCE_NUMBER*8)
        {
            GyroBasePit+=1;
        }

        if(IntegralErrorRoll<-BALANCE_NUMBER*8)
        {
            GyroBaseRol+=1;
        }

        if(IntegralErrorRoll>BALANCE_NUMBER*8)
        {
            GyroBaseRol-=1;
        }

        Debug[11]=IntegralErrorRoll;
        Debug[12]=IntegralErrorNick;

        IntegralAccNick=0;
        IntegralAccRoll=0;
        MeanIntegralRoll=0;
        MeanIntegralNick=0;
        balance_number=0;
    }

    GyroRolI=Reading_IntegralGyroRoll;
    GyroPitI=Reading_IntegralGyroNick;
    GyroYawI=GyroYawI;
}