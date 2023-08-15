

#ifndef ULTRASONIC_PRIVATE_H_
#define ULTRASONIC_PRIVATE_H_

/******Timer Interrupts CallBack Functions*********/

void Ultrasonic_ICU_Func(void);
void Ultrasonic_TimerOVF_Func(void);
void Ultrasonic_TimerOCA_Func(void);
void Ultrasonic_TimerOCB_Func(void);
void Ultrasonic_Timer0_OC_Func(void);

#endif /* ULTRASONIC_PRIVATE_H_ */