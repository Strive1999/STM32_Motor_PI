#ifndef __LED_H
#define __LED_H
#include "sys.h"
 /**************************************************************************
���ߣ�ƽ��С��֮�� 
�Ա����̣�http://shop114407458.taobao.com/
**************************************************************************/
//LED �˿ڶ���
#define LED PBout(5) // PB5
void LED_Init(void);  //��ʼ��
void Led_Flash(u16 time);
#endif
