#include "StdTypes.h"
#include "DIO_Interface.h"
#include "Utils.h"
#include "LCD_Private.h"
#include "LCD_Interface.h"
#include "LCD_Cfg.h"

#define F_CPU 8000000
#include <util/delay.h>

static u8 LCD_Cursor=0;
static LCD_Line_type LCD_Current_Line=line1;

// static u8 string_len(u8* str)
// {
// 	u8 i;
// 	for (i = 0; str[i]; i++);
//
// 	return i;
// }
// static void reverseString(u8* str)
// {
// 	u8 c = string_len(str);
// 	u8 temp = 0;
// 	for (u8 i = 0; i < c / 2; i++)
// 	{
// 		temp = str[i];
// 		str[i] = str[c - i - 1];
// 		str[c - i - 1] = temp;
// 	}
// }
// static void Num_To_String(s32 num,u8* str)
// {
// 	u8 i=0;
// 	if(num>=0)
// 	{
// 		while(num)
// 		{
// 			str[i]=num%10 +'0';
// 			num=num/10;
// 			i++;
// 		}
// 		reverseString(str);
// 		str[i]=0;
// 	}
// 	else
// 	{
// 		num=num*-1;
// 		while(num)
// 		{
// 			str[i]=num%10 +'0';
// 			num=num/10;
// 			i++;
// 		}
// 		str[i]='-';
// 		reverseString(str);
// 		str[i+1]=0;
// 	}
//
// }

#if LCD_Mode == _8_BIT
static void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN_LCD,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN_LCD,LOW);
	_delay_ms(1);
}

static void WriteData(u8 data)
{	
	DIO_WritePin(RS,HIGH);	
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN_LCD,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN_LCD,LOW);
	_delay_ms(1);
	
}

void LCD_Init(void)
{
	_delay_ms(50);
	
	WriteIns(0x38);
	WriteIns(0x0c); //0x0e,0x0f
	WriteIns(0x01);//clear screen
	_delay_ms(1);
	WriteIns(0x06);
}

#else
static void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,Read_BIT(ins,7));
	DIO_WritePin(D6,Read_BIT(ins,6));
	DIO_WritePin(D5,Read_BIT(ins,5));
	DIO_WritePin(D4,Read_BIT(ins,4));
	
	DIO_WritePin(EN_LCD,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN_LCD,LOW);
	_delay_ms(1);
	
	DIO_WritePin(D7,Read_BIT(ins,3));
	DIO_WritePin(D6,Read_BIT(ins,2));
	DIO_WritePin(D5,Read_BIT(ins,1));
	DIO_WritePin(D4,Read_BIT(ins,0));
	
	DIO_WritePin(EN_LCD,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN_LCD,LOW);
	_delay_ms(1);
}

static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,Read_BIT(data,7));
	DIO_WritePin(D6,Read_BIT(data,6));
	DIO_WritePin(D5,Read_BIT(data,5));
	DIO_WritePin(D4,Read_BIT(data,4));
	
	DIO_WritePin(EN_LCD,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN_LCD,LOW);
	_delay_ms(1);
	
	DIO_WritePin(D7,Read_BIT(data,3));
	DIO_WritePin(D6,Read_BIT(data,2));
	DIO_WritePin(D5,Read_BIT(data,1));
	DIO_WritePin(D4,Read_BIT(data,0));
	
	DIO_WritePin(EN_LCD,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN_LCD,LOW);
	_delay_ms(1);
	
}

void LCD_Init(void)
{
	_delay_ms(50);
	
	WriteIns(0x02);
	WriteIns(0x28);
	WriteIns(0x0c); //0x0e,0x0f
	WriteIns(0x01);//clear screen
	_delay_ms(1);
	WriteIns(0x06);
}
#endif

void LCD_WriteChar(u8 ch)
{
	if((LCD_Cursor==15))
	{
		LCD_GoTo(line2,0);
	}
	else if((LCD_Cursor==31))
	{
		LCD_GoTo(line1,0);
		LCD_Cursor=0;
	}
	WriteData(ch);
	LCD_Cursor++;
}

void LCD_WriteString(c8* str)
{
	u8 i;
	for(i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
}

void LCD_WriteNumber(s32 num)
{
	u8 str_num[20]={0};
	s8 i=0;
	/*Num_To_String(num,str_num); //another implementation
	LCD_WriteString(str_num);*/
	
	if(num==0)
	{
		LCD_WriteChar('0');
	}
	if(num<0)
	{
		LCD_WriteChar('-');
		num=num*(-1);
	}
	
	while(num)
	{
		str_num[i]=num%10 +'0';
		num=num/10;
		i++;
	}
	i--;
	for(;i>=0;i--)
	{
		LCD_WriteChar(str_num[i]);
	}
}
void LCD_WriteBinary(u8 num)
{
	s8 i;
	for(i=7;i>=0;i--)
	{
		//LCD_WriteChar(Read_BIT(num,i)?'1':'0');
		LCD_WriteChar(Read_BIT(num,i)+'0');
	}
	/*u8 i;        //another implementation
	u8 str[9]={0};
	for(i=0;i<8;i++)
	{
		if((num>>i)&1)
		{
			str[i]='1';
		}
		else
		{
			str[i]='0';
		}
	}
	reverseString(str);
	str[i]=0;
	LCD_WriteString(str);*/
	
}

void LCD_WriteHex(u8 num)
{
	u8 HN=num>>4;
	u8 LN=num&0x0f;
	if (HN<10)
	{
		LCD_WriteChar(HN+'0');
	}
	else
	{
		LCD_WriteChar(HN-10+'A');
	}
	if (LN<10)
	{
		LCD_WriteChar(LN+'0');
	}
	else
	{
		LCD_WriteChar(LN-10+'A');
	}
	
	/*u8 str_num[20]={0};
	s8 i=0;
	
	if(num==0)
	{
		LCD_WriteChar('0');
	}
	if(num<0)
	{
		LCD_WriteChar('-');
		num=num*(-1);
	}
	
	while(num)
	{
		if((num%16)>9)
		{
			str_num[i]=((num%16)-10) +'A';
		}
		else
		{
			str_num[i]=num%16 +'0';
		}
		num=num/16;
		i++;
	}
	
	for(;i>=0;i--)
	{
		LCD_WriteChar(str_num[i]);
	}*/
}

void LCD_GoTo(LCD_Line_type line,u8 cell)
{
	if(line==line1)
	{
		WriteIns(0x80+cell);
		LCD_Cursor=cell;
	}
	else if(line==line2)
	{
		WriteIns(0x80+0x40+cell);
		LCD_Cursor=cell+15;
	}
}
u8 LCD_GetCursor(void)
{
	return LCD_Cursor;
}

void LCD_WriteStringGoto(LCD_Line_type line,u8 cell,c8* str)
{
	LCD_GoTo(line,cell);
	LCD_WriteString(str);
}

void LCD_ClearPosition(LCD_Line_type line,u8 cell,u8 NoCells)
{
	u8 i;
	LCD_GoTo(line,cell);
	for(i=0;i<NoCells;i++)
	{
		LCD_WriteChar(' ');
	}
}
void LCD_CustomChar(u8 address,u8* customchar)
{
	u8 i;	
	if(address<8)
	{
		address=0x40+(address*8);
		WriteIns(address);
		for(i=0;i<8;i++)
		{
			_delay_ms(1);
			WriteData(customchar[i]);
		}
		WriteIns(0x80);
	}
	
}

void LCD_Clear(void)
{
	WriteIns(0x01);
	LCD_Cursor=0;
	LCD_Current_Line=line1;
}