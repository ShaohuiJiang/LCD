/*******************************************************************************
* @file      : LCD_dis.h
* @author    : Jiangsh
* @version   : V1.0.0
* @date      : Tue May 15 2018
* @brief     : 
********************************************************************************
* @attention :如果本文本中存在汉字变量，文本要转化成GB2312编码格式保存和打开
*
*
*/
/* 条件编译-------------------------------------------------------------------*/
#ifndef _LCD_DIS_H
#define _LCD_DIS_H



/*头文件----------------------------------------------------------------------*/
///添加头文件
#include "LCD_config.h"

/*宏定义----------------------------------------------------------------------*/
typedef enum
{
    CombinedActivePowerEnergy,          //组合有功
	PositiveActivePowerEnergy,	        //正向有功
	ReverseActivePowerEnergy,		    //反向有功
    CombinedOneReactivePowerEnergy,     //组合1无功
    CombinedTwoReactivePowerEnergy,     //组合2无功
	PositiveReactivePowerEnergy,	    //正向无功
	ReverseReactivePowerEnergy,		    //反向无功
    FirstQuadrantReactivePowerEnergy,   //第1象限无功
    SecondQuadrantReactivePowerEnergy,  //第2象限无功
    ThirdQuadrantReactivePowerEnergy,   //第3象限无功
    FourthQuadrantReactivePowerEnergy,  //第4象限无功
    PositiveApparentEnergy,             //正向视在
    ReverseApparentEnergy               //反向视在
}ENERGY_TYPE;                           //电量种类

typedef enum
{
    TotalPhase,                         //合相
    APhase,                             //A相
    BPhase,                             //B相
    CPhase                              //C相
}PHASE_TYPE;                            //相位种类


typedef enum
{
    Plus,                               //正
    Minus                               //负
}PLUS_MINUS;                            //正负标志

typedef enum
{
    DisplayHighZero,                    //显示高位零
    NoDisplayHighZero                   //不显示高位零
}HIGHZERO_TYPE;                         //高位显零标志

typedef enum
{
    NoDisplaySplitScreen,               //不显示分屏
    DisplaySplitScreenZero,             //显示分屏序号00
    DisplaySplitScreenOne,              //显示分屏序号01
    DisplaySplitScreenTwo,              //显示分屏序号02
    DisplaySplitScreenThree             //显示分屏序号03
    //可以继续增加...
}SPLITSCREENDISPLAY_TYPE;               //分屏显示标志

typedef enum
{
    DisplayAction,                      //显示
    ClearAciton                         //不显示，即清除
}DISPLAY_ACTION_TYPE;                   //显示行为类型，用于状态和报警提示

/*声明外部函数----------------------------------------------------------------*/
/** 
 * @brief  显示模块初始化并打开
 * @note   打开后默认显示是空白
 * @retval None
 */
extern void Display_Init(void);

/** 
 * @brief  显示模块关闭
 * @note   
 * @retval None
 */
extern void Diplay_Closed(void);
/** 
 * @brief  中文提示区名称部分滚动显示函数
 * @note   这个函数要放在定时器中，定时执行，当中文提示区名称显示不下时，会自动启用
 * @retval None
 */
extern void RollDiplay_ChineseHintArea(void);


#if (MeterType == ThreePhaseMeter)       //三相模式
/** 
 * @brief  显示象限区状态
 * @note   
 * @param  number: 1：第一象限，2：第二象限，3：第三象限，4：第4象限， 其他值无效
 * @retval None
 */
extern void Display_QuadrantStatus(unsigned char number);
#endif
/** 
 * @brief  显示或者不显示公钥状态
 * @note   
 * @param  displayaction: 参见DISPLAY_ACTION_TYPE枚举类型
 * @retval None
 */
extern void Display_PublicKeyStatus(DISPLAY_ACTION_TYPE displayaction);
/** 
 * @brief  显示或者不显示红外认证状态
 * @note   
 * @param  displayaction: 
 * @retval None
 */
extern void Display_InfraredAuthenticationStatus(DISPLAY_ACTION_TYPE displayaction);
/** 
 * @brief  显示或者不显示电能表挂起状态
 * @note   
 * @param  displayaction: 参见DISPLAY_ACTION_TYPE枚举类型
 * @retval None
 */
extern void Display_SuspendedStatus(DISPLAY_ACTION_TYPE displayaction);



/** 
 * @brief  显示电量函数
 * @note  
 * @param  phase: 代表相位 具体参见PHASE_TYPE枚举 
 * @param  engerytype: 电量种类，具体参见ENERGY_TYPE枚举
 * @param  date:    日期 0~12，0表示当前  其他代表上x月
 * @param  rate:    费率 0~12，其中0代表总，其他代表Tx
 * @param  engerypoint: 指向电量存储的数组，默认6字节BCD码，最低字节代表第3,4小数
 * @param  decimalpoint: 代表显示的电量显示几位小数，0~4
 * @param  plusminus: 代表是否显示负号，    Plus代表不显示，Minus代表显示
 * @param  displayhighzero: 高位是否显零，具体参见HIGHZERO_TYPE枚举
 * @retval None
 */
extern void Display_Engery(PHASE_TYPE phase,ENERGY_TYPE engerytype,unsigned char date,unsigned char rate,unsigned char* engerypoint,unsigned char decimalpoint,PLUS_MINUS plusminus,HIGHZERO_TYPE displayhighzero);

/** 
 * @brief  显示当前日期
 * @note   
 * @param  datepoint: 指向电量存储的数组，默认3字节BCD码，最低字节代表日
 * @retval None
 */
extern void Display_CurrentDate(unsigned char* datepoint);

/** 
 * @brief  显示当前时间
 * @note   
 * @param  timepoint: 指向时间存储的数组，默认3字节BCD码，最低字节代表秒
 * @retval None
 */
extern void Display_CurrentTime(unsigned char* timepoint);

/** 
 * @brief  显示当前剩余金额
 * @note   三相显示“当前剩余电费” 单相显示“当前剩余金额”
 * @param  amountpoint: 指向剩余金额存储的数组，默认4字节BCD码，最低字节代表小数1、2位
 * @param  displayhighzero: 高位是否显零，0代表不显示， 1代表显示
 * @retval None
 */
extern void Display_RemainingAmount(unsigned char* amountpoint,unsigned char displayhighzero);

/** 
 * @brief  显示当前透支金额
 * @note   三相显示“当前透支电费” 单相显示“当前透支金额”
 * @param  amountpoint: 指向透支金额存储的数组，默认4字节BCD码，最低字节代表小数1、2位
 * @param  displayhighzero: 高位是否显零，0代表不显示， 1代表显示
 * @retval None
 */
extern void Display_OverdraftAmount(unsigned char* amountpoint,unsigned char displayhighzero);


#endif
/*end------------------------------------------------------------------------*/
