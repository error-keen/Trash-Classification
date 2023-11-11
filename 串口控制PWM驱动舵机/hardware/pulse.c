#include "stm32f10x.h"                  // Device header
void Pulse_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//开启A类的时钟
	GPIO_InitTypeDef GPIO_InitStructure;//定义GPIO结构体
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	//为结构体工作模式赋值为推挽输出,高低电平都具有驱动能力
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	//输出速度为50mhz
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	//引脚赋值为全部引脚
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);
}
void Pulse_ON(void){
	GPIO_SetBits(GPIOA,GPIO_Pin_11);
}
void Pulse_OFF(void){
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);
}