#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
 /**************************************************************************
���ߣ�ƽ��С��֮�� 
�Ա����̣�http://shop114407458.taobao.com/
**************************************************************************/
#define USART_REC_LEN  			20  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  rec[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void uart2_init(u32 bound);
#endif


