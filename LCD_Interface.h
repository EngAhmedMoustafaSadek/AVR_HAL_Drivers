

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

typedef enum{
	line1=0,
	line2=1
	}LCD_Line_type;

void LCD_Init(void);
void LCD_WriteChar(u8 ch);
void LCD_WriteString(c8* str);
void LCD_WriteNumber(s32 num);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u8 num);
void LCD_GoTo(LCD_Line_type line,u8 cell);
void LCD_ClearPosition(LCD_Line_type line,u8 cell,u8 NoCells);
void LCD_Clear(void);
void LCD_WriteStringGoto(LCD_Line_type line,u8 cell,c8* str);
void LCD_CustomChar(u8 address,u8* customchar);
u8 LCD_GetCursor(void);

#endif /* LCD_INTERFACE_H_ */