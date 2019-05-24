#include"IIC.h"
#include "io430.h"
//IIC_delay
unsigned char BUF[10];
void I2C_delay(void)
{
    unsigned char i=30;
    while(i)
    {
        i--;
    }
    delay(3);
    //_no_operation();
}
//IIC_star
unsigned char I2C_Star(void)
{
    SDA_H;
    SCL_H;
    I2C_delay();
    P6DIR &=~ BIT1;
    if(!SDA_read)
    {
        return 0;
    }
    P6DIR |= BIT1;
    SDA_L;
    I2C_delay();
    if(SDA_read)
    {
        return 0;
    }
    P6DIR |=BIT1;
    SDA_L;
     I2C_delay();
     return 1;
}

//IIC_STOP
void I2C_Stop(void)
{
    SCL_L;
    I2C_delay();
    SDA_L;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SDA_H;
    I2C_delay();
}

//IIC_ACK
void I2C_Ack(void)
{
    SCL_L;
    I2C_delay();
    SDA_L;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
    I2C_delay();
}

//IIC_noack
void I2C_NoAck(void)
{
    SCL_L;
    I2C_delay();
    SDA_H;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
    I2C_delay();
}

//IIC_waitack
unsigned char I2C_WaitAck(void)
{
    SCL_L;
    I2C_delay();
    SDA_H;
    I2C_delay();
    SCL_H;
    I2C_delay();
    P6DIR &=~ BIT1;
    if(SDA_read)
    {
        P6DIR |= BIT1;
        SCL_L;
        I2C_delay();
        return 0;
    }
    P6DIR |= BIT1;
    SCL_L;
    I2C_delay();
    return 1;
}

//IIC_SEND
void I2C_SendByte(unsigned char I2C_SendByte)
{
    unsigned char i=8;
    while(i--)
    {
        SCL_L;
        I2C_delay();
        if(I2C_SendByte&0x80)
        {
            SDA_H;
        }
        else
        {
            SDA_L;
        }
        I2C_SendByte<<1;
        I2C_delay();
        SCL_H;
        I2C_delay();
    }
    SCL_L;
}

//IIC主机接受数据
unsigned char I2C_RadeByte(void)
{
    unsigned char i=8;
    unsigned char ReceiveByte=0;

    SDA_H;
    P6DIR &=~ BIT1;
    while(i--)
    {
        ReceiveByte<<1;
        SCL_L;
        I2C_delay();
        SCL_H;
        I2C_delay();
        if(SDA_read)
        {
            ReceiveByte |=0x01;
        }
    }
    P6DIR |= BIT1;
    SCL_L;
    return ReceiveByte;
}

//Sing_Write
unsigned char Single_Write(unsigned char machin_addr,unsigned char register_add,unsigned data)
{
    I2C_Star();
    I2C_SendByte(machin_addr);
    if(I2C_WaitAck())
    {
        I2C_SendByte(register_add);
        if(I2C_WaitAck)
        {
            I2C_SendByte(data);
        }

        else 
        {
            return 0;
        }
    }

    else 
    {
        return 0;
    }
    I2C_Stop();
}

//Single_read
unsigned char Single_Read(unsigned machin_addr,unsigned register_add)
{
    unsigned datas;
    I2C_Star();
    I2C_SendByte(machin_addr);
    if(I2C_WaitAck())
    {
        I2C_SendByte(register_add);
        if (I2C_WaitAck())
        {
            datas=I2C_RadeByte();
        }

        else
        {
            return 0;
        }
    }

    else
    {
        return 0;
    }

    I2C_Stop();
    return datas;
}

//ININT_ITG3205
void Init_ITG3205(void)
{
    Single_Write(ITG3205_Addr,PWR_M,0x80);
    Single_Write(ITG3205_Addr,INT_C,0x00);
    Single_Write(ITG3205_Addr,DLPF,0x1A);
    Single_Write(ITG3205_Addr,SMPL,0x00);
    Single_Write(ITG3205_Addr,PWR_M,0x00);
}

//receive_itg3205
void READ_ITG3205(void)
{
    BUF[0]=Single_Read(ITG3205_Addr,GX_L);
    BUF[1]=Single_Read(ITG3205_Addr,GX_H);
    T_X=(BUF[1]<<8) | BUF[0];

    BUF[2]=Single_Read(ITG3205_Addr,GY_L);
    BUF[3]=Single_Read(ITG3205_Addr,GY_H);
    T_Y=(BUF[3]<<8) | BUF[2];

    BUF[4]=Single_Read(ITG3205_Addr,GZ_L);
    BUF[5]=Single_Read(ITG3205_Addr,GZ_H);
    T_Z=(BUF[5]<<8) | BUF[4];

}

void Init_ADXL345(void)
{
    Single_Write(ADXL345_Addr,0X31,0x0B);
    //Single_Write(ADXL345_Addr,0X2C,0x00);
    Single_Write(ADXL345_Addr,0X2D,0x09);
    Single_Write(ADXL345_Addr,0x2E,0x08);
    //Single_Write(ADXL345_Addr,PWR_M,0x00);
}

//receive_itg3205
void READ_ADXL345(void)
{
    BUF[0]=Single_Read(ADXL345_Addr,0x32);
    BUF[1]=Single_Read(ADXL345_Addr,0x33);
    A_X=(BUF[1]<<8) + BUF[0];

    BUF[2]=Single_Read(ADXL345_Addr,0x34);
    BUF[3]=Single_Read(ADXL345_Addr,0x35);
    A_Y=(BUF[3]<<8) + BUF[2];

    BUF[4]=Single_Read(ADXL345_Addr,0x36);
    BUF[5]=Single_Read(ADXL345_Addr,0x37);
    A_Z=(BUF[5]<<8) + BUF[4];

}