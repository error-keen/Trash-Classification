#include "SYS.H"
/*
  CN5投放舵机
  CN4压缩舵机
  CN3云台舵机
  */
uint16_t Angle=140;
void JudgeSort(void){
	if(Serial_RxFlag==1){
//		OLED_ShowString(4,1,"                ");
//		OLED_ShowString(4,1,Serial_RxPacket);
		if(strcmp(Serial_RxPacket,"ylg")==0){
//			OLED_ShowString(2,1,"                ");
//			OLED_ShowString(2,1,"ylg_OK");
//			Serial_SendString("ylg_OK\r\n");
			Delay_ms(500);
			if(distance1<10||distance1>100){
				Serial_SendString("full_2\r\n");
				OLED_ShowString(1,5,"1");
			}
			Servo_SetAngles(0);
			Delay_ms(1500);
			Servo_SetAngles3(35);
			Delay_ms(1500);
			Servo_SetAngles3(Angle);
			Delay_ms(1500);
			Pulse_ON();
			Delay_ms(15000);
			Pulse_OFF();
			Delay_ms(1500);
			Servo_SetAngles2(0);
			Delay_ms(1500);
			Servo_SetAngles2(90);
			Servo_SetAngles(0);
			Serial_SendString("OK\r\n");
		}
			else if(strcmp(Serial_RxPacket,"Recyclable")==0){
//				OLED_ShowString(2,1,"                ");
//				OLED_ShowString(2,1,"Recyclable_OK");
//				Delay_ms(500);
//				Serial_SendString("Recyclable_OK\r\n");
				
				if(distance1<10||distance1>100){
					Serial_SendString("full_2\r\n");
					OLED_ShowString(1,5,"1");
				}
				Servo_SetAngles(0);
				Delay_ms(1500);
				Servo_SetAngles3(35);
				Delay_ms(1500);
				Servo_SetAngles3(Angle);
				Delay_ms(1500);
				Servo_SetAngles2(0);
				Delay_ms(1500);
				Servo_SetAngles2(90);
				Servo_SetAngles(0);
				Serial_SendString("OK\r\n");
				
			}
			  else if(strcmp(Serial_RxPacket,"Harmful")==0){
//				  OLED_ShowString(2,1,"                ");
//				  OLED_ShowString(2,1,"Harmfull_OK");
//				  Serial_SendString("Harmfull_OK\r\n");
//				  Delay_ms(500);
				  
				  if(distance2<10||distance2>100){
					  Serial_SendString("full_1\r\n");
					  OLED_ShowString(2,5,"2");
				  }
				  Servo_SetAngles(90);
				  Delay_ms(1500);
				  Servo_SetAngles3(35);
				  Delay_ms(1500);
				  Servo_SetAngles3(Angle);
				  Delay_ms(1500);
				  Servo_SetAngles(0);
				  Serial_SendString("OK");
				  
			  }
			  else if(strcmp(Serial_RxPacket,"Other")==0){
//				  OLED_ShowString(2,1,"                ");
//				  OLED_ShowString(2,1,"Other_OK");
//				  Serial_SendString("Other_OK\r\n");
//				  Delay_ms(500);
				 
				  if(distance3<10||distance3>100){
					  Serial_SendString("full_4\r\n");
					   OLED_ShowString(3,5,"3");
				  }
				  
				  Servo_SetAngles(180);
				  Delay_ms(1500);
				  Servo_SetAngles3(35);
				  Delay_ms(1500);
				  Servo_SetAngles3(Angle);
				  Delay_ms(1500);
				  Servo_SetAngles(0);
				  Serial_SendString("OK");

			  }
			  else if(strcmp(Serial_RxPacket,"KitchenWaste")==0){
//				  OLED_ShowString(2,1,"                ");
//				  OLED_ShowString(2,1,"KitchenWaste_OK");
//				  Serial_SendString("KitchenWaste_OK\r\n");
				  
				  if(distance4<10||distance4>100){
					  Serial_SendString("full_3\r\n");
					  OLED_ShowString(4,5,"4");
				  }
				  Servo_SetAngles(270);
				  Delay_ms(1500);
				  Servo_SetAngles3(35);
				  Delay_ms(1500);
				  Servo_SetAngles3(Angle);
				  Delay_ms(1500);
				  Servo_SetAngles(0);
				  Serial_SendString("OK");
				  
			  }
			  else
			  {
				  Serial_SendString("ERROR_COMMAND\r\n");
				  OLED_ShowString(2,1,"                "); 
				  OLED_ShowString(2,1,"ERROR_COMMAND");
				  Delay_ms(500);
			  }
			  Serial_RxFlag=0;
		  }	
}
void start(){
	
	distance1 = HCSR04_GetValue();
	distance2 = HCSR041_GetValue();
	distance3 = HCSR042_GetValue();
	distance4 = HCSR043_GetValue();
	distance5 = HCSR044_GetValue();
	OLED_ShowNum(1, 1, distance1, 3);
	OLED_ShowNum(2, 1, distance2, 3);
	OLED_ShowNum(3, 1, distance3, 3);
	OLED_ShowNum(4, 1, distance4, 3);
//	OLED_ShowNum(1, 5, distance5, 3);
	if(distance5<10){
		Serial_SendString("OK\r\n");
//		Delay_ms(11000);
//		OLED_ShowString(1,1,"1");
	}
	JudgeSort();
	
}
int main(void){
	
	OLED_Init();
	Servo_Init();
	HCSR04_Init();
	Serial_Init();
	Timer_Init();
	Key_Init();
	Pulse_Init();
	
//	Servo_SetAngles2(80);
////	Delay_ms(1500);
//	Servo_SetAngles3(140);
////	Delay_ms(1500);
////	Servo_SetAngles3(Angle);
////	Delay_ms(1500);
////	Pulse_ON();
////	Delay_ms(15000);
////	Pulse_OFF();
////	Servo_SetAngles2(0);
////	Delay_ms(5000);
//////	Servo_SetAngles2(100);
//	Servo_SetAngles(0);
	

//	uint32_t ch=0;
////	
//	while(1){
////		Serial_SendNum(ch,10);
////		ch++;
//		OLED_ShowString(2,1,"1");
//		Serial_SendString("OK\r\n");
////		Delay_ms(10);
//		if(Serial_RxFlag==1)
//			{
//			OLED_ShowString(1,1,Serial_RxPacket);
//			Serial_RxFlag=0;
//			}
//	}
	


	while(1){
		start();
	}
//	
//	
//	Serial_SendString("OK");
//	while(1){
//		distance1 = HCSR041_GetValue();
//		distance2 = HCSR04_GetValue();
//		distance3 = HCSR042_GetValue();
//		distance4 = HCSR043_GetValue();
//		distance5 = HCSR044_GetValue();
//		if(distance5){
//			Serial_SendString("OK");
//		}
//		KeyNum=Key_GetNum();
//		if(flag%2==0){
//			JudgeSort();
//			OLED_ShowString(1,1,"TxPacket:");
//			OLED_ShowString(3,1,"RxPacket:");
//		}
//		if(KeyNum==1)
//		{
//			flag++;
//			OLED_Clear();
//		}
//		if(flag%2!=0){
//			OLED_ShowString(1, 1, "distance:");
//			OLED_ShowString(1, 13, "cm");
//			OLED_ShowString(2, 1, "distance:");
//			OLED_ShowString(2, 13, "cm");
//			OLED_ShowString(3, 1, "distance:");
//			OLED_ShowString(3, 13, "cm");
//			OLED_ShowString(4, 1, "distance:");
//			OLED_ShowString(4, 13, "cm");
//			OLED_ShowNum(1, 10, distance1, 3);
//			OLED_ShowNum(2, 10, distance2, 3);
//			OLED_ShowNum(3, 10, distance3, 3);
//			OLED_ShowNum(4, 10, distance4, 3);
//			Delay_ms(100);
//			if(distance1!=22){
//				Serial_SendString("FULL-1"){
//			}
//			if(distance2!=22){
//				Serial_SendString("FULL-2"){
//			}
//			if(distance3!=22){
//				Serial_SendString("FULL-3");
//			}
//			if(distance4!=22){
//				Serial_SendString("FULL-4");
//			}
//		}
//	}
}
