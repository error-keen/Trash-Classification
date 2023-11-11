#include "stm32f10x.h"                  // Device header
#include "PWM.H"

void Servo_Init(void){
	PWM_Init();
}
void Servo_SetAngles(float Angle){
	PWM_SetCompare2(Angle/270*2000+500);
}
void Servo_SetAngles2(float Angle){
	PWM_SetCompare3(Angle/270*2000+500);
}
void Servo_SetAngles3(float Angle){
	PWM_SetCompare4(Angle/180*2000+500);
}