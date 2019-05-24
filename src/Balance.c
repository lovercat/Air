int Ele_cal;
int Ail_cal;
int Rud_cal;
//控制飞行器稳定
void Balance(int Rol,int Pit,int Yaw)
{
    if(Pit>0 & Rol>0 & Yaw>0)
    {
        Ele_cal--;
        Ail_cal--;
        Rud_cal--;
    }
    if(Pit>0 & Rol <0 & Yaw>0)
    {
        Ele_cal--;
        Ail_cal++;
        Rud_cal--;
    }
    if(Pit<0 & Rol>0 & Yaw>0)
    {
        Ele_cal++;
        Ail_cal--;
        Rud_cal--;
    }
    if(Pit<0 & Rol<0 & Yaw>0)
    {
        Ele_cal++;
        Ail_cal++;
        Rud_cal--;
    }
    if(Pit>0 & Rol>0 & Yaw<0)
    {
        Ele_cal--;
        Ail_cal--;
        Rud_cal++;
    }
    if(Pit>0 & Rol<0 & Yaw<0)
    {
        Ele_cal--;
        Ail_cal++;
        Rud_cal++;
    }
    if(Pit<0 & Rol>0 & Yaw<0)
    {
        Ele_cal++;
        Ail_cal--;
        Rud_cal++;
    }
    if(Pit<0 & Rol<0 & Yaw<0)
    {
        Ele_cal++;
        Ail_cal++;
        Rud_cal++;
    }
    PID(Ail_cal,Ele_cal,Rud_cal);
}