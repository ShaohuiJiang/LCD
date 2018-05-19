/*******************************************************************************
* @file      : LCD_config.h
* @author    : Jiangsh
* @version   : V1.0.0
* @date      : Tue May 15 2018
* @brief     : LCDģ�������ͷ�ļ�
********************************************************************************
* @attention :������ı��д��ں��ֱ������ı�Ҫת����GB2312�����ʽ����ʹ�
*
*
*/
/* ��������-------------------------------------------------------------------*/
#ifndef _LCD_CONFIG_H
#define _LCD_CONFIG_H

/*ͷ�ļ�----------------------------------------------------------------------*/
#include "ht6xxx.h"         //MCU��Ӧ�ļĴ���ͷ�ļ�

/*�궨��----------------------------------------------------------------------*/

//Һ���ͺ�

#define LCDType HG160800X_ST75163
//ѡ��
#define HG160800X_ST75163   1 //Һ���ͺţ�����HG160800X,����оƬ:����ST75163


//��ʾģʽ
#define MeterType  ThreePhaseMeter
//ѡ��
#define OnePhaseMeter 1       // �������ʾģʽ
#define ThreePhaseMeter 2     // �������ʾģʽ


/*����----------------------------------------------------------------------*/

/* LCDƬѡ�� */
#define CS_High()           HT_GPIOB->PTSET |= (1<<10)      
#define CS_Low()            HT_GPIOB->PTCLR |= (1<<10)      

/* LCD��ָ��\����ѡ��� */
#define A0_High()           HT_GPIOB->PTSET |= (1<<9)     
#define A0_Low()            HT_GPIOB->PTCLR |= (1<<9)      

/* LCD�ĸ�λ�� */
#define RST_High()           HT_GPIOB->PTSET |= (1<<8)      
#define RST_Low()            HT_GPIOB->PTCLR |= (1<<8)      

/* LCD��ʱ�ӽ� */
#define SCK_High()           HT_GPIOB->PTSET |= (1<<7)      
#define SCK_Low()            HT_GPIOB->PTCLR |= (1<<7)    

/* LCD�����ݽ� */
#define SDA_High()          {HT_GPIOB->PTDIR |= (1<<6); HT_GPIOB->PTSET |= (1<<6);}      
#define SDA_Low()           {HT_GPIOB->PTDIR |= (1<<6); HT_GPIOB->PTCLR |= (1<<6);}      
#define SDA_IN()             HT_GPIOB->PTDIR &= ~(1<<6)     
#define SDA_STATUS()         HT_GPIOB->PTDAT &= (1<<6)

/* LCD�Ĺܽų�ʼ���ã��ú궨�屻LCD_Init���ã���LCD_Init��Display_Init()���ã�������main������ֻҪ����Display_Init()���� */
#define LCD_GPIO_Init()     {HT_CMU->WPREG = 0xA55A;HT_GPIOB->IOCFG &= ~0x07c0;HT_CMU->WPREG = 0x0000;\
                             HT_GPIOB->PTCLR |= 0x07c0;HT_GPIOB->PTSET |= 0x06c0;\
                             HT_GPIOB->PTOD  |= 0x07c0;	HT_GPIOB->PTDIR |= 0x07c0;}

#endif
/*end------------------------------------------------------------------------*/

