#include "StdTypes.h"
#include "DIO_Interface.h"
#include "MOTOR_Interface.h"
#include "MOTOR_Cfg.h"


typedef struct{
	
	DIO_Pin_type en;
	DIO_Pin_type in1;
	DIO_Pin_type in2;
	
	}MOTOR_Pin_type;

MOTOR_Pin_type MOTOR_Pin_Arr[4]={{M1_EN,M1_IN1,M1_IN2},{M2_EN,M2_IN1,M2_IN2},{M3_EN,M3_IN1,M3_IN2},{M4_EN,M4_IN1,M4_IN2}};
	
void MOTOR_Init(void)
{
	switch(MOTOR_INIT_STATE)
	{
		case STOP:
		MOTOR_Stop(M1);
		MOTOR_Stop(M2);
		MOTOR_Stop(M3);
		MOTOR_Stop(M4);
		break;
		case CW:
		MOTOR_CW(M1);
		MOTOR_CW(M2);
		MOTOR_CW(M3);
		MOTOR_CW(M4);
		break;
		case CCW:
		MOTOR_CCW(M1);
		MOTOR_CCW(M2);
		MOTOR_CCW(M3);
		MOTOR_CCW(M4);
		break;
	}
}
void MOTOR_Stop (MOTOR_type m)
{
	DIO_WritePin(MOTOR_Pin_Arr[m].en,LOW);
	DIO_WritePin(MOTOR_Pin_Arr[m].in1,LOW);
	DIO_WritePin(MOTOR_Pin_Arr[m].in2,LOW);
}
void MOTOR_CW (MOTOR_type m)
{
	DIO_WritePin(MOTOR_Pin_Arr[m].en,HIGH);
	DIO_WritePin(MOTOR_Pin_Arr[m].in1,HIGH);
	DIO_WritePin(MOTOR_Pin_Arr[m].in2,LOW);
}
void MOTOR_CCW (MOTOR_type m)
{
	DIO_WritePin(MOTOR_Pin_Arr[m].en,HIGH);
	DIO_WritePin(MOTOR_Pin_Arr[m].in1,LOW);
	DIO_WritePin(MOTOR_Pin_Arr[m].in2,HIGH);
}
void MOTOR_Speed (MOTOR_type m, u8 speed)
{
	
}
