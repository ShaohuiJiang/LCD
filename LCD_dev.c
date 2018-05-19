/*******************************************************************************
* @file      : LCD_dev.c
* @author    : Jiangsh
* @version   : V1.0.0
* @date      : Tue May 15 2018
* @brief     : 
********************************************************************************
* @attention :������ı��д��ں��ֱ������ı�Ҫת����GB2312�����ʽ����ʹ�
*
*
*/
/*ͷ�ļ�----------------------------------------------------------------------*/
///���ͷ�ļ�
#include "LCD_dev.h" 
#include "CharLib.h"
#include "LCD_config.h"
/*�궨��----------------------------------------------------------------------*/


/*�ڲ���������----------------------------------------------------------------*/
/* LCD�Ļ������� */
static unsigned char LCDRAM_Buf[seg][Page];

/*�����ڲ�����----------------------------------------------------------------*/
static void Delay_Nms(unsigned int n);
static void SendByte(unsigned char Dbyte);
static void Writecom(unsigned char wcom);
static void Writedata(unsigned char wdata);
static void Set_OTP_Register(void);
static void LCD_Config_Init(void);
 //�ú���û���õ��������Σ�����������澯 static unsigned char Readcom(void);
 //�ú���û���õ��������Σ�����������澯 static void Clear_ICON_DDRAM(void);
 //�ú���û���õ��������Σ�����������澯 static void OTP_Write(void);
static void window(void);
static void set_window_area(unsigned short startseg,unsigned short startpage,unsigned short endseg,unsigned short endpage);
static void LCDRAM_Buf_DrawPoint(unsigned short x,unsigned short y,unsigned char bit);
/*�����ڲ�����----------------------------------------------------------------*/

 /** 
  * @brief  ���뼶��ʱ
  * @note   
  * @param  n: 0~65565
  * @retval None
  */
static void Delay_Nms(unsigned int n) 
{
    unsigned int i,j;
    for(i=0;i<n;i++)
    for(j=0;j<1000;j++);
}

/*�ڲ���LCDͨ�ź���------------------------*/
/** 
 * @brief  ��LCD����һ���ֽ�
 * @note   �ֽڿ���������Ҳ���������ݣ���ʹ�û���
 * @param  Dbyte: һ���ֽ�
 * @retval None
 */
static void SendByte(unsigned char Dbyte)
{
    unsigned char i,j;
    
    for(i=0 ;i< 8 ;i++)
    {
        SCK_Low();
        
        j=0X80&Dbyte;
       
        Dbyte=Dbyte<< 1;   
        
        if(j&0x80)
        {
            SDA_High();
        }
        else
            SDA_Low();      //�Ƴ���λ��SDA
        
        SCK_High();	
        SCK_Low();	
    }
}

/** 
 * @brief  ��LCD����һ���ֽ�����
 * @note   
 * @param  wcom: һ���ֽ�����
 * @retval None
 */
static void Writecom(unsigned char wcom)
{
    CS_Low();
    A0_Low();
    SendByte(wcom);
    CS_High();
}

/** 
 * @brief  ��LCD����һ���ֽ�����
 * @note   
 * @param  wdata: һ���ֽ�����
 * @retval None
 */
static void Writedata(unsigned char wdata)
{
    CS_Low();
    A0_High();
    SendByte(wdata);
    CS_High();
}

/** 
 * @brief  ��LCD��һ���ֽ�����
 * @note   
 * @retval ����������
 */
