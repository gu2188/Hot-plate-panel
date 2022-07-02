#include"wk.h"

unsigned int working_condition;//close=0,open=1,keep=2,timer and keep =3
unsigned int adjustment_range;
unsigned int adjustment_range_data[4];//adjustment range 1~5~10~100
int design_temperature;
void Always_interrupt_init(void)
{
    EA=1;
    //External_interrupt
    EX0=1;
    EX1=1;
    IT0=1;
    IT1=1;
    IE0=1;
    IE1=1;
    Ex_interrupt_0=0;//!!This line because the schematic design flaws, the use of _code changes.	normal:Ex_interrupt_0=1;
    Ex_interrupt_1=0;//!!This line because the schematic design flaws, the use of _code changes.	normal:Ex_interrupt_1=1;
    //timer_interrupt
    ET0=1;
    ET1=1;

}

void timer0_init(void) //50ms
{
    TMOD|=0x01;
    TL0=0x00;
    TH0=0x4C;
    TF0=0;
    TR0=1;
}

void timer1_init(void) //10ms
{
    TMOD|=0x10;
    TL1=0x00;
    TH1=0xDC;
    TF1=0;
    TR1=0;
}

void External_interrupt_0(void) interrupt 0
{
    IE0=0;
    working_condition++;
    if(working_condition==4)
        working_condition=0;
}

void External_interrupt_1(void) interrupt 2
{
    adjustment_range++;
    if(adjustment_range==4)
        adjustment_range=0;
}

void timer0_interrupt(void) interrupt 1
{
    TF0 = 0;
    TL0=0x00;
    TH0=0x4C;
    if(key3==1)
    {
        design_temperature+=adjustment_range_data[adjustment_range];
        if(design_temperature>250)
            design_temperature=250;
        while(key3);
    }
    if(key4==1)
    {
        design_temperature-=adjustment_range_data[adjustment_range];
        if(working_condition==3)
        {
            if(design_temperature<1)
                design_temperature=1;
        }
        else
        {
            if(design_temperature<40)
                design_temperature=40;
        }
        while(key4);
    }
}

void timer1_interrupt(void) interrupt 3
{
    static int num=0;
    TL1=0x00;
    TH1=0xDC;
    TF1=0;
    num++;
    if((num/6000)>=((volatile)design_temperature))
        /*When design_temperature change,the program crashes and
        variables change,so volative can restore the program to
        normal
        */
    {
        num=0;
        TR1=0;
        working_condition=0;
    }
    if(working_condition!=3)
    {
        num=0;
        TR1=0;
    }
}
