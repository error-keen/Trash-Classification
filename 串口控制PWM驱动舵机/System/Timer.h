#ifndef __TIMER_H
#define __TIMER_H

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


void Timer_Init(void);

#endif
