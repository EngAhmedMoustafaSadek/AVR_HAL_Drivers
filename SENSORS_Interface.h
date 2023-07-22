

#ifndef SENSORS_INTERFACE_H_
#define SENSORS_INTERFACE_H_

//u16 SENSORS_TEMP_Read(void);
void SENSORS_TEMP_Read(void);
u16 SENSORS_GetTEMP(void);
void SENSORS_SetTEMP(u16 temp);

void SENSORS_Smoke_Read(void);
u16 SENSORS_GetSmoke(void);
void SENSORS_SetSmoke(u16 temp);

void SENSORS_ISR_CallBack(void);

u16 SENSORS_PRESS_Read(void);



#endif /* SENSORS_INTERFACE_H_ */