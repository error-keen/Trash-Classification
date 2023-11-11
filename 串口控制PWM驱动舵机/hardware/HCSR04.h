#ifndef __HCSR04_H
#define __HCSR04_H

#define Trig_Port 		GPIOB
#define Trig_Pin1 		GPIO_Pin_0
#define Trig_Pin2 		GPIO_Pin_6
#define Trig_Pin3		GPIO_Pin_5
#define Trig_Pin4 		GPIO_Pin_11
#define Trig_Pin5 		GPIO_Pin_13
#define Trig_RCC		RCC_APB2Periph_GPIOB

#define Echo_Port 		GPIOB
#define Echo_Pin1 		GPIO_Pin_1
#define Echo_Pin2 		GPIO_Pin_7
#define Echo_Pin3 		GPIO_Pin_10
#define Echo_Pin4		GPIO_Pin_12
#define Echo_Pin5		GPIO_Pin_14
#define Echo_RCC		RCC_APB2Periph_GPIOB


void HCSR04_Init(void);
uint16_t HCSR041_GetValue(void);
uint16_t HCSR042_GetValue(void);
uint16_t HCSR043_GetValue(void);
uint16_t HCSR04_GetValue(void);
uint16_t HCSR044_GetValue(void);

#endif 

//#define Trig_Port 		GPIOA
//#define Trig_Pin1 		GPIO_Pin_11
//#define Trig_Pin2 		GPIO_Pin_5
//#define Trig_Pin3		GPIO_Pin_7
//#define Trig_RCC		RCC_APB2Periph_GPIOA

//#define Echo_Port 		GPIOA
//#define Echo_Pin1 		GPIO_Pin_4
//#define Echo_Pin2 		GPIO_Pin_6
//#define Echo_Pin3 		GPIO_Pin_8
//#define Echo_RCC		RCC_APB2Periph_GPIOA

//#define Trig_Port1 		GPIOB
//#define Trig_Pin4 		GPIO_Pin_12

//#define Echo_Port1 		GPIOB
//#define Echo_Pin4 		GPIO_Pin_4

//#define Trig_RCC1		RCC_APB2Periph_GPIOB
//#define Echo_RCC1		RCC_APB2Periph_GPIOB