/*�ú���û���õ��������Σ�����������澯
static unsigned char Readcom(void)
{	
    unsigned char i,L0;
	L0=0;
	Writecom(0x38);     	
    Writecom(0x7F);     	//ʹ�ܶ�ID
	Writecom(0x30);     	

	CS_Low();
    A0_Low();
    SendByte(0xFE) ;
    A0_High();
  
   	CS_Low();
	SDA_High();
  	A0_High();
	
	SDA_IN();
    for(i=0;i<8;i++)
    {
  		SCK_Low();
  		if(SDA_STATUS() == (1<<6))
  		L0=L0+1;
  	
  		SCK_High();
  	    if(i<7)
   	    L0=L0<<1;
    }
    CS_High() ;
	Writecom(0x38);     	
    Writecom(0x7E);     	
	Writecom(0x30);     

    return L0;	
}
*/
/** 
 * @brief  ���LCD��ICON RAM�������ݣ�����ֹICON RAM
 * @note   
 * @retval None
 */
 /*�ú���û���õ��������Σ�����������澯
static void Clear_ICON_DDRAM(void)
{
    unsigned char j;
    Writecom(0x30);	    //Extension Command 1
    Writecom(0x77);	    //Enable ICON RAM

    Writecom(0x15);    	//Column Address Setting 
    Writedata(0x00);    //Starting column address 
    Writedata(0x9F);    //Ending column address
    Writecom(0x5c); 	//Write data
    for(j=0;j<seg;j++)
    {
        Writedata(0x00);
    }
    Writecom(0x76);	    //Disable ICON RAM  
}
*/
/** 
 * @brief  ִ�����������OTP��ID
 * @note   ��������Ҳ���Ǻ����������Ҫ��Һ������
 * @retval None
 */
 /*�ú���û���õ��������Σ�����������澯
static void OTP_Write(void)   
{    
    Writecom(0x30);  // Extension Command 1 
    Writecom(0xAE);  // Display OFF 
    Delay_Nms(50);  // Delay 50ms 
    Writecom(0x39);  //Enable OTP 
    Writecom(0XD6);   
    Writedata(0x10);   
    
    Writecom(0x31);  // Extension Command 2 
    Writecom(0XF0);  // Frame Rate = 73Hz 
    Writedata(0x0D);   
    Writedata(0x0D);   
    Writedata(0x0D);   
    Writedata(0X0D);   
    
    Writecom(0xE4);  // OTP Selection Control 
    Writedata(0x99);   
    Writecom(0xE5);  // OTP Programming Setting 
    Writedata(0x0F);   
    Writecom(0xE0);  // OTP WR/RD Control 
    Writedata(0x20);   
    Delay_Nms(100);  // Delay 100ms 
    Writecom(0xE2);  // OTP Write 
    Delay_Nms(100);  // Delay 100ms 
    Writecom(0xE1);  // OTP Control Out 
    Writecom(0x30);  // Extension Command 1 
} 
*/

/** 
 * @brief  ����ID
 * @note   ID������ʲô�����������Ҫ��Һ������
 * @retval None
 */
static void Set_OTP_Register(void)   
{   
    Writecom(0x38);  // Extension Command 3 
    Writecom(0xD5);  // Set ID=3
    Writedata(0x03);   
}
/** 
 * @brief  LCD���ó�ʼ��
 * @note   �ú�������ǰ��ȷ��LCD�ٿعܽ��Ѿ����õ�λ
 * @retval None
 */
