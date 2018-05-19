/*******************************************************************************
* @file      : LCD_config.h
* @author    : Jiangsh
* @version   : V1.0.0
* @date      : Tue May 15 2018
* @brief     : LCD模块的配置头文件
********************************************************************************
* @attention :如果本文本中存在汉字变量，文本要转化成GB2312编码格式保存和打开
*
*
*/
/* 条件编译-------------------------------------------------------------------*/
#ifndef _LCD_CONFIG_H
#define _LCD_CONFIG_H

/*头文件----------------------------------------------------------------------*/
#include "ht6xxx.h"         //MCU对应的寄存器头文件

/*宏定义----------------------------------------------------------------------*/

//液晶型号

#define LCDType HG160800X_ST75163
//选项
#define HG160800X_ST75163   1 //液晶型号：华田HG160800X,驱动芯片:矽创ST75163


//显示模式
#define MeterType  ThreePhaseMeter
//选项
#define OnePhaseMeter 1       // 单相表显示模式
#define ThreePhaseMeter 2     // 三相表显示模式


/*配置----------------------------------------------------------------------*/

/* LCD片选脚 */
#define CS_High()           HT_GPIOB->PTSET |= (1<<10)      
#define CS_Low()            HT_GPIOB->PTCLR |= (1<<10)      

/* LCD的指令\数据选择脚 */
#define A0_High()           HT_GPIOB->PTSET |= (1<<9)     
#define A0_Low()            HT_GPIOB->PTCLR |= (1<<9)      

/* LCD的复位脚 */
#define RST_High()           HT_GPIOB->PTSET |= (1<<8)      
#define RST_Low()            HT_GPIOB->PTCLR |= (1<<8)      

/* LCD的时钟脚 */
#define SCK_High()           HT_GPIOB->PTSET |= (1<<7)      
#define SCK_Low()            HT_GPIOB->PTCLR |= (1<<7)    

/* LCD的数据脚 */
#define SDA_High()          {HT_GPIOB->PTDIR |= (1<<6); HT_GPIOB->PTSET |= (1<<6);}      
#define SDA_Low()           {HT_GPIOB->PTDIR |= (1<<6); HT_GPIOB->PTCLR |= (1<<6);}      
#define SDA_IN()             HT_GPIOB->PTDIR &= ~(1<<6)     
#define SDA_STATUS()         HT_GPIOB->PTDAT &= (1<<6)

/* LCD的管脚初始配置：该宏定义被LCD_Init调用，而LCD_Init被Display_Init()调用，理论上main函数中只要调用Display_Init()即可 */
#define LCD_GPIO_Init()     {HT_CMU->WPREG = 0xA55A;HT_GPIOB->IOCFG &= ~0x07c0;HT_CMU->WPREG = 0x0000;\
                             HT_GPIOB->PTCLR |= 0x07c0;HT_GPIOB->PTSET |= 0x06c0;\
                             HT_GPIOB->PTOD  |= 0x07c0;	HT_GPIOB->PTDIR |= 0x07c0;}

#endif
/*end------------------------------------------------------------------------*/

