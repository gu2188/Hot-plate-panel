#include"wk.h"

void According_lcd(void)
{
    static unsigned char a=0;
    int T=0;
    //The first line
    lcd_w_cmd(0x80);//~0x85
    switch(working_condition)
    {
    case 0:
        lcd_w_data('c');
        lcd_w_data('l');
        lcd_w_data('o');
        lcd_w_data('c');
        lcd_w_data('e');
        break;
    case 1:
        lcd_w_data('o');
        lcd_w_data('p');
        lcd_w_data('e');
        lcd_w_data('n');
        lcd_w_data(' ');
        break;
    case 2:
        lcd_w_data('k');
        lcd_w_data('e');
        lcd_w_data('e');
        lcd_w_data('p');
        lcd_w_data(' ');
        break;
    case 3:
        lcd_w_data('t');
        lcd_w_data('i');
        lcd_w_data('m');
        lcd_w_data('e');
        lcd_w_data('r');
        break;
    }
    adc_thermistor_voltage();
    adc_thermistor_voltage_data();
		T=temp_find();
    lcd_w_cmd(0x86);//~0x88
    lcd_w_data(((uchar)(T/100)+'0'));
    lcd_w_data(((uchar)(T%100/10)+'0'));
    lcd_w_data((uchar)(T%10)+'0');

    lcd_w_cmd(0x89);//~0x8A
    lcd_w_data('-');
    lcd_w_data('>');

    lcd_w_cmd(0x8B);//0X8D
    lcd_w_data((uchar)(design_temperature/100+'0'));
    lcd_w_data((uchar)(design_temperature%100/10+'0'));
    lcd_w_data((uchar)(design_temperature%10+'0'));

    lcd_w_cmd(0x8F);
    if(working_condition&&a)
    {
        lcd_w_data('*');
        a=!a;
    }
    else
    {
        lcd_w_data(' ');
        a=!a;
    }
    //The second line
    lcd_w_cmd(0xC0);//~0xC4
    adc_res_voltage();
    adc_res_voltage_data();
    lcd_w_data(((uchar)(res_voltage_data_power)/100+'0'));
    lcd_w_data(((uchar)(res_voltage_data_power)%100/10+'0'));
    lcd_w_data(((uchar)(res_voltage_data_power)%10+'0'));
    lcd_w_data('W');
    lcd_w_cmd(0xC5);//

}

void Job_control(void)
{
    mos_control();
    if(working_condition==3)
        TR1=1;
    else
        TR1=0;
}

void mos_control(void)
{
    int T=0;
		T=temp_find();
    if(working_condition==0)
        MOS_control=0;
    else if(working_condition==1)
        MOS_control=1;
    else if(working_condition==2)
    {
        if(T>design_temperature)
        {
            MOS_control=0;
        }
        else if(T<(design_temperature-3))
        {
            MOS_control=1;
        }
    }
    else if(working_condition==3)
    {
        if(T>200)
        {
            MOS_control=0;
        }
        else if(T<(197))
        {
            MOS_control=1;
        }
    }

}
