#include "io430.h"
void UCS_XTAL2_Init(char mclkdiv, char smclkdiv, char aclkdiv)
{
    P5SEL |= BIT2 | BIT3;
    UCSCTL6 &= ~XT2OFF;
    UCSCTL3 |= SELEREF_2;
    UCSCTL4 |= SELS_5 | SELM5;
    UCSCTL4 |=SELA_5;

    UCSCTL6 &= ~XT2DRIVE1;

    UCSCTL5 |= aclkdiv<<8;
    UCSCTL5 |= smclkdiv<<4;
    UCSCTL5 |= mclkdiv;

    do 
    {
        UCSCTL7 &= ~(XT2OFFG | XT1LFOFFG | DCOFFG);
        SFRIFG1 &= ~OFIFG;

    }
    while(SFRIFG! & OFIFG);
}

