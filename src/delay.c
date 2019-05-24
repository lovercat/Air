#include "io430.h"
#include<stdio.h>
#define MCU_SPEED 20
//#define delay(x) _delay_cycles((x*MCU_SPEED))
void delay(char x)
{
    volatile unsigned int i,j;
    for (i=0;i<x;i++)
    //_delay_cycles(MCU_SPEED);
     for(j=110;j>0;j--);
}