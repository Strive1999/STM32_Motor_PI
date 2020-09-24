#include "moto.h"

void Moto_Init(void)//��ʼ�����Ƶ����IO
{
  GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStruct);	
	
//	//LED
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOC,&GPIO_InitStruct);	
}

void Pwm_Init(u16 arr,u16 psc) //��ʼ��pwm���
{	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  //ʹ�ܶ�ʱ��1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //ʹ��GPIOA��ʱ��
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;         //�������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;   //PA8(CH1) PA11(CH4)
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;                     //�趨�������Զ���װֵ 
	TIM_TimeBaseInitStruct.TIM_Prescaler  = psc;                 //�趨Ԥ��Ƶ��
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;                //����ʱ�ӷָ�
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);              //��ʼ����ʱ��
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;              //PWMģʽ1:CNT<CCRʱ�����Ч
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;  //�Ƚ����ʹ��
	TIM_OCInitStruct.TIM_Pulse = 0;                             //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;       //��ЧΪ�ߵ�ƽ
	TIM_OC4Init(TIM1,&TIM_OCInitStruct);                         //��ʼ������Ƚϲ���
	
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable); //CH1ʹ��Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM1, ENABLE);              //ʹ��TIM1��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(TIM1,ENABLE);                            //ʹ�ܶ�ʱ��1
	TIM_CtrlPWMOutputs(TIM1,ENABLE);                 //�߼���ʱ����������������
}

