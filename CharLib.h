/*******************************************************************************
* @file      : CharLib.h
* @author    : Jiangsh
* @version   : V1.0.0
* @date      : Sat Apr 21 2018
* @brief     : 
********************************************************************************
* @attention :������ı��д��ں��ֱ������ı�Ҫת����GB2312�����ʽ����ʹ�
*
*
*/
/* ��������-------------------------------------------------------------------*/
#ifndef _CHARLIB_H
#define _CHARLIB_H

/*ͷ�ļ�----------------------------------------------------------------------*/
#include "LCD_config.h"

/*�궨��----------------------------------------------------------------------*/
typedef struct
{
        unsigned short CharGbk;             //GBK��
  const unsigned char* CharAddress;         //��Ӧ��GBK����ַ����ڵ��ֿ�λ��

}GBK_CHARADDRESS_STRUCT;                    //�ַ���GBK���ֿ�������ʼ��ַ�ṹ��


/* ��ʾ�ַ��ߴ� seg*100+com */

#if (MeterType == ThreePhaseMeter)

#define Size_6P12P       612    //������ʾ��������ĸ
#define Size_13P12P     1312    //������ʾ�������ַ�
#else
#define Size_7P14P       714    //������ʾ��������ĸ
#define Size_14P14P     1414    //������ʾ������
#endif 

#define Size_12P12P     1212    //�����������ʾ�����֡�������ʾ�����֡���λ�����ֺ���������������ޱ�־

#define Size_18P36P   1836      //����������
#define Size_4P36P     436      //������С����
#define Size_8P36P     836      //����������

#define Size_26P12P   2612      //������ʾ����λ
#define Size_10P11P   1011      //״̬��ʾ����־

#define Size_8P12P     812      //��λ���ַ�
#define Size_24P12P   2412      //��λ���ַ�
#define Size_25P12P   2512      //��λ���ַ�

#define Size_6P11P     611      //״̬��ʾ���ַ�
#define Size_7P11P     711      //״̬��ʾ���ַ�
#define Size_8P11P     811      //״̬��ʾ���ַ�
#define Size_9P11P     911      //״̬��ʾ���ַ�
#define Size_11P11P    1111     //״̬��ʾ���ַ�
#define Size_12P11P    1211     //״̬��ʾ���ַ�
#define Size_13P11P    1311     //״̬��ʾ���ַ�
#define Size_14P11P    1411     //״̬��ʾ���ַ�


/* ������ģ���ֵĴ�С */
#if (MeterType == ThreePhaseMeter)
#define ChineseHint_Char_6P12P_Number  18
#define ChineseHint_Char_12P12P_Number 56
#define GBKNumber (ChineseHint_Char_6P12P_Number+ChineseHint_Char_12P12P_Number)
#else
#define ChineseHint_Char_7P14P_Number  18
#define ChineseHint_Char_14P14P_Number 56
#define GBKNumber (ChineseHint_Char_7P14P_Number+ChineseHint_Char_14P14P_Number)
#endif

/*��������--------------------------------------------------------------------*/

#if (MeterType == ThreePhaseMeter)
//������ר���ֿ�����
//��Ȧ ��(0) ��Ȧ ��(1)��Ȧ  ��(2) ��Ȧ ��(3)
extern const unsigned char QuadrantIcon_12p12p[4][24];

//������ʾ�����ֺ���ĸר���ֿⲻ�����������֢����
/*
 0(0) 1(1) 2(2) 3(3) 4(4) 5(5) 6(6) 7(7) 8(8) 9(9) T(10) A(11) B(12) C(13)
 N(14) O(15) S(16)
 */
extern const unsigned char ChineseHint_Char_6p12p[ChineseHint_Char_6P12P_Number][12];

//������ʾ������ר���ֿ�����������֢����
/*
 ��(0) ǰ(1) ��(2) ��(3) ��(4) ��(5) ��(6) ��(7) ��(8) ��(9) ��(10) ��(11) ƽ(12) ��(13) ʣ(14) ��(15)
 ��(16) ��(17) ��(18) ��(19) ͸(20) ֧(21) ��(22) ��(23) ��(24) ��(25) ��(26) ʱ(27) ��(28) ��(29) ��(30) ��(31)
 ��(32) ��(33) ��(34) ��(35) ��(36) ��(37) ��(38) ��(39) ʧ(40) ѹ(41) ��(42)  ��(43)  ��(44) ��(45) ��(46) ��(47)
 ��(48) ��(49) ��(50) ��(51) ��(52) ��(53) ��(54) ��(55)
 */
extern const unsigned char ChineseHint_Char_12p12p[ChineseHint_Char_12P12P_Number][24];

//�������ר���ֿ⣬00~09
extern const unsigned char SplitScreenIcon_13p12p[10][26];
#else
//������ʾ�����ֺ���ĸר���ֿⲻ�����������֢����
/*
 0(0) 1(1) 2(2) 3(3) 4(4) 5(5) 6(6) 7(7) 8(8) 9(9) T(10) A(11) B(12) C(13)
 N(14) O(15) S(16)
 */
extern const unsigned char ChineseHint_Char_7p14p[ChineseHint_Char_7P14P_Number][14];

//������ʾ������ר���ֿ�����������֢����
/*
 ��(0) ǰ(1) ��(2) ��(3) ��(4) ��(5) ��(6) ��(7) ��(8) ��(9) ��(10) ��(11) ƽ(12) ��(13) ʣ(14) ��(15)
 ��(16) ��(17) ��(18) ��(19) ͸(20) ֧(21) ��(22) ��(23) ��(24) ��(25) ��(26) ʱ(27) ��(28) ��(29) ��(30) ��(31)
 ��(32) ��(33) ��(34) ��(35) ��(36) ��(37) ��(38) ��(39) ʧ(40) ѹ(41) ��(42)  ��(43)  ��(44) ��(45) ��(46) ��(47)
 ��(48) ��(49) ��(50) ��(51) ��(52) ��(53) ��(54) ��(55)
 */
