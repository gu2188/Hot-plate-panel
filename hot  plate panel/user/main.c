#include"wk.h"

void variable_init(void)
{
    //IO_init
    P3M1|=0X00;
    P3M0|=0x10;
    P1M1=0X03;
    P1M0=0X00;
    //variable_init
    res_voltage_data=0;
    res_voltage_data_power=0;
    thermistor_voltage_data=0;
    thermistor_voltage_data_power=0;
    working_condition=2;//!!This line because the schematic design flaws, the use of _code changes. normal:working_condition=0;
    adjustment_range=2;
    adjustment_range_data[0]=1;
    adjustment_range_data[1]=5;
    adjustment_range_data[2]=10;
    adjustment_range_data[3]=100;
    design_temperature=200;
    //IO_init
    key3=0;
    key4=0;
    //mos control
    MOS_control=0;
}

int main()
{
    variable_init();
    lcd_init();
    Always_interrupt_init();
    timer0_init();
    timer1_init();
    ADC_initialize();
    while(1)
    {
        Job_control();
        According_lcd();
    }
}