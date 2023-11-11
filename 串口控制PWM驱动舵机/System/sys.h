#ifndef SYS_H
#define SYS_H
#include "stm32f10x.h"                  // Device header
#include "OLED.H"
#include "Servo.H"
#include "Delay.h"
#include "serial.h"
#include "string.h"
#include "HCSR04.h"
#include "Timer.h"
#include "Key.h"
#include "Pulse.h"
uint16_t Angle1=0;//�ɻ���
uint16_t Angle2=90;//���ɻ���
uint16_t Angle3=180;//�к�
uint16_t Angle4=270;//����
uint8_t KeyNum;
uint16_t distance1;//������1����
uint16_t distance2;//������2����
uint16_t distance3;//������3����
uint16_t distance4;//������4����
uint16_t distance5;//������5����
uint16_t flag=0;

#endif
