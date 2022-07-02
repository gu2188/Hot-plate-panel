#include"wk.h"

void lcd_init(void)
{
    lcd_w_cmd(0x3c);
    lcd_w_cmd(0x0c);
    lcd_w_cmd(0x01);
    lcd_w_cmd(0x06);
}
uchar lcd_Read_state(void)
{
    uchar s;
    RW=1;
    delay(200);
    RS=0;
    delay(200);
    E=1;
    delay(200);
    s=LCD_DB;
    delay(200);
    E=0;
    delay(200);
    RW=0;
    delay(200);
    return(s);
}
void lcd_w_cmd(uchar com)
{
    uchar i;
    do
    {
        i=lcd_Read_state();
        i=i&0x80;
        delay(200);
    }
    while (i!=0);
    RW=0;
    delay(200);
    RS=0;
    delay(200);
    E=1;
    delay(200);
    LCD_DB=com;
    delay(200);
    E=0;
    delay(200);
    RW=1;
    delay(200);
}
void lcd_w_data(uchar data_)
{
    uchar i;
    do
    {
        i=lcd_Read_state();
        i=i&0x80;
        delay(200);
    }
    while (i!=0);
    RW=0;
    delay(200);
    RS=1;
    delay(200);
    E=1;
    delay(200);
    LCD_DB=data_;
    delay(200);
    E=0;
    delay(200);
    RW=1;
    delay(200);
}