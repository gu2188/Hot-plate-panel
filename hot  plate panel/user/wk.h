#ifndef _WK_H_
#define _WK_H_

#include<reg52.h>
#include<string.h>
#include<intrins.h>
#include<math.h>
#define u32 unsigned long int
#define uchar unsigned char
#define uint unsigned int
void variable_init(void);
void delay(uint x);
//LCD1602
sbit RS=P2^2;
sbit RW=P2^1;
sbit E=P2^0;
//sbit RS=P2^6;
//sbit RW=P2^5;
//sbit E=P2^7;
#define LCD_DB P0
//---------------------
void lcd_init(void);
uchar lcd_Read_state(void);
void lcd_w_cmd(uchar com);
void lcd_w_data(uchar data_);
//***************************

//ADC
extern unsigned int res_voltage_data;
extern double res_voltage_data_power;
extern unsigned int thermistor_voltage_data;
extern u32 thermistor_voltage_data_power;
//----------------------
void ADC_initialize(void);
void adc_res_voltage(void);
void adc_res_voltage_data(void);
void adc_thermistor_voltage(void);
void adc_thermistor_voltage_data(void);
//------------------------
sfr ADC_CONTR=0XBC;
sfr ADC_RES=0XBD;
sfr ADC_RESL=0XBE;
sfr AUXR1=0XA2;
sfr IPH=0XB7;
sfr P1ASF=0X9D;
//****************************
sfr AUXR=0X8E;

//_interrupt , key , design temperature and timer
extern unsigned int working_condition;
extern unsigned int adjustment_range;
extern double res_voltage_data_power;
extern unsigned int adjustment_range_data[4];
extern int design_temperature;
//---------------------------
sbit Ex_interrupt_0=P3^2;
sbit Ex_interrupt_1=P3^3;
sbit key3=P2^3;
sbit key4=P2^4;
//---------------------------
void Always_interrupt_init(void);
void timer0_init(void);
void timer1_init(void);
//**********************************

//LCD_ACCORDING AND Job control
sbit MOS_control=P3^4;
//------------------------------
void According_lcd(void);
void Job_control(void);
void mos_control(void);
//*****************************
extern u32 code NTCcode[];

int temp_find();
//IO init
sfr P3M1=0XB1;
sfr P3M0=0XB2;
sfr P1M1=0X91;
sfr P1M0=0X92;
#endif