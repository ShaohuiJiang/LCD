/*******************************************************************************
* @file      : LCD_dev.h
* @author    : Jiangsh
* @version   : V1.0.0
* @date      : Tue May 15 2018
* @brief     : LCDģ�����������ͷ�ļ�
********************************************************************************
* @attention :������ı��д��ں��ֱ������ı�Ҫת����GB2312�����ʽ����ʹ�
*
*
*/
/* ��������-------------------------------------------------------------------*/
#ifndef _LCD_DEV_H
#define _LCD_DEV_H

/*ͷ�ļ�----------------------------------------------------------------------*/
#include "LCD_config.h"

/*�궨��---------------------------------------------------------------------*/

/* LCD�ĵ����� */        
#define com   80        //COM��
#define seg   160       //����
#define Page  10        //COM��ɵ�ҳ��

#if (MeterType == ThreePhaseMeter)      //����ģʽ

//ע�⣺��������������ʾ����com�϶����ص��ģ�ֻ��seg��Χ��һ��
/* ��������COM��ַ��Χ��ǰ�պ󿪣�12p */
#define QuadrantAreaStartCom 0
#define QuadrantAreaEndCom   12

/* ��������ҳ��ַ��Χ ��ǰ�պ󿪣�2byte*/
#define QuadrantAreaStartPageCom     0
#define QuadrantAreaAreaEndPageCom   2

/* ��������SEG��ַ��Χ ��ǰ�պ󿪣�12p*/
#define QuadrantAreaStartSeg 0
#define QuadrantAreaEndSeg   12

#endif

#if (MeterType == ThreePhaseMeter)
/* ������ʾ����COM��ַ��Χ��ǰ�պ󿪣� 12p*/
#define ChineseHintAreaStartCom 0
#define ChineseHintAreaEndCom   12

/* ������ʾ����ҳ��ַ��Χ ��ǰ�պ󿪣�2bytes*/
#define ChineseHintAreaStartPageCom 0
#define ChineseHintAreaEndPageCom   2

/* ������ʾ����Seg��ַ��Χ��ǰ�պ󿪣� 145p*/
#define ChineseHintAreaStartSeg 15
#define ChineseHintAreaEndSeg   seg

#else      

/* ������ʾ����COM��ַ��Χ��ǰ�պ󿪣� 14p*/
#define ChineseHintAreaStartCom 0
#define ChineseHintAreaEndCom   14

/* ������ʾ����ҳ��ַ��Χ ��ǰ�պ󿪣�2bytes*/
#define ChineseHintAreaStartPageCom 0
#define ChineseHintAreaEndPageCom   2

/* ������ʾ����Seg��ַ��Χ��ǰ�պ󿪣� 160p*/
#define ChineseHintAreaStartSeg 0
#define ChineseHintAreaEndSeg   160

#endif


#if (MeterType == ThreePhaseMeter)       //����ģʽ

/* ������ʾ���ķ�����COM��ַ��Χ��ǰ�պ󿪣� 12p*/
#define SplitWindowAreaStartCom 0
#define SplitWindowAreaEndCom   12

/* ������ʾ���ķ�����ҳ��ַ��Χ ��ǰ�պ󿪣�2bytes*/
#define SplitWindowAreaStartPageCom 0
#define SplitWindowAreaEndPageCom   2

/* ������ʾ���ķ���seg��ַ��Χ��ǰ�պ󿪣�13p */
#define SplitWindowAreaEndseg   seg
#define SplitWindowAreaStartseg (SplitWindowAreaEndseg-13)

#else

/* ������ʾ����COM��ַ��Χ��ǰ�պ󿪣� 14p*/
#define SplitWindowAreaStartCom 0
#define SplitWindowAreaEndCom   14

/* ������ʾ����ҳ��ַ��Χ ��ǰ�պ󿪣�2bytes*/
#define SplitWindowAreaStartPageCom 0
#define SplitWindowAreaEndPageCom   2

/* ������ʾ���ķ���seg��ַ��Χ��ǰ�պ󿪣� */
#define SplitWindowAreaEndseg  seg
#define SplitWindowAreaStartseg (SplitWindowAreaEndseg-14)
#endif



#if (MeterType == ThreePhaseMeter)       //����ģʽ

/* ��������COM��ַ��Χ ��ǰ�պ󿪣�36p*/
#define NumberAreaStartCom      15
#define NumberAreaEndCom        51

/* ��������ҳ��ַ��Χ ��ǰ�պ󿪣�6bytes*/
#define NumberAreaStartPageCom   1
#define NumberAreaEndPageCom     7  

#else

/* ��������COM��ַ��Χ ��ǰ�պ󿪣�36p*/
#define NumberAreaStartCom      16
#define NumberAreaEndCom        52

/* ��������ҳ��ַ��Χ ��ǰ�պ󿪣�5bytes*/
#define NumberAreaStartPageCom   2
#define NumberAreaEndPageCom     7  

#endif

/* ��������Seg��ַ��Χ ��ǰ�պ󿪣�160p*/
#define NumberAreaStartSeg      0
#define NumberAreaEndSeg        seg

  