static void LCD_Config_Init(void)
{
	int Data = 0;
    
    ///��λLCD����оƬ
    RST_Low();
    Delay_Nms(20);
    RST_High();
    Delay_Nms(20);
 
    ///��չ����2�����������
    Writecom(0x31); // Extension Command 2
    ////OTP�Զ���ȡ��״̬�رգ���
    Writecom(0xD7); // Disable Auto Read
    Writedata(0x9F);
    ////ʹ��OTP��״̬����
    Writecom(0xE0); // Enable OTP Read
    Writedata(0x00);
    Delay_Nms(20);
    
    ////����OTP��̹��̣���
    Writecom(0xE3); // OTP Up-Load
    Delay_Nms(20);
    ////ȡ��OTP����
    Writecom(0xE1); // OTP Control Out
    
    ///��չ����1����������
    Writecom(0x30); // Extension Command 1
    ////�˳�����״̬
    Writecom(0x94); // Sleep Out
    ////�ر���ʾ
    Writecom(0xAE); // Display OFF
    Delay_Nms(50);
    ////����ѹ��·
    Writecom(0x20); //Power Control
    Writedata(0x0B); // VB, VR,VF All ON
    Delay_Nms(100);
    ////����Vop��ѹֵ
    Writecom(0x81); // Set Vop = 14.0V
    Writedata(0x04);
    Writedata(0x04);

    // Frame Rate��֡�ʣ�
    ///��չ����2�����������
    Writecom(0x31);   // Extension Command 2
    ////���ò�ͬ�¶��µ�֡��
    Writecom(0XF0);   // Frame Rate
    Writedata(0x02);  // 34.5Hz  //����-30  -40Ч����ѣ�-40~TA��
    Writedata(0x06);  // 46(TA~TB)
    Writedata(0x14);  // 83(TB~TC)
    Writedata(0x1c);  // 138(TC~90)
    ////TA/TB/TC���¶ȵ�
    Writecom(0XF2);   // Temperature Range
    Writedata(0x06);  // -34C��TA��
    Writedata(0x1c);  // -12C (TB)
    Writedata(0x50);  //  40C (TC)
    
    //Temperature Gradient Compensation(�¶��ݶȲ���ϵ��)
    Writecom(0xf4);
    Writedata(0x10) ;  //����-30  -40Ч����� ������ VOP=12.7V(C9����)
    Writedata(0x11);  //����-30  -40Ч�����
    Writedata(0x00);
    Writedata(0x00);
    Writedata(0x00);
    Writedata(0x11);
    Writedata(0x51);
    Writedata(0x35);

    ///��չ����2�����������
    Writecom(0x31); // Extension Command 2
    ////��ָ������������ǿ��Ч�ʺ�ƫ�ñȡ�
    Writecom(0x32); // Analog Circuit Set
    Writedata(0x00);
    Writedata(0x01); // Booster Efficiency =Level1
    Writedata(0x04); //Bias=1/10
	////��ָ�����ڿ���������ѹ��·���ṩ������ѹ���ĵ�Դ					
    Writecom(0x51); // Booster Level x10
    Writedata(0xFB);
    
	///��չ����2�����������					
    Writecom(0x30); // Extension Command 1
    ///��ָ�����ʾģʽΪ�Ҷ�ģʽ��ɫģʽ������Ϊ��ɫģʽ
    Writecom(0xF0); //Display Mode
    Writedata(0x10); //Mono Mode
    ///������ʾ����
    Writecom(0xCA); //Display Control
    Writedata(0x00); // CL Dividing Ratio => Not Divide//����CL�ָ����
    Writedata(0X4F); //Duty Set => 80 Duty//
    Writedata(0x00); //Frame Inversion
						
    Writecom(0xBC); // Data Scan Direction������ɨ�跽��
    Writedata(0x02);//00 �� 02 ɨ��˳��//00�Ǵ������ң��������£�02�Ǵ������󣬴�������
    Writecom(0xA6); // Normal Display//������ʾ
            
    Writecom(0x31); //Extension Command 2
    Writecom(0x40); //Internal Power Supply���ڲ���Դ��
    Writecom(0x30); // Extension Command 1

    // icon clear��ͼ��ram�����㣩
    Writecom(0x77); // Enable ICON RAM
    Writecom(0x5C);
    for(Data = 0; Data <= 255; Data++)
    {
        Writedata(0);
    }
    
    Writecom(0x76); // Disable ICON RAM����ֹͼ��ram��

    Writecom(0x30); //Extension Command 1
    ////���ÿɷ��ʵ��е�ַ������
    Writecom(0x15); // Column Address Setting
    Writedata(0x00); // SEG0 -> SEG159
    Writedata(0x9F);
    ////���ÿɷ��ʵ�ҳ��ַ������
    Writecom(0x75); // Row Address Setting
    Writedata(0x00); // COM0 -> COM59
    Writedata(0x13);
    
    //����Լ�����Ļ�������Ҳ���LCD��DDRAM
    Clear_LCDRAM_Buf();
    Refresh_LCD_DDRAM();
    Writecom(0xAF); // Display ON������ʾ��
}

/*�ڲ�������LCDоƬ��ʾ��ˢ�·�Χ����------------------------*/
/** 
 * @brief  ����LCD������DDRAM���򶼿�д
 * @note   
 * @retval None
 */
