

#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_


void Ultrasonic_Init(void);
void Ultrasonic_Trigger(DIO_Pin_type ultrasonic_pin);
void Ultrasonic_ICU_Func(void);
void Ultrasonic_DistanceCalc(void);
void Ultrasonic_TimerOVF_Func(void);
u16 Ultrasonic_GetDistance(void);
void Ultrasonic_Runnable(void);
#endif /* ULTRASONIC_INTERFACE_H_ */