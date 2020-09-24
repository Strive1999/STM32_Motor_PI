/*
* @file         main.c	
* @author       ����
* @version      Text
* @date         2020.09.12
* @brief        Capstone������
* @remark       һЩ֧�֣�ƽ��С��֮�ҡ��о�԰���ӡ�BվMjGame������     
*/

#include "sys.h"

unsigned char flag_Stop=1;     //���ֹͣ��־λ
int set=30;  //�ٶ��趨ֵ��ÿ10ms����������
int get;     //����������������
int Kp=60,Ki=7;		//p,i����
int err,Last_err,pi_out;//ƫ��/�ϴ�ƫ��/pi���������
int step=10;//�Ӽ��ٲ���ֵ

int main(void)
{	
	delay_init();             //��ʱ��ʼ��
	OLED_Init();							//OLED��ʼ��
//	uart_init(128000);        //��ʼ������1����λ��ͨѶ��
	Moto_Init();              //��ʼ�����Ƶ����IO
	Pwm_Init(7199,0);         //��ʼ��pwm���(10kHZ)
	Encoder_Init_TIM4();      //��ʱ��������ģʽ
	EXTIX_Init();							//�����ⲿ�ж�
	start_show();							//��ʼ����չʾ
	uart2_init(9600);        //��������2��ʼ����APP��
	TIM3_Int_Init(99,7199);   //10ms�ж�
	while(1)
	{
//		DataScope();	          //��λ��
    printf("{B%d:%d:%d}$",0,set,get);//APP������ʾ
		delay_flag=1;	          //50ms��־λ	
		capstone_show();				//capstone������ˢ��
		while(delay_flag);      //50ms��ʱ��  ������ʾ��λ����Ҫ�ϸ��50ms��������  
	}
}