static void window(void)
{
 	Writecom(0x30);    	//Extension Command 1 
	Writecom(0x15);    	//Column Address Setting 
	Writedata(0x00);    //Starting column address
	Writedata(0x9F);    //Ending column address

	Writecom(0x75);    	//Row Address Setting 
	Writedata(0x00);    //Starting page address 
	Writedata(0x13); 	//Ending page address
	Writecom(0x5c); 	//Write data
}

/** 
 * @brief  ���ÿ�дDDRAM����
 * @note   ͨ�����������Ӧ��LCDд�ĵ�һ�������Ƕ�ӦҺ����������ⷶΧ��ǰ�պ�
 * @param  startseg: ��ʼ�е�ַ
 * @param  startpage: ��ʼҳ��ַ
 * @param  endseg: �����е�ַ
 * @param  endpage: ����ҳ��ַ
 * @retval None
 */
static void set_window_area(unsigned short startseg,unsigned short startpage,unsigned short endseg,unsigned short endpage)
{
 	Writecom(0x30);    	                        //Extension Command 1 
	Writecom(0x15);    	                        //Column Address Setting 
	Writedata((unsigned char)startseg);         //Starting column address
	Writedata(((unsigned char)endseg-1));       //Ending column address

	Writecom(0x75);    	                        //Row Address Setting 
	Writedata((unsigned char)startpage);        //Starting page address 
	Writedata(((unsigned char)endpage-1)); 	    //Ending page address
	Writecom(0x5c); 	                        //Write data    
}



/*�ڲ�������LCDRAM_Buf���麯��------------------------*/
/** 
 * @brief  LCDRAM_Buf����λ����㺯��
 * @note   (x,y)λ�õ�ĳ�㣬��ʾ���߲���ʾ��
 * ע�⣬���ֻ�����˻������ĵ㣬������ʾ��Ҫ��������������������д��LCD
 * @param  x: seg��λ��
 * @param  y: com��λ��
 * @param  bit: 0������ʾ��1����ʾ
 * @retval None
 */
static void LCDRAM_Buf_DrawPoint(unsigned short x,unsigned short y,unsigned char bit)
{
    unsigned short pos;
    unsigned short bx;
    unsigned char temp=0;

    if(x>=seg||y>=com)return;       //������Χ
    pos=y/8;        //�õ�ҳ��ַ       
    
    bx=y%8;         //�õ�����ҳ��ַ��bitλ
    temp=1<<(7-bx);

    if(bit)
    {
        LCDRAM_Buf[x][pos]|=temp;
    }
    else 
    {
        LCDRAM_Buf[x][pos]&=~temp; 
    }   
}


/*����ȫ�ֺ���----------------------------------------------------------------*/

/*LCDӲ����غ���---------------------------*/

/** 
 * @brief  LCD���ܳ�ʼ������
 * @note   �����˹ܽų�ʼ�������ó�ʼ��������ID
 * @retval None
 */
extern void LCD_Init(void)
{
    LCD_GPIO_Init();
    LCD_Config_Init();  
    Set_OTP_Register();       
}

extern void Closed_LCD(void)
{
    ///��չ����1����������
    Writecom(0x30); // Extension Command 1
    ////�ر���ʾ
    Writecom(0xAE); // Display OFF
    ////�˳�����״̬
    Writecom(0x95); // Sleep IN
    Delay_Nms(100);
    ///�õ�LCD����оƬ��λ��
    RST_Low();
}

/*����LCDRAM_Buf���麯��------------------------*/

/** 
 * @brief  ��LCDRAM_Buf��ָ��λ����ʾ�����һ���ַ�(�������֡���ĸ�����֡�����)
 * @note   ��㷽ʽ������ʽ������Ļ���ȷ��ͬһλ����ʾ�˶�Ӧ�ַ�����Ȼ����֤���Ч��
 * @param  x: ָ����ʼλ�õ�seg
 * @param  y: ָ����ʼλ�õ�com
 * @param  charbufstartaddress: �ַ�����ģ��ʼ��ַ
 * @param  size: �ַ��ߴ�
 * @param  displayorclear: clear���������display������ʾ
 * @retval None
 */
