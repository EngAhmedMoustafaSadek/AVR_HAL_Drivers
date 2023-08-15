
#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Interface.h"
#include "Timers_Interface.h"
#include "Ultrasonic_Interface.h"
#include "Ultrasonic_Private.h"
#include "Ultrasonic_Cfg.h"
#include "LCD_Interface.h"
#define F_CPU 8000000
#include <util/delay.h>

static volatile u8 flag=0;
static volatile u8 Trigger_Delay_Flag=0;
static volatile u8 Timeout_flag=0;
static volatile u16 T2=0;
static volatile u16 T1=0;
static u16 Distance=0;
static volatile u8 C=0;
static volatile u8 C1=0;
static volatile u16 K=0;

void Ultrasonic_Init(void)
{
	Timer1_OVF_InterruptEnable();
	//Timer1_ICU_InterruptEnable();
	OCR0=250;
	TIMER0_OC_SetCallBack(Ultrasonic_Timer0_OC_Func);
	Timer1_OVF_SetCallBack(Ultrasonic_TimerOVF_Func);
	Timer1_ICU_SetCallBack(Ultrasonic_ICU_Func);
}
void Ultrasonic_Trigger(DIO_Pin_type ultrasonic_pin)
{
	if(Trigger_Delay_Flag==0)
	{
		TIMER0_OC_InterruptEnable();
		Timer1_ICU_InterruptEnable();
		Timer1_InputCaptureEdge(RISING);
		DIO_WritePin(ultrasonic_pin,HIGH);
		_delay_us(10);
		DIO_WritePin(ultrasonic_pin,LOW);
		K=0;
		Trigger_Delay_Flag=1;
		Timeout_flag=0;
	}
}

Error_t Ultrasonic_DistanceCalc(void)
{
	if (Timeout_flag==1)
	{
		return OUTOFRANGE;
	}
	else if(flag==2)
	{
		//DIO_TogglePin(PIND7);
		u32 T = (T2-(s32)T1) + (C1*((u32)65536));
		Distance= T/58;
		flag=0;
		C1=0;
		return OK;	
	}
	return NOK;
}

u16 Ultrasonic_GetDistance(void)
{
	return Distance;
}

void Ultrasonic_ICU_Func(void)
{
	if (flag==0)
	{
		T1=ICR1;
		C=0;
		TCNT0=0;
		Timer1_InputCaptureEdge(FALLING);
		flag=1;
	}
	else if(flag==1 && Timeout_flag==0)
	{
		T2=ICR1;
		C1=C;
		Timer1_ICU_InterruptDisable();
		flag=2;
	}
}

void Ultrasonic_TimerOVF_Func(void)
{
	//DIO_TogglePin(PINC5);
	C++;
}

void Ultrasonic_Timer0_OC_Func(void)
{
	K++;
	if (K==240) //delay of min 60ms between each trigger refer to ultrasonic data sheet
	{
		//Timeout_flag=0;
		Trigger_Delay_Flag=0;
		TIMER0_OC_InterruptDisable();
	}
	if (K==94 && flag==1)   //timeout for out of range measurement max=400cm.
	{
		Timer1_ICU_InterruptDisable();
		Timeout_flag=1;
		//DIO_TogglePin(PINC7);
	}
}