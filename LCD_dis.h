/*******************************************************************************
* @file      : LCD_dis.h
* @author    : Jiangsh
* @version   : V1.0.0
* @date      : Tue May 15 2018
* @brief     : 
********************************************************************************
* @attention :������ı��д��ں��ֱ������ı�Ҫת����GB2312�����ʽ����ʹ�
*
*
*/
/* ��������-------------------------------------------------------------------*/
#ifndef _LCD_DIS_H
#define _LCD_DIS_H



/*ͷ�ļ�----------------------------------------------------------------------*/
///���ͷ�ļ�
#include "LCD_config.h"

/*�궨��----------------------------------------------------------------------*/
typedef enum
{
    CombinedActivePowerEnergy,          //����й�
	PositiveActivePowerEnergy,	        //�����й�
	ReverseActivePowerEnergy,		    //�����й�
    CombinedOneReactivePowerEnergy,     //���1�޹�
    CombinedTwoReactivePowerEnergy,     //���2�޹�
	PositiveReactivePowerEnergy,	    //�����޹�
	ReverseReactivePowerEnergy,		    //�����޹�
    FirstQuadrantReactivePowerEnergy,   //��1�����޹�
    SecondQuadrantReactivePowerEnergy,  //��2�����޹�
    ThirdQuadrantReactivePowerEnergy,   //��3�����޹�
    FourthQuadrantReactivePowerEnergy,  //��4�����޹�
    PositiveApparentEnergy,             //��������
    ReverseApparentEnergy               //��������
}ENERGY_TYPE;                           //��������

typedef enum
{
    TotalPhase,                         //����
    APhase,                             //A��
    BPhase,                             //B��
    CPhase                              //C��
}PHASE_TYPE;                            //��λ����


typedef enum
{
    Plus,                               //��
    Minus                               //��
}PLUS_MINUS;                            //������־

typedef enum
{
    DisplayHighZero,                    //��ʾ��λ��
    NoDisplayHighZero                   //����ʾ��λ��
}HIGHZERO_TYPE;                         //��λ�����־

typedef enum
{
    NoDisplaySplitScreen,               //����ʾ����
    DisplaySplitScreenZero,             //��ʾ�������00
    DisplaySplitScreenOne,              //��ʾ�������01
    DisplaySplitScreenTwo,              //��ʾ�������02
    DisplaySplitScreenThree             //��ʾ�������03
    //���Լ�������...
}SPLITSCREENDISPLAY_TYPE;               //������ʾ��־

typedef enum
{
    DisplayAction,                      //��ʾ
    ClearAciton                         //����ʾ�������
}DISPLAY_ACTION_TYPE;                   //��ʾ��Ϊ���ͣ�����״̬�ͱ�����ʾ

/*�����ⲿ����----------------------------------------------------------------*/
/** 
 * @brief  ��ʾģ���ʼ������
 * @note   �򿪺�Ĭ����ʾ�ǿհ�
 * @retval None
 */
extern void Display_Init(void);

/** 
 * @brief  ��ʾģ��ر�
 * @note   
 * @retval None
 */
extern void Diplay_Closed(void);
/** 
 * @brief  ������ʾ�����Ʋ��ֹ�����ʾ����
 * @note   �������Ҫ���ڶ�ʱ���У���ʱִ�У���������ʾ��������ʾ����ʱ�����Զ�����
 * @retval None
 */
extern void RollDiplay_ChineseHintArea(void);


#if (MeterType == ThreePhaseMeter)       //����ģʽ
/** 
 * @brief  ��ʾ������״̬
 * @note   
 * @param  number: 1����һ���ޣ�2���ڶ����ޣ�3���������ޣ�4����4���ޣ� ����ֵ��Ч
 * @retval None
 */
extern void Display_QuadrantStatus(unsigned char number);
#endif
/** 
 * @brief  ��ʾ���߲���ʾ��Կ״̬
 * @note   
 * @param  displayaction: �μ�DISPLAY_ACTION_TYPEö������
 * @retval None
 */
extern void Display_PublicKeyStatus(DISPLAY_ACTION_TYPE displayaction);
/** 
 * @brief  ��ʾ���߲���ʾ������֤״̬
 * @note   
 * @param  displayaction: 
 * @retval None
 */
extern void Display_InfraredAuthenticationStatus(DISPLAY_ACTION_TYPE displayaction);
/** 
 * @brief  ��ʾ���߲���ʾ���ܱ����״̬
 * @note   
 * @param  displayaction: �μ�DISPLAY_ACTION_TYPEö������
 * @retval None
 */
extern void Display_SuspendedStatus(DISPLAY_ACTION_TYPE displayaction);



/** 
 * @brief  ��ʾ��������
 * @note  
 * @param  phase: ������λ ����μ�PHASE_TYPEö�� 
 * @param  engerytype: �������࣬����μ�ENERGY_TYPEö��
 * @param  date:    ���� 0~12��0��ʾ��ǰ  ����������x��
 * @param  rate:    ���� 0~12������0�����ܣ���������Tx
 * @param  engerypoint: ָ������洢�����飬Ĭ��6�ֽ�BCD�룬����ֽڴ����3,4С��
 * @param  decimalpoint: ������ʾ�ĵ�����ʾ��λС����0~4
 * @param  plusminus: �����Ƿ���ʾ���ţ�    Plus������ʾ��Minus������ʾ
 * @param  displayhighzero: ��λ�Ƿ����㣬����μ�HIGHZERO_TYPEö��
 * @retval None
 */
extern void Display_Engery(PHASE_TYPE phase,ENERGY_TYPE engerytype,unsigned char date,unsigned char rate,unsigned char* engerypoint,unsigned char decimalpoint,PLUS_MINUS plusminus,HIGHZERO_TYPE displayhighzero);

/** 
 * @brief  ��ʾ��ǰ����
 * @note   
 * @param  datepoint: ָ������洢�����飬Ĭ��3�ֽ�BCD�룬����ֽڴ�����
 * @retval None
 */
extern void Display_CurrentDate(unsigned char* datepoint);

/** 
 * @brief  ��ʾ��ǰʱ��
 * @note   
 * @param  timepoint: ָ��ʱ��洢�����飬Ĭ��3�ֽ�BCD�룬����ֽڴ�����
 * @retval None
 */
extern void Display_CurrentTime(unsigned char* timepoint);

/** 
 * @brief  ��ʾ��ǰʣ����
 * @note   ������ʾ����ǰʣ���ѡ� ������ʾ����ǰʣ���
 * @param  amountpoint: ָ��ʣ����洢�����飬Ĭ��4�ֽ�BCD�룬����ֽڴ���С��1��2λ
 * @param  displayhighzero: ��λ�Ƿ����㣬0������ʾ�� 1������ʾ
 * @retval None
 */
extern void Display_RemainingAmount(unsigned char* amountpoint,unsigned char displayhighzero);

/** 
 * @brief  ��ʾ��ǰ͸֧���
 * @note   ������ʾ����ǰ͸֧��ѡ� ������ʾ����ǰ͸֧��
 * @param  amountpoint: ָ��͸֧���洢�����飬Ĭ��4�ֽ�BCD�룬����ֽڴ���С��1��2λ
 * @param  displayhighzero: ��λ�Ƿ����㣬0������ʾ�� 1������ʾ
 * @retval None
 */
extern void Display_OverdraftAmount(unsigned char* amountpoint,unsigned char displayhighzero);


#endif
/*end------------------------------------------------------------------------*/
