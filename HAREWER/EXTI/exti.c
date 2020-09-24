#include "exti.h"

void EXTIX_Init(void)
{
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	����IO��ʼ��
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	

   //A0	  �ж��߼��жϳ�ʼ������ �½��ش��� //K2
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	

   //A1	  �ж��߼��жϳ�ʼ������  �½��ش���	//K1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);	  	

   //A4	  �ж��߼��жϳ�ʼ������  �½��ش���	//K4
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	
		
		//C15	�ж��߼��жϳ�ʼ������  �½��ش���	//K3
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource15);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_Init(&EXTI_InitStructure);	  	


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;							
  	NVIC_Init(&NVIC_InitStructure);  	

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;						
  	NVIC_Init(&NVIC_InitStructure);  	 
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;								
  	NVIC_Init(&NVIC_InitStructure);  	
}

//�ⲿ�ж�1������� k1
void EXTI1_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY1==0)	 //����KEY1
	{			
		flag_Stop=!flag_Stop;	
	}		 
	EXTI_ClearITPendingBit(EXTI_Line1);  //���LINE3�ϵ��жϱ�־λ  
}


//�ⲿ�ж�0������� k2
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY2==0)	 	 //k1����
	{		
		set+=step;
		if(set>=70)	set=70;
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}

//�ⲿ�ж�15������� k3
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY3==0)	 //����KEY0
	{
		set-=step;
		if(set<=0)	set=0;
	}		 
	EXTI_ClearITPendingBit(EXTI_Line15);  //���LINE4�ϵ��жϱ�־λ  
}

//�ⲿ�ж�4������� k4
void EXTI4_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY4==0)	 //����KEY0
	{
		set=-set;
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ  
}

 
