#ifndef __MOTO_H
#define __MOTO_H
#include "sys.h"

void Moto_Init(void);    //��ʼ�����Ƶ�����������
void Pwm_Init(u16 arr,u16 psc); //PWM�����ʼ��
#define PWMA   TIM1->CCR1
#define AIN2   PBout(15)
#define AIN1   PBout(14)
#define BIN1   PBout(11)
#define BIN2   PBout(10)
#define LED_PWF   PCout(13)
#define PWMB   TIM1->CCR4

#endif