/* ���ı�����COM��ַ��Χ��ǰ�պ󿪣� 12p */
#define AlarmHintAreaStartCom     54
#define AlarmHintAreaEndCom       66

/* ���ı�������ҳ��ַ��Χ��ǰ�պ󿪣�3Byts */
#define AlarmHintAreaStartPageCom  6
#define AlarmHintAreaEndPageCom    9

/* ���ı�������Seg��ַ��Χ��ǰ�պ󿪣� 135p */
#define AlarmHintAreaStartSeg     0
#define AlarmHintAreaEndSeg      135


/* ��λ����COM��ַ��Χ��ǰ�պ󿪣� 12p */
#define UnitAreaStartCom     54
#define UnitAreaEndCom       66

/* ��λ����ҳ��ַ��Χ��ǰ�պ󿪣�3Byts */
#define UnitAreaStartPageCom  6
#define UnitAreaEndPageCom    9

/* ��λ����Seg��ַ��Χ��ǰ�պ󿪣� 25p */
#define UnitAreaStartSeg     135
#define UnitAreaEndSeg       seg



#if (MeterType == ThreePhaseMeter)       //����ģʽ

/* �ַ�״̬��ʾ����COM��ַ��Χ��ǰ�պ󿪣� 11p */
#define StatusHintAreaStartCom       69
#define StatusHintAreaEndCom         80

#else

/* �ַ�״̬��ʾ����COM��ַ��Χ��ǰ�պ󿪣� 11p */
#define StatusHintAreaStartCom       68
#define StatusHintAreaEndCom         79

#endif

/* �ַ�״̬��ʾ������ҳ��ַ��Χ��ǰ�պ󿪣�2bytes */
#define StatusHintAreaStartPageCom    8
#define StatusHintAreaEndPageCom      10

/* �ַ�״̬��ʾ����Seg��ַ��Χ��ǰ�պ󿪣�  */
#define StatusHintAreaStartSeg        0
#define StatusHintAreaEndSeg          seg

#define display                        1
#define clear                          0

/*�����ⲿ����----------------------------------------------------------------*/

/* LCD���ܳ�ʼ�������������˹ܽų�ʼ�������ó�ʼ��������ID�� */
extern void LCD_Init(void);

/* �رյ���Һ����ͬʱ��λ���õ� */
extern void Closed_LCD(void);

/* ��LCDRAM_BUf��ָ��λ����ʾ�������һ���ַ�(�������֡���ĸ�����֡�����) */
extern void InputCharacter_to_LCDRAM_Buf(unsigned short x,unsigned short y,const unsigned char* charbufstartaddress,unsigned int size,unsigned char displayorclear);

/* LCDRAM_Buf�������� */
extern void Clear_LCDRAM_Buf(void);

#if (MeterType == ThreePhaseMeter)
/* ���LCDRAM_Buf����������������� */
extern void Clear_QuadrantArea_Of_LCDRAM_Buf(void);
#endif 

/* ���LCDRAM_Buf������ָ����Χ�ڵ����� */
extern void Clear_PartArea_of_LCDRAM_Buf(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2);

/* ���LCDRAM_Buf�����������ʾ�������� */
extern void Clear_ChineseHintArea_Of_LCDRAM_Buf(void);

/* ���LCDRAM_Buf����������������� */
extern void Clear_NumberArea_Of_LCDRAM_Buf(void);

/* ���LCDRAM_Buf����ı�����ʾ�������� */
extern void Clear_AlarmHintArea_Of_LCDRAM_Buf(void);

/* ���LCDRAM_Buf����ĵ�λ�������� */
extern void Clear_UnitArea_Of_LCDRAM_Buf(void);

/* ���LCDRAM_Buf�����״̬��ʾ�������� */
extern void Clear_StatusHintArea_Of_LCDRAM_Buf(void);

/* ˢ��LCD��������ʾ���� */
extern void Refresh_LCD_DDRAM(void);

#if (MeterType == ThreePhaseMeter)
/* ˢ��LCD����������ʾ���� */
extern void Refresh_QuadrantArea_of_LCD_DDRAM(void);
#endif 

/* ˢ��LCD�Ĳ���������ʾ���� */
extern Refresh_PartArea_of_LCD_DDRAM(unsigned char startseg,unsigned char startpage,unsigned char endseg,unsigned char endpage );
/* ˢ��LCD��������ʾ����ʾ���� */
extern void Refresh_ChineseHintArea_of_LCD_DDRAM(void);

/* ˢ��LCD����������ʾ���� */
extern void Refresh_NumberArea_of_LCD_DDRAM(void);

/* ˢ��LCD�ı�������ʾ���� */
extern void Refresh_AlarmHintArea_of_LCD_DDRAM(void);

/* ˢ��LCD�ĵ�λ����ʾ���� */
extern void Refresh_UnitArea_of_LCD_DDRAM(void);
/* ˢ��LCD��״̬����ʾ���� */
extern void Refresh_StatusHintArea_of_LCD_DDRAM(void);

/* ֱ����LCDRAM_Bufд�ֽ� */
extern void Wirte_LCDRAM_Buf(unsigned short x, unsigned short y, unsigned char Buf);
#endif
/*end------------------------------------------------------------------------*/