extern const unsigned char ChineseHint_Char_14p14p[ChineseHint_Char_14P14P_Number][28];

//�������ר���ֿ⣬00~09
extern const unsigned char SplitScreenIcon_14p14p[10][28];
#endif

//������ר�á�-����0��
extern const unsigned char MinusIcon_8p36p[1][40];
//������ר��С���㡰.��(0),ר��ð�š�����(1)
extern const unsigned char Point_4p36p[2][20];
//������ר������ 0(0) 1(1) 2(2) 3(3) 4(4) 5(5) 6(6) 7(7) 8(8) 9(9)
extern const unsigned char NumberArea_char_18p36p[10][90];


// ��λ��ר�ú��֣���(0) Ԫ(1)
extern const unsigned char UintArea_char_12p12p[2][24];
//����Щ�ַ�����ɣ�W,V,A,kW��kWh��var��VA��kVA,Ah;
// ��λ��ר���ַ��� W(0) V(1) A(2) k(3) h(4) v(5) a(6) r(7)
extern const unsigned char UintArea_char_8p12p[8][16];
// ��λ��ר���ַ���kvar(0) kvah(1)
extern const unsigned char UintArea_char_24p12p[2][48];
// ��λ��ר���ַ���kvarh(0)
extern const unsigned char UintArea_char_25p12p[1][50];


//������ר���ַ��� ��(0) ��(1) ��(2) ��(3) ��(4) ��(5) ��(6) ��(7) բ(8) ͸(9) ֧(10) ��(11) ��(12) ��(13)
extern const unsigned char AlarmHint_char_12p12p[14][24];

#if (MeterType == ThreePhaseMeter)
//״̬��ʾ��ר���ַ�������״̬(0)
extern const unsigned char StatusHint_char_6p11p[1][12];

//״̬��ʾ��ר���ַ�����˽Կ״̬(0) ��һ·485ͨ��״̬(1) �ڶ�·485ͨ��״̬(2) ���1״̬(3) ���2״̬(4)
extern const unsigned char StatusHint_char_7p11p[5][14];

//״̬��ʾ��ר���ַ���Ub(0) Uc(1)
extern const unsigned char StatusHint_char_8p11p[2][16];

//״̬��ʾ��ר���ַ������״̬(0) Ua(1)
extern const unsigned char StatusHint_char_9p11p[2][18];

//״̬��ʾ��ר���ַ�����Ia״̬(0) ��Ia״̬(1) 
extern const unsigned char StatusHint_char_11p11p[2][22];

//״̬��ʾ��ר���ַ����ز�״̬(0) ��Ib״̬(1) ��Ib״̬(2) ��Ic״̬(3) ��Ic״̬(4)
extern const unsigned char StatusHint_char_10p11p[5][20];

//״̬��ʾ��ר���ַ�������ͨ���������ź�(0) ����ͨ������1���ź�(1) ����ͨ������2���ź�(2) ����ͨ������3���ź�(3) ����ͨ������4���ź�(4) ����ָʾ(5)
extern const unsigned char StatusHint_char_12p11p[6][24];

/*
״̬��ʾ��ר���ַ���
����1(0) ����2(1) ����3(2) ����4(3) ����5(4) ����6(5) ����7(6) ����8(7) ����9(8) ����10(9) ����11(10) ����12(11) ����13(12) ����14(13) ����15(14) ����16(15)
����17(16) ����18(17) ����19(18) 
����1(19) ����2(20) ����3(21) ����4(22) ����5(23) ����6(24) ����7(25) ����8(26) ����9(27) ����10(28) ����11(29) ����12(30) ����13(31) ����14(32) ����15(33) ����16(34) 
����17(35) ����18(36) ����19(37) 
*/
extern const unsigned char StatusHint_char_13p11p[38][26];

#else
//״̬��ʾ��ר���ַ���485�ͺ���״̬(0)
extern const unsigned char StatusHint_char_6p11p[1][12];

//״̬��ʾ��ר���ַ�������״̬(0) ���״̬(1)
extern const unsigned char StatusHint_char_7p11p[2][14];

//״̬��ʾ��ר���ַ�������״̬(0) 
extern const unsigned char StatusHint_char_9p11p[1][18];

//״̬��ʾ��ר���ַ����ز�״̬(0) ��˽Կ״̬(1) 
extern const unsigned char StatusHint_char_10p11p[2][20];

//״̬��ʾ��ר���ַ������״̬(0) 
extern const unsigned char StatusHint_char_13p11p[1][26];

/*
״̬��ʾ��ר���ַ���
����1(0) ����2(1) ����3(2) ����4(3) ����5(4) ����6(5) ����7(6) ����8(7) ����9(8) ����10(9) ����11(10) ����12(11) ����13(12) ����14(13) ����15(14) ����16(15)
����17(16) ����18(17) ����19(18) 
����1(19) ����2(20) ����3(21) ����4(22) ����5(23) ����6(24) ����7(25) ����8(26) ����9(27) ����10(28) ����11(29) ����12(30) ����13(31) ����14(32) ����15(33) ����16(34) 
����17(35) ����18(36) ����19(37) 
*/
extern const unsigned char StatusHint_char_14p11p[38][28];
#endif 
/* GBK����ַ���Ӧ������ */
extern const GBK_CHARADDRESS_STRUCT  charaddressbuf[GBKNumber];


#endif
/*end------------------------------------------------------------------------*/

