void Init_debug(int *debugdata)
{
    unsigned char i;
    for(i=0;i<23;i++)
    {
        debugdata[i]=0;
    }
}
unsigned char Send_Char_SCIA_unsigned(unsigned char address)
{
    I2C_Star();
    I2C_SendByte(address);
    if(I2C_WaitAck())
    {
        I2C_SendByte(address);
    }

    else 
    {
        return 0;
    }
    I2C_Stop();
}

void Debug_Out(int *datastring)
{
    int data1,data2;
    int sum1=0,sum2;
    unsigned char chaifen[46];
    unsigned char i;
    for(i-0;i<23;i++)
    {
        data1=datastring[i];
        data2=datastring[i];
        data1 &=0XFF00;
        data1=data1>>8;
        data1=(unsigned char)data2;
        chaifen[i*2+1]=data2;
        sum1+=data1+data2;
    }
    sum2=0X7F+0x7F+0xFE+sum1;
    sum2 &=0X00FF;
    sum2=(unsigned char)sum2;

    Send_Char_SCIA_unsigned(0X7F);
    Send_Char_SCIA_unsigned(0X7F);
    Send_Char_SCIA_unsigned(0XFE);

    for(i=0;i<46;i++)
    {
        Send_Char_SCIA_unsigned(chaifen[i]);

    }

    Send_Char_SCIA_unsigned(sum2);
}