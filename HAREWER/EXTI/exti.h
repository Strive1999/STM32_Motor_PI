#ifndef __EXTI_H
#define __EXTI_H	 
#include "sys.h"

#define KEY2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����1
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//��ȡ����2
#define KEY4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//��ȡ����4
#define KEY3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)//��ȡ����3

void EXTIX_Init(void);//�ⲿ�жϳ�ʼ��		
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI15_IRQHandler(void);
extern int set;
#endif

