
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "Timers_Interface.h"
#include "Ultrasonic_Interface.h"
#include "Ultrasonic_Cfg.h"
#define F_CPU 8000000
#include <util/delay.h>

static volatile u8 flag=0;
static volatile u16 T2,T1=0;
static u16 Distance=0;
static volatile u32 C=0;

void Ultrasonic_Init(void)
{
	Timer1_OVF_InterruptEnable();
	Timer1_ICU_InterruptEnable();
	Timer1_OVF_SetCallBack(Ultrasonic_TimerOVF_Func);
	Timer1_ICU_SetCallBack(Ultrasonic_ICU_Func);
	Timer1_InputCaptureEdge(RISING);
}
void Ultrasonic_Trigger(DIO_Pin_type ultrasonic_pin)
{
	DIO_WritePin(ultrasonic_pin,HIGH);
	_delay_us(10);
	DIO_WritePin(ultrasonic_pin,LOW);
	C=0;
}

void Ultrasonic_DistanceCalc(void)
{
	if (flag==2)
	{
		u32 T = T2-T1 + (u32)C*65535;
		Distance= (u32)T/58;
		flag=0;
		C=0;
		_delay_ms(60);
	}
	
}

u16 Ultrasonic_GetDistance(void)
{
	return Distance;
}

void Ultrasonic_ICU_Func(void)
{
	if (flag==0)
	{
		T1=TIMER1_GetICUValue();
		Timer1_InputCaptureEdge(FALLING);
		flag=1;
	}
	else if(flag==1)
	{
		T2=TIMER1_GetICUValue();
		Timer1_InputCaptureEdge(RISING);
		flag=2;
	}
}

void Ultrasonic_TimerOVF_Func(void)
{
	C++;
}