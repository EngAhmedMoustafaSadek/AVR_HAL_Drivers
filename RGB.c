#include "StdTypes.h"
#include "Timers_Interface.h"
#include "RGB_Interface.h"

#define F_CPU 8000000
#include <util/delay.h>
#include "LCD_Interface.h"

static RGB_TimersPinUsed_t TimersUsedArr[3];
static RGB_Color_t color1;
static RGB_Color_t color2;
static u16 DelayCounter=0;

void RGB_Init(RGB_TimersPinUsed_t red,RGB_TimersPinUsed_t green,RGB_TimersPinUsed_t blue)
{
	TimersUsedArr[0]=red;
	TimersUsedArr[1]=green;
	TimersUsedArr[2]=blue;
}
void RGB_SetValue(RGB_Color_t color)
{
	
		switch(TimersUsedArr[0])
		{
			case TIMER0_OC0:
			TIMER0_SetCompareValue(color.red);
			break;
			case TIMER1_OC1A:
			TIMER1_SetCompareValueA(color.red);
			break;
			case TIMER1_OC1B:
			TIMER1_SetCompareValueB(color.red);
			break;
			case TIMER2_OC2:
			TIMER2_SetCompareValue(color.red);
			break;
		}
		switch(TimersUsedArr[1])
		{
			case TIMER0_OC0:
			TIMER0_SetCompareValue(color.green);
			break;
			case TIMER1_OC1A:
			TIMER1_SetCompareValueA(color.green);
			break;
			case TIMER1_OC1B:
			TIMER1_SetCompareValueB(color.green);
			break;
			case TIMER2_OC2:
			TIMER2_SetCompareValue(color.green);
			break;
		}
		switch(TimersUsedArr[2])
		{
			case TIMER0_OC0:
			TIMER0_SetCompareValue(color.blue);
			break;
			case TIMER1_OC1A:
			TIMER1_SetCompareValueA(color.blue);
			break;
			case TIMER1_OC1B:
			TIMER1_SetCompareValueB(color.blue);
			break;
			case TIMER2_OC2:
			TIMER2_SetCompareValue(color.blue);
			break;
		}
}
void RGB_ShiftColor(void)
{
	static RGB_Color_t colorShiftTemp;
	static u8 flag=0;
	if (flag==0)
	{
		colorShiftTemp=color1;
		flag=1;
	}
	 /*(colorShiftTemp.red!=color2.red || colorShiftTemp.green!=color2.green || colorShiftTemp.blue!=color2.blue)*/
	
		if (colorShiftTemp.red!=color2.red)
		{
			if (colorShiftTemp.red>color2.red)
			{
				colorShiftTemp.red--;
			}
			else if(color1.red<color2.red)
			{
				colorShiftTemp.red++;
			}
		}
		if (colorShiftTemp.green!=color2.green)
		{
			if (colorShiftTemp.green>color2.green)
			{
				colorShiftTemp.green--;
			}
			else if(colorShiftTemp.green<color2.green)
			{
				colorShiftTemp.green++;
			}
		}
		if (colorShiftTemp.blue!=color2.blue)
		{
			if (colorShiftTemp.blue>color2.blue)
			{
				colorShiftTemp.blue--;
			}
			else if(colorShiftTemp.blue<color2.blue)
			{
				colorShiftTemp.blue++;
			}
		}
		RGB_SetValue(colorShiftTemp);
	if (colorShiftTemp.red==color2.red && colorShiftTemp.green==color2.green && colorShiftTemp.blue==color2.blue)
	{
		flag=0;
		TIMER2_OV_InterruptDisable();
	}
	
}
static void RGB_Delay(void)
{
	static u8 c=0;
	TIMER2_SetTimerValue(6);
	if(c==DelayCounter)
	{
		RGB_ShiftColor();
		c=0;
	}
	c++;
}
void RGB_ShiftColorDelay(RGB_Color_t inputcolor1,RGB_Color_t inputcolor2,u8 delay)
{
	color1=inputcolor1;
	color2=inputcolor2;
	TIMER2_OV_InterruptEnable();
	TIMER2_OV_SetCallBack(RGB_Delay);
	DelayCounter = (delay*(u32)1000)/250;
}