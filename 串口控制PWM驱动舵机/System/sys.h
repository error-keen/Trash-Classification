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
uint16_t Angle1=0;//¿É»ØÊÕ
uint16_t Angle2=90;//²»¿É»ØÊÕ
uint16_t Angle3=180;//ÓĞº¦
uint16_t Angle4=270;//³øÓà
uint8_t KeyNum;
uint16_t distance1;//³¬Éù²¨1¾àÀë
uint16_t distance2;//³¬Éù²¨2¾àÀë
uint16_t distance3;//³¬Éù²¨3¾àÀë
uint16_t distance4;//³¬Éù²¨4¾àÀë
uint16_t distance5;//³¬Éù²¨5¾àÀë
uint16_t flag=0;

#endif
