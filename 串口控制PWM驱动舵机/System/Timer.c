#include "stm32f10x.h"                  // Device header
#include "Timer.h"

extern uint16_t Time;
void Timer_Init(void)
{
	Time = 0;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//选择APB1总线下的定时器Timer2
	
	TIM_InternalClockConfig(TIM3);		//TIM2使用内部时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		//计数模式，此处为向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 7199;		//ARR 1 = 0.0001S
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		//高级计时器特有，重复计数
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);		//使能中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;		//中断通道选择
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//优先级，同上
	
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3, ENABLE);		//打开定时器
}

void TIM3_IRQHandler()		//定时器2的中断函数，不懂直接套用
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{

		if (GPIO_ReadInputDataBit(Echo_Port, Echo_Pin1|Echo_Pin2|Echo_Pin3|Echo_Pin4|Echo_Pin5) == 1)
		{
			Time ++;
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);		//清空标志位
	}
}
