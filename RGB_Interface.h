

#ifndef RGB_INTERFACE_H_
#define RGB_INTERFACE_H_

typedef enum {
	TIMER0_OC0=0,
	TIMER1_OC1A,
	TIMER1_OC1B,
	TIMER2_OC2
	}RGB_TimersPinUsed_t;
	
typedef struct {
	u8 red;
	u8 green;
	u8 blue;
	}RGB_Color_t;
	
void RGB_Init(RGB_TimersPinUsed_t red,RGB_TimersPinUsed_t green,RGB_TimersPinUsed_t blue);
void RGB_SetValue(RGB_Color_t color);
void RGB_ShiftColor(void);
void RGB_ShiftColorDelay(RGB_Color_t inputcolor1,RGB_Color_t inputcolor2,u8 delay);

#endif /* RGB_INTERFACE_H_ */