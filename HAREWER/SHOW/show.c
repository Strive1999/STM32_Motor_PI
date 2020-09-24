#include "show.h"

unsigned char i,Send_Count,delay_flag,delay_50; //��λ����ر���
unsigned int OledTimeMs=0;												//ʱ���׼

void DataScope(void)	//��λ�����ݲ�����ʾ
{   
	DataScope_Get_Channel_Data( get, 1 );      
	DataScope_Get_Channel_Data( set, 2 ); 
//	DataScope_Get_Channel_Data( get*6000/1560, 1 );      
//	DataScope_Get_Channel_Data( set*6000/1560, 2 );  
	DataScope_Get_Channel_Data( 0, 3 );  

	Send_Count = DataScope_Data_Generate(3);
	for( i = 0 ; i < Send_Count; i++) 
	{
		while((USART1->SR&0X40)==0);  
		USART1->DR = DataScope_OutPut_Buffer[i]; 
	}
}

void start_show(void)
{
	OLED_ShowString(32,0,"Capstone",16,1);
	OLED_ShowChinese(4,32,0,16,1);//ת
	OLED_ShowChinese(25,32,1,16,1);//��
	OLED_ShowChinese(46,32,2,16,1);//��
	OLED_ShowChinese(67,32,3,16,1);//��
	OLED_ShowChinese(88,32,4,16,1);//��
	OLED_ShowChinese(109,32,5,16,1);//��
	OLED_Refresh();//ˢ����ʾ
	delay_ms(1000);
	delay_ms(1000);
	OLED_Clear();
	
	TIM2_Int_Init(9,7199);   //��ʱ��2Ϊ�ǿն����ṩ1msһ�ε��ж�����ʵ��ָ��֡��ˢ��
	ShowStars();						//�ǿն���
	TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);  //�رն�ʱ��2
	TIM_Cmd(TIM2,DISABLE);	 
}

void capstone_show(void)
{
	int set_speed,get_speed;
	OLED_ShowString(0,0,"Capstone",16,1);
	if(flag_Stop)
		OLED_ShowString(72,0,"Stop   ",16,1);
	else if(set<0)
		OLED_ShowString(72,0,"Back   ",16,1);
	else if(set>0)
		OLED_ShowString(72,0,"Forward",16,1);
	
	OLED_ShowString(0,16,"Kp:",16,1);
	OLED_ShowNum(24,16,Kp,3,16,1);
	OLED_ShowString(64,16,"Ki:",16,1);
	OLED_ShowNum(88,16,Ki,3,16,1);
	
	OLED_ShowString(0,32,"set:",16,1);//�趨ֵ��ʾ
	if(set>=0)
		OLED_ShowChar(32,32,'+',16,1);
	else if(set<0)
		OLED_ShowChar(32,32,'-',16,1);
	OLED_ShowNum(40,32,abs(set),2,16,1);
	OLED_ShowString(64,32,"n:",16,1);
	OLED_ShowString(104,32,"rpm",16,1);
	set_speed=abs(set)*6000/1560;
	OLED_ShowNum(80,32,set_speed,3,16,1);
	
	OLED_ShowString(0,48,"get:",16,1);//����ֵ��ʾ
	if(get>=0)
		OLED_ShowChar(32,48,'+',16,1);
	else if(get<0)
		OLED_ShowChar(32,48,'-',16,1);
	OLED_ShowNum(40,48,abs(get),2,16,1);
	OLED_ShowString(64,48,"n:",16,1);
	OLED_ShowString(104,48,"rpm",16,1);
	get_speed=abs(get)*6000/1560;
	OLED_ShowNum(80,48,get_speed,3,16,1);
	OLED_Refresh();//ˢ����ʾ
}

//����:�̶�֡��ʱ�䣩ˢ����Ļ��valueΪ֡��
unsigned char FrameRateUpdateScreen(int value)
{
	if(OledTimeMs==0)				//OledTimeMs��Ҫ��1ms�ж��б���������ֱ������0
	{
		OLED_Refresh();
		OLED_Clear_Data();
		OledTimeMs=1000/value;
		return 1;
	}
	return 0;
}

//�ǿն����㷨
void ShowStars(void)
{
	int i;
	int count=0;
	int fps=60;
	typedef struct START
	{
		short x;
		short y;
		short speed;
		unsigned char speedcount;
		unsigned char isexist;
	}Star;
	
	Star star[128]={0};
	srand(2);
	for(i=0;i<128;i++)
	{
		if(star[i].isexist==0)
		{
			//����128��()���ǵĳ�ʼ��Ϣ
			star[i].x=rand()%127;		//������ɳ�ʼx����
			star[i].y=rand()%64;		//�������y������
			star[i].speedcount=0;
			star[i].speed=rand()%8+1;	//1-8����
			star[i].isexist=1;
		}
	}
	while(1)
	{
		if(FrameRateUpdateScreen(fps)==1)	//�ڴ˺����ж�ʱˢ����
		{
			count++;
			if(count>=fps*2)   			//��������ʱ��10s
				return;
		}
		for(i=0;i<128;i++)
		{
			//�����һ�������Ѿ��ƶ����˳���Ļ����
			//�����������������һ��������
			if(star[i].isexist==0)
			{
				star[i].x=0;
				star[i].y=rand()%64;
				star[i].speed=rand()%6+1;
				star[i].speedcount=0;		
				star[i].isexist=1;
			}
			else
			{
				star[i].speedcount++;
				if(star[i].x>=124)			
					star[i].isexist=0;
				
				OLED_DrawLine(star[i].x,star[i].y,star[i].x,star[i].y,0);
				if(star[i].speedcount==star[i].speed)	
				{
					star[i].speedcount=0;		
					star[i].x+=1;					
				}										
				OLED_DrawLine(star[i].x, star[i].y, star[i].x+(6/star[i].speed)-1, star[i].y,1);
			}
		}
	}
}

void Huaxian()//���߶����㷨
{
	int i;
	OLED_Clear_Data();
	for(i=0;i<20;i++)
	{
		OLED_DrawLine(0,0,i*10,63,1);
		OLED_Refresh();
		delay_ms(50);
	}
	for(i=0;i<20;i++)
	{
		OLED_DrawLine(128,0,128-i*10,63,1);
		OLED_Refresh();
		delay_ms(50);
	}
	delay_ms(1000);
}
