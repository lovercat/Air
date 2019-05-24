//ITG3205
#define     WHO     0x00
#define     SMPL    0x15
#define     DLPF    0x16
#define     INT_C   0x17
#define     INT_S   0x1A
#define     TMP_H   0x1B
#define     TMP_L   0x1C
#define     GX_H    0x1D
#define     GX_L    0x1E
#define     GY_H    0x1F
#define     GY_L    0x20
#define     GZ_H    0x21
#define     GZ_L    0x22
#define     PWR_M   0x3E
#define     ITG3205_Addr 0xD0


//ADXL345
#define     ADXL345_Addr    0xA6
unsigned char TX_DATA[4];
unsigned char BUF[10];
char test=0;
int T_X,T_Y,T_Z,T_T,A_X,A_Y,A_Z;    //x,y,z轴温度


//IIC端口定义
#define     SCL_H   P6OUT |= BIT0
#define     SCL_L   P6OUT &=~BIT0

#define     SDA_H   P6OUT |= BIT1
#define     SDA_L   P6OUT &+~BIT1

#define     SCL_read    P6IN&BIT0
#define     SDA_read    P6IN&BIT1
