

#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_



void Ultrasonic_Init(void);

void Ultrasonic_Trigger(DIO_Pin_type ultrasonic_pin);

Error_t Ultrasonic_DistanceCalc(void);

u16 Ultrasonic_GetDistance(void);
//void Ultrasonic_Runnable(void);

#endif /* ULTRASONIC_INTERFACE_H_ */