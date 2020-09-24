#include "control.h"

//��Ҫ�������̺�����10msִ��һ��
int TIM3_IRQHandler(void) 
{
	if(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update)==SET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);   //�����ʱ��3�жϱ�־λ
		
		if(!flag_Stop)
		{
			get=Read_Encoder(4);      //ȡ��ʱ��4����ֵ������ֵ��
			err=set-get;              //����ƫ��
			Incremental_PI();    			//����ʽPI���������		
			Xianfu_Pwm();						  //����޷�
			Set_Pwm(pi_out);					//����pwm
		}
		else
		{
			BIN1=0;BIN2=0;PWMB=0;
			get=0;Last_err=0;
		}
		
		if(delay_flag==1)						//���������ṩ50ms����ʱ����λ���ã�
		{
			if(++delay_50==5)	 
			{
				delay_50=0;
				delay_flag=0;    
			}
		}	
		
	}
	return 0;
}

void Set_Pwm(int out)//��ֵ��PWM�Ĵ���
{
		if(out>0) BIN1=0,   BIN2=1;
		else      BIN1=1,   BIN2=0;
		PWMB=myabs(out);
}

//pi����������޷�
void Xianfu_Pwm(void) 
{
	int Amplitude=7200;  //===PWM������7200 ������7100
	if(pi_out<-Amplitude)  pi_out = -Amplitude;
	if(pi_out>Amplitude)   pi_out =  Amplitude;
}

int myabs(int a) //ȡ����ֵ
{ 		   
	 int temp;
	 if(a<0)  temp=-a;  
	 else temp=a;
	 return temp;
}
/**************************************************************************
�������ܣ�����PI������
����  ֵ��pi���������
��������ʽ��ɢPID��ʽ 
out+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
out�����������
�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pi_out+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI ()
{ 	
	 pi_out+=Kp*(err-Last_err)+Ki*err;   //����ʽPI������
	 Last_err=err;	                   //������һ��ƫ�� 
	 return pi_out;                         //�������
}
