#include "stm32f10x.h"
#include "CSB.h"
#include "Delay.h"

uint64_t timek;
uint64_t timej;
uint32_t dintance;

void csbInit()
{
	GPIO_InitTypeDef GPIOA_Structure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIOA_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOA_Structure.GPIO_Pin = GPIO_Pin_11;//Trig
	GPIOA_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOA_Structure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);
	
	GPIOA_Structure.GPIO_Mode = GPIO_Mode_IPD;
	GPIOA_Structure.GPIO_Pin = GPIO_Pin_10;//Echo
	GPIO_Init(GPIOA,&GPIOA_Structure);
	
}
uint16_t csbceju()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_11);
	Delay_us(15);
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);
	
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0);
	timek=0;
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==1);
	timej=timek;
	
	if(timej/100<38)
	{
	 dintance=timej*346/200;//mm
	}
	
	return dintance;
}


//void TIM2_IRQHandler()
//{
//		if(TIM_GetITStatus(TIM2,TIM_IT_Update) == 1)
//    {
//		 timek++;
//		 TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//    }
//}
