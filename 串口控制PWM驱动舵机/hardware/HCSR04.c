#include "stm32f10x.h"                  // Device header
#include "HCSR04.h"
#include "Timer.h"
#include "Delay.h"

uint16_t Time;

void HCSR04_Init(void)
{
	RCC_APB2PeriphClockCmd(Trig_RCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = Trig_Pin1|Trig_Pin2|Trig_Pin3|Trig_Pin4|Trig_Pin5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Trig_Port, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = Echo_Pin1|Echo_Pin2|Echo_Pin3|Echo_Pin4|Echo_Pin5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Echo_Port, &GPIO_InitStruct);
	
	GPIO_ResetBits(Trig_Port, Trig_Pin1|Trig_Pin2|Trig_Pin3|Trig_Pin4|Trig_Pin5);
	
//	RCC_APB2PeriphClockCmd(Trig_RCC1, ENABLE);
//	
//	
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStruct.GPIO_Pin = Trig_Pin4;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(Trig_Port1, &GPIO_InitStruct);
//	
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
//	GPIO_InitStruct.GPIO_Pin = Echo_Pin4;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(Echo_Port1, &GPIO_InitStruct);
//	
//	GPIO_ResetBits(Trig_Port1, Trig_Pin4);
	
}


void HCSR04_Start(void)
{
	GPIO_SetBits(Trig_Port, Trig_Pin1);
	Delay_us(45);
	GPIO_ResetBits(Trig_Port, Trig_Pin1);
	Timer_Init();
}


uint16_t HCSR04_GetValue(void)
{
	HCSR04_Start();
	Delay_ms(100);
	return ((Time * 0.0001) * 34000) / 2;
//	return Time;
}

void HCSR041_Start(void)
{
	GPIO_SetBits(Trig_Port, Trig_Pin2);
	Delay_us(45);
	GPIO_ResetBits(Trig_Port, Trig_Pin2);
	Timer_Init();
}


uint16_t HCSR041_GetValue(void)
{
	HCSR041_Start();
	Delay_ms(100);
	return ((Time * 0.0001) * 34000) / 2;
//	return Time;
}

void HCSR042_Start(void)
{
	GPIO_SetBits(Trig_Port, Trig_Pin3);
	Delay_us(45);
	GPIO_ResetBits(Trig_Port, Trig_Pin3);
	Timer_Init();
}


uint16_t HCSR042_GetValue(void)
{
	HCSR042_Start();
	Delay_ms(100);
	return ((Time * 0.0001) * 34000) / 2;
//	return Time;
}

void HCSR043_Start(void)
{
	GPIO_SetBits(Trig_Port, Trig_Pin4);
	Delay_us(45);
	GPIO_ResetBits(Trig_Port, Trig_Pin4);
	Timer_Init();
}


uint16_t HCSR043_GetValue(void)
{
	HCSR043_Start();
	Delay_ms(100);
	return ((Time * 0.0001) * 34000) / 2;
//	return Time;
}

void HCSR044_Start(void)
{
	GPIO_SetBits(Trig_Port, Trig_Pin5);
	Delay_us(45);
	GPIO_ResetBits(Trig_Port, Trig_Pin5);
	Timer_Init();
}


uint16_t HCSR044_GetValue(void)
{
	HCSR044_Start();
	Delay_ms(100);
	return ((Time * 0.0001) * 34000) / 2;
//	return Time;
}