extern void InputCharacter_to_LCDRAM_Buf(unsigned short x,unsigned short y,const unsigned char* charbufstartaddress,unsigned int size,unsigned char displayorclear)
{
    unsigned char temp;
    unsigned short y0;
    unsigned int t,t1,segnumber,comnumber,bytesnumber; 

    y0 = y;

    segnumber = size/100;

    comnumber = size%100;

    
    bytesnumber = segnumber*(comnumber/8+((comnumber%8)?1:0));      //�õ���Ҫ��ʾ���õ��ֽ���

    for(t=0;t<bytesnumber;t++)                                      //����ʾ���õ��ֽ�ȫ��д��LCDRAM_Buf������
    {     
        temp=*(charbufstartaddress+t);
        for(t1=0;t1<8;t1++) 
        {
            if(temp&0x80)
            {

                if((x>=seg)||(y>=com))  //����Χ��
                {
                    return;             //�������鷶Χ�ģ���д
                }

                if(displayorclear == display)      //д1������ʾ
                {
                    LCDRAM_Buf_DrawPoint(x,y,1);
                }
                else                                //д0�������
                {
                    LCDRAM_Buf_DrawPoint(x,y,0);
                }

            }
            temp<<=1;
            y++;
            if((y-y0)==(unsigned short)(size%100))
            {
                y=y0; x++;
                break;
            }
        }
    }
}

/** 
 * @brief  ���LCDRAM_Buf������ָ����Χ�ڵ�����
 * @note   ע�⣬��Χ����ǰ�պ󿪷�ʽ������ʼ��ᱻ����������㲻�ᱻ���
 * @param  x1: ��ʼseg��0~(seg-1)
 * @param  y1: ��ʼcom 0~(com-1)
 * @param  x2: ����seg 1~seg
 * @param  y2: ����com 1~com
 * @retval None
 */
extern void Clear_PartArea_of_LCDRAM_Buf(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2)
{
    unsigned short j,k;
    if((x1>=seg)||(y1>=com)||(x2>seg)||(y2>com))//λ�ó���Χ�ˣ�ֱ�ӷ���
    {
        return;         
    }
    if((x1>=x2)||(y1>=y2))  //��ʼλ�ñ���С�ڽ���λ�ã�����ֱ�ӷ���
    {
        return;
    }

    for(j=y1;j<y2;j++)
    {
        for(k=x1;k<x2;k++)
        {
            LCDRAM_Buf_DrawPoint(k,j,0);  
        }       
    }
}

/** 
 * @brief  LCDRAM_Buf��������
 * @note   
 * @retval None
 */
extern void Clear_LCDRAM_Buf(void)
{ 
    Clear_PartArea_of_LCDRAM_Buf(0,0,seg,com);
}

#if (MeterType == ThreePhaseMeter)
/** 
 * @brief  ���LCDRAM_Buf�����������������
 * @note   
 * @retval None
 */
extern void Clear_QuadrantArea_Of_LCDRAM_Buf(void)
{
    Clear_PartArea_of_LCDRAM_Buf(QuadrantAreaStartSeg,QuadrantAreaStartCom,QuadrantAreaEndSeg,QuadrantAreaEndCom);
}
#endif 

/** 
 * @brief  ���LCDRAM_Buf�����������ʾ��������
 * @note   
 * @retval None
 */
extern void Clear_ChineseHintArea_Of_LCDRAM_Buf(void)
{
    Clear_PartArea_of_LCDRAM_Buf(ChineseHintAreaStartSeg,ChineseHintAreaStartCom,ChineseHintAreaEndSeg,ChineseHintAreaEndCom);
}

/** 
 * @brief  ���LCDRAM_Buf�����������������
 * @note   
 * @retval None
 */
extern void Clear_NumberArea_Of_LCDRAM_Buf(void)
{
    Clear_PartArea_of_LCDRAM_Buf(NumberAreaStartSeg,NumberAreaStartCom,NumberAreaEndSeg,NumberAreaEndCom);
}

/** 
 * @brief  ���LCDRAM_Buf����ı�����ʾ�͵�λ��������
 * @note   
 * @retval None
 */
