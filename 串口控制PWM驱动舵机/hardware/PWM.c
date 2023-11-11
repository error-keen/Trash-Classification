#include "stm32f10x.h"                  // Device header
void PWM_Init(void){
	//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//GPIO初始化
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//1分频
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
	
	TIM_TimeBaseInitStruct.TIM_Period=20000-1;//ARR自动重装值-1
	TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;//预分频器PSC的预分频值-1
	//设置分频后为1kHz,定时1s,两者取值不能超65535
	
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//重复计数器,高级计数器才有,TIM2是通用计数器
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	//初始化输出比较单元
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);//给结构体赋初始值
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=0;//CCR占空比
	TIM_OC2Init(TIM2,&TIM_OCInitStruct);//通道2
	
	TIM_OCStructInit(&TIM_OCInitStruct);//给结构体赋初始值
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=0;//CCR占空比
	TIM_OC3Init(TIM2,&TIM_OCInitStruct);//通道3
	
	TIM_OCStructInit(&TIM_OCInitStruct);//给结构体赋初始值
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=0;//CCR占空比
	TIM_OC4Init(TIM2,&TIM_OCInitStruct);//通道3
	
	//启动定时器
	TIM_Cmd(TIM2,ENABLE);
}
void PWM_SetCompare2(uint16_t Compare){
	TIM_SetCompare2(TIM2,Compare);
}
void PWM_SetCompare3(uint16_t Compare){
	TIM_SetCompare3(TIM2,Compare);
}
void PWM_SetCompare4(uint16_t Compare){
	TIM_SetCompare4(TIM2,Compare);
}
