#include "encoder.h"


//TIM4��ʼ��Ϊ�������ӿ�ģʽ
void Encoder_Init_TIM4(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��PB�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);					     
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD-1; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ʱ�Ӳ���Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;////���ϼ���  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
  TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,
														 TIM_ICPolarity_Rising, 
														 TIM_ICPolarity_Rising);//������ģʽ3
	
  TIM_ICStructInit(&TIM_ICInitStructure); 
  TIM_ICInitStructure.TIM_ICFilter = 10;  //�����˲�������
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
 
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);//ʹ�ܶ�ʱ���ж�
  TIM_SetCounter(TIM4,1000);//����TIMx �������Ĵ���ֵ
  TIM_Cmd(TIM4, ENABLE); //ʹ�ܶ�ʱ��
}


//�жϴ�����Ϊ�գ�����жϱ�־λ������ж�
void TIM4_IRQHandler(void)
{
 if(TIM_GetFlagStatus(TIM4,TIM_FLAG_Update)==SET)//����ж�
 {
	 TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//����жϱ�־λ 
 }
}
//��λʱ���ȡ����������ֵ����תΪ��ֵ����תΪ��ֵ��1000Ϊ������ʼֵ��
int Read_Encoder(u8 TIMX)//��ȡ��������ֵ
{
  int count;
	switch(TIMX)
	{
	  case 2:count=(short)TIM2->CNT; TIM2 -> CNT=0;  break;
		case 3:count=(short)TIM3->CNT; TIM3 -> CNT=0;  break;
		case 4:count=(short)TIM4->CNT; TIM4 -> CNT=1000; break;
		default: count=0;
	}
  return (count-1000);
}