extern void Clear_AlarmHintArea_Of_LCDRAM_Buf(void)
{
    Clear_PartArea_of_LCDRAM_Buf(AlarmHintAreaStartSeg,AlarmHintAreaStartCom,AlarmHintAreaEndSeg,AlarmHintAreaEndCom);
}
extern void Clear_UnitArea_Of_LCDRAM_Buf(void)
{
    Clear_PartArea_of_LCDRAM_Buf(UnitAreaStartSeg,UnitAreaStartCom,UnitAreaEndSeg,UnitAreaEndCom);
}
/** 
 * @brief  ���LCDRAM_Buf�����״̬��ʾ��������
 * @note   
 * @retval None
 */
extern void Clear_StatusHintArea_Of_LCDRAM_Buf(void)
{
    Clear_PartArea_of_LCDRAM_Buf(StatusHintAreaStartSeg,StatusHintAreaStartCom,StatusHintAreaEndSeg,StatusHintAreaEndCom);
}

/*ˢ��LCDоƬ��ʾ������------------------------*/
/** 
 * @brief  ˢ��LCD��������ʾ����
 * @note   ���Ա�������LCDRAM_Buf�е�����Ϊ׼
 * @retval none
 */
extern void Refresh_LCD_DDRAM(void)
{  
    unsigned char i,j;
    window();
    for(i=0;i<Page;i++)         //ҳ��ַ��Χ
    {
        for(j=0;j<seg;j++)      //�ε�ַ��Χ
        {
            Writedata(LCDRAM_Buf[j][i]);
        }
    }
}

#if (MeterType == ThreePhaseMeter)
/** 
 * @brief  ˢ��LCD����������ʾ����
 * @note   ���Ա�������LCDRAM_Buf�е�����Ϊ׼
 * @retval None
 */
extern void Refresh_QuadrantArea_of_LCD_DDRAM(void)
{
    unsigned char i,j;
    set_window_area(QuadrantAreaStartSeg,QuadrantAreaStartPageCom,QuadrantAreaEndSeg,QuadrantAreaAreaEndPageCom);   //ȷ��LCD����ʾ����
    for(i=QuadrantAreaStartPageCom;i<QuadrantAreaAreaEndPageCom;i++)         //ҳ��ַ��Χ
    {
        for(j=QuadrantAreaStartSeg;j<QuadrantAreaEndSeg;j++)      //�ε�ַ��Χ
        {
            Writedata(LCDRAM_Buf[j][i]);
        }
    }
}
#endif 
/** 
 * @brief  ˢ��ָ����Χ��Һ����ʾ
 * @note   ǰ�պ�
 * @param  startseg: ��ʼseg
 * @param  startpage: ��ʼpage
 * @param  endseg: ����seg
 * @param  endpage: ����page
 * @retval None
 */
extern Refresh_PartArea_of_LCD_DDRAM(unsigned char startseg,unsigned char startpage,unsigned char endseg,unsigned char endpage )
{
    unsigned char i,j;
    set_window_area(startseg,startpage,endseg,endpage); //ȷ��LCD����ʾ����
    for(i=startpage;i<endpage;i++)                      //ҳ��ַ��Χ
    {
        for(j=startseg;j<endseg;j++)                    //�ε�ַ��Χ
        {
            Writedata(LCDRAM_Buf[j][i]);
        }
    }    
}
/** 
 * @brief  ˢ��LCD��������ʾ����ʾ����
 * @note   ���Ա�������LCDRAM_Buf�е�����Ϊ׼
 * @retval None
 */
extern void Refresh_ChineseHintArea_of_LCD_DDRAM(void)
{
    unsigned char i,j;
    set_window_area(ChineseHintAreaStartSeg,ChineseHintAreaStartPageCom,ChineseHintAreaEndSeg,ChineseHintAreaEndPageCom);   //ȷ��LCD����ʾ����
    for(i=ChineseHintAreaStartPageCom;i<ChineseHintAreaEndPageCom;i++)         //ҳ��ַ��Χ
    {
        for(j=ChineseHintAreaStartSeg;j<ChineseHintAreaEndSeg;j++)      //�ε�ַ��Χ
        {
            Writedata(LCDRAM_Buf[j][i]);
        }
    }
}

