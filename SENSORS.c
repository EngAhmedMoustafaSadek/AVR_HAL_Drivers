
#include "StdTypes.h"
#include "ADC_Interface.h"
#include "SENSORS_Interface.h"
#include "SENSORS_Cfg.h"

static u16 TEMP=300;
static u16 Smoke=0;


/*
u16 SENSORS_TEMP_Read(void)
{
	u16 adc=ADC_VoltRead(LM35_CH);

	u16 temp=(adc*(u32)5000)/1024;
	
	return temp;
	
}*/
void SENSORS_TEMP_Read(void)
{
	u16 adc=ADC_Read_INT();
	u16 temp=(adc*(u32)5000)/1024;
	SENSORS_SetTEMP(temp);
}
void SENSORS_SetTEMP(u16 temp)
{
	TEMP=temp;
}
u16 SENSORS_GetTEMP(void)
{
	return TEMP;
}
void SENSORS_Smoke_Read(void)
{
	u16 adc=ADC_Read_INT();
	u16 smk=(adc*(u32)5000)/1024;
	SENSORS_SetSmoke((smk*(u32)100)/5000);
}
void SENSORS_SetSmoke(u16 smk)
{
	Smoke=smk;
}
u16 SENSORS_GetSmoke(void)
{
	return Smoke;
}

void SENSORS_ISR_CallBack(void)
{
	if (ADC_GetChannel()==LM35_CH)
	{
		SENSORS_TEMP_Read();
		ADC_StartConversion_INT(SMOKE_CH);
	}
	else if (ADC_GetChannel()==SMOKE_CH)
	{
		SENSORS_Smoke_Read();
		ADC_StartConversion_INT(LM35_CH);
	}
}

u16 SENSORS_PRESS_Read(void)
{
	u16 adc=ADC_Read(MPX4115_CH);
	
	u16 press= ((((u32)1000*(adc-55))+460)/921)+150;
	
	return press;
	
}
