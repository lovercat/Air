int T_Y,T_X,T_Z;
int GyroYaw,GyroPit,GyroRol,GyroAccPit,GyroAccRol,GyroAccYaw;
int A_X,A_Y,A_Z;

//平均滤波
int Gyro_Acc_Filter_1(char flitercnt)
{
    int Gyro_Rol_value[20],Gyro_Pit_value[20],Gyro_Yaw_value[20];
    int Acc_Rol_value[20],Acc_Pit_value[20],Acc_Yaw_value[20];
    char cnt=flitercnt;

    for(cnt=0;cnt<flitercnt;cnt++)
    {
        READ_ITG3205();
        READ_ADXL345();

        Gyro_Rol_value[cnt]=T_Y;
        Gyro_Pit_value[cnt]=T_X;
        Gyro_Yaw_value[cnt]=T_Z;

        if(A_X>250 || A_X<-250)
        {
            A_X=0;
        }

        if(A_Y>250 || A_Y<-250)
        {
            A_Y=0;
        }

        if(A_Z>250 || A_Z<-250)
        {
            A_Z=0;
        }

        Acc_Rol_value[cnt]=A_X;
        Acc_Pit_value[cnt]=A_Y;
        Acc_Yaw_value[cnt]=A_Z;
    }

    for(cnt=0;cnt<flitercnt;cnt++)
    {
        T_Y+=Gyro_Rol_value[cnt];
        T_X+=Gyro_Pit_value[cnt];
        T_Z+=Gyro_Yaw_value[cnt];
        
        A_X+=Acc_Rol_value[cnt];
        A_Y+=Acc_Pit_value[cnt];
        A_Z+=Acc_Yaw_value[cnt];
    }

    T_Y/=(flitercnt*8);
    T_X/=(flitercnt*8);
    T_Z/=(flitercnt*8);

    A_X/=(flitercnt);
    A_Y/=flitercnt;
    A_Z/=flitercnt;

    GyroAccRol=A_X;
    GyroAccPit=A_Y;
    GyroAccYaw=A_Z;

    GyroRol=T_X;
    GyroPit=T_Y;
    GyroYaw=T_Z;

    if(GyroAccRol>250 || GyroAccRol<-250)
        GyroAccRol=0;
    if(GyroAccPit>250 || GyroAccPit<-250)
        GyroAccPit=0;
    if(GyroAccYaw>250 ||GyroAccYaw<-250)
        GyroAccYaw=9;

    return T_Y;
}