/** 
 * @brief  ˢ��LCD����������ʾ����
 * @note   ���Ա�������LCDRAM_Buf�е�����Ϊ׼
 * @retval None
 */
extern void Refresh_NumberArea_of_LCD_DDRAM(void)
{
    unsigned char i,j;
    set_window_area(NumberAreaStartSeg,NumberAreaStartPageCom,NumberAreaEndSeg,NumberAreaEndPageCom);   //ȷ��LCD����ʾ����
    for(i=NumberAreaStartPageCom;i<NumberAreaEndPageCom;i++)         //ҳ��ַ��Χ
    {
        for(j=NumberAreaStartSeg;j<NumberAreaEndSeg;j++)      //�ε�ַ��Χ
        {
            Writedata(LCDRAM_Buf[j][i]);
        }
    }
}

/** 
 * @brief  ˢ��LCD�ı�������ʾ����
 * @note   ���Ա�������LCDRAM_Buf�е�����Ϊ׼
 * @retval None
 */
extern void Refresh_AlarmHintArea_of_LCD_DDRAM(void)
{
    unsigned char i,j;
    set_window_area(AlarmHintAreaStartSeg,AlarmHintAreaStartPageCom,AlarmHintAreaEndSeg,AlarmHintAreaEndPageCom);   //ȷ��LCD����ʾ����
    for(i=AlarmHintAreaStartPageCom;i<AlarmHintAreaEndPageCom;i++)         //ҳ��ַ��Χ
    {
        for(j=AlarmHintAreaStartSeg;j<AlarmHintAreaEndSeg;j++)      //�ε�ַ��Χ
        {
            Writedata(LCDRAM_Buf[j][i]);
        }
    }
}
/** 
 * @brief  ˢ��LCD�ĵ�λ����ʾ����
 * @note   ���Ա�������LCDRAM_Buf�е�����Ϊ׼
 * @retval None
 */
extern void Refresh_UnitArea_of_LCD_DDRAM(void)
{
    unsigned char i,j;
    set_window_area(UnitAreaStartSeg,UnitAreaStartPageCom,UnitAreaEndSeg,UnitAreaEndPageCom);   //ȷ��LCD����ʾ����
    for(i=UnitAreaStartPageCom;i<UnitAreaEndPageCom;i++)         //ҳ��ַ��Χ
    {
        for(j=UnitAreaStartSeg;j<UnitAreaEndSeg;j++)      //�ε�ַ��Χ
        {
            Writedata(LCDRAM_Buf[j][i]);
        }
    }
}
/** 
 * @brief  ˢ��LCD��״̬����ʾ����
 * @note   ���Ա�������LCDRAM_Buf�е�����Ϊ׼
 * @retval None
 */
extern void Refresh_StatusHintArea_of_LCD_DDRAM(void)
{
    unsigned char i,j;
    set_window_area(StatusHintAreaStartSeg,StatusHintAreaStartPageCom,StatusHintAreaEndSeg,StatusHintAreaEndPageCom);   //ȷ��LCD����ʾ����
    for(i=StatusHintAreaStartPageCom;i<StatusHintAreaEndPageCom;i++)         //ҳ��ַ��Χ
    {
        for(j=StatusHintAreaStartSeg;j<StatusHintAreaEndSeg;j++)      //�ε�ַ��Χ
        {
            Writedata(LCDRAM_Buf[j][i]);
        }
    }
}

/** 
 * @brief  дLCDRAM_Buf���麯��
 * @note   
 * @param  x: segֵ
 * @param  y: pageֵ
 * @param  Buf: ��д������
 * @retval None
 */
extern void Wirte_LCDRAM_Buf(unsigned short x, unsigned short y, unsigned char Buf)
{
    if((x>=seg)||(y>=Page))    //����Χ
    {
        return;
    }
    LCDRAM_Buf[x][y] = Buf;

}
/*end-------------------------------------------------------------------------*/

