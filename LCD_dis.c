/*******************************************************************************
* @file      : LCD_dis.c
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
#include "LCD_dis.h"
#include "CharLib.h"
#include "LCD_dev.h"
#include "string.h"




/*�궨��----------------------------------------------------------------------*/
#define ChineseHintAreaGBKBufSize 20                    //������ʾ��GBK�뻺�����ߴ�
#define ChineseHintAreaLCDRAMBackupBufSegSize   320     //������ʾ�����õ��󻺴����ߴ�




/*�ڲ���������----------------------------------------------------------------*/
static short ChineseHintAreaGBKBuf[ChineseHintAreaGBKBufSize];  //������ʾ��GBK�뻺����
static unsigned char ChineseHintAreaLCDRAMBackupBuf[ChineseHintAreaLCDRAMBackupBufSegSize][ChineseHintAreaEndPageCom-ChineseHintAreaStartPageCom];  //������ʾ�����õ��󻺴���

static unsigned char  ChineseHintArea_RollDisplay;              //������ʾ���������Ƿ����ö�̬��ʾ��־��0�����ã�1�Ǵ������ã�ע�⣬��ʼ��ʱĬ�����ã�ÿ����������ʾ��ʱ������ 
static unsigned char  ChineseHintArea_SplitScreenDisplay;       //������ʾ���ķ����Ƿ����ñ�־��0�����ã�1�������ã�ע�⣬��ʼ��ʱĬ�����ã�ÿ����������ʾ��ʱ������


/*�����ڲ�����----------------------------------------------------------------*/
//����������ʾ��GBK�뻺�����ĺ���
static void Clear_ChineseHintAreaGBKBuf(void);
static void Wirte_ChineseHintAreaGBKBuf(unsigned char index,short gbkcode);
static short Read_ChineseHintAreaGBKBuf(unsigned char index);
static unsigned char Read_GBKNum_ChineseHintAreaGBKBuf(void);
static void StrToChineseHintAreaGBKBuf(char *str);

//����������ʾ�����õ��󻺴����ߴ�
static void Clear_ChineseHintAreaLCDRAMBackupBuf(void);
static void ChineseHintAreaLCDRAMBackupBuf_DrawPoint(unsigned short x,unsigned short y,unsigned char bit);
static void InputCharacter_to_ChineseHintAreaLCDRAMBackupBuf(unsigned short x,unsigned short y,const unsigned char* charbufstartaddress,unsigned int size,unsigned char displayorclear);
static unsigned short Read_SEGNum_ChineseHintAreaLCDRAMBackupBuf(void);


const unsigned char* Get_CharBufAddress( short gbkcode);
static void ChineseHintAreaGBKBufToChineseBackupBuf(void);
static void Copy_ChineseHintAreaGBKBuf_To_LCDRAM_Buf(unsigned short endseg,unsigned short offset);

static void Fill_Char_In_ChineseHintArea( char* strbuf,signed char SplitScreen);




/*�����ڲ�����----------------------------------------------------------------*/
/** 
 * @brief  ChineseHintAreaGBKBuf����
 * @note   
 * @retval None
 */
static void Clear_ChineseHintAreaGBKBuf(void)
{
    unsigned char i;
    for(i=0;i<ChineseHintAreaGBKBufSize;i++)
    {
        ChineseHintAreaGBKBuf[i] = 0;
    }
}
/** 
 * @brief  ��ChineseHintAreaGBKBufָ��λ��дgbk��
 * @note   ����Χ��ʲô������д
 * @param  gbkcode: gbk��
 * @retval None
 */
static void Wirte_ChineseHintAreaGBKBuf(unsigned char index,short gbkcode)
{
    if(index>=ChineseHintAreaGBKBufSize)
    {
        return ;
    }
    ChineseHintAreaGBKBuf[index] = gbkcode;
}
/** 
 * @brief  ��ȡChineseHintAreaGBKBufָ��λ�õ�gbk��
 * @note   ����Χ�ͷ���0
 * @param  index:  ����
 * @retval 0����Чgbk�룬����ֵ����Ӧ��gbk��
 */
static short Read_ChineseHintAreaGBKBuf(unsigned char index)
{
    if(index>=ChineseHintAreaGBKBufSize)
    {
        return 0;
    }  
    return ChineseHintAreaGBKBuf[index];
}
/** 
 * @brief  ChineseHintAreaGBKBuf�з�0��GBK������
 * @note   
 * @retval ����
 */
static unsigned char Read_GBKNum_ChineseHintAreaGBKBuf(void)
{
    unsigned char index = 0;
    short value;
    for(index=0;index<ChineseHintAreaGBKBufSize;index++)
    {
        value = Read_ChineseHintAreaGBKBuf(index);
        if(value == 0)
        {
            return index;
        }
    }
    return index;
}
/** 
 * @brief  ���ַ���ת��short�͵�GBK��д��ChineseHintAreaGBKBuf��
 * @note   
 * @param  *str: �ַ���
 * @retval None
 */
static void StrToChineseHintAreaGBKBuf(char *str)
{
    unsigned char offset;
    unsigned char i;
    int len;
    short tempgbk;
    
    Clear_ChineseHintAreaGBKBuf();                  //���
    len = strlen(str);
    offset = 0;
    for(i=0;i<len;i++)
    {
        if(*(str+offset) == 0)
        {
            return;
        }
        else if(*(str+offset)<0x80)       //��ĸ��������
        {
            tempgbk = (unsigned short)*(str+offset);
            Wirte_ChineseHintAreaGBKBuf(i,tempgbk);
            offset++;
        }
        else if(*(str+offset)>0x80)      //����
        {
            tempgbk = (unsigned short)*(str+offset)*256+(unsigned short)*(str+offset+1);
            Wirte_ChineseHintAreaGBKBuf(i,tempgbk);
            offset +=2;
        }
    }


}

/** 
 * @brief  ChineseHintAreaLCDRAMBackupBuf����
 * @note   
 * @retval None
 */
static void Clear_ChineseHintAreaLCDRAMBackupBuf(void)
{
    unsigned short i;
    unsigned char j;
    for(i=0;i<ChineseHintAreaLCDRAMBackupBufSegSize;i++)
    {
        for(j=0;j<(ChineseHintAreaEndPageCom-ChineseHintAreaStartPageCom);j++)
        {
            ChineseHintAreaLCDRAMBackupBuf[i][j] = 0;
        }
    }        
}
/** 
 * @brief  ChineseHintAreaLCDRAMBackupBuf��㺯��
 * @note   ����Χ�ĵ㣬ʲô����д
 * @param  x: seg��
 * @param  y: com��
 * @param  bit: 0��д0,1��д1
 * @retval None
 */
static void ChineseHintAreaLCDRAMBackupBuf_DrawPoint(unsigned short x,unsigned short y,unsigned char bit)
{
    unsigned short pos;
    unsigned short bx;
    unsigned char temp=0;

    if((x>=(ChineseHintAreaLCDRAMBackupBufSegSize)||y>=(ChineseHintAreaEndPageCom-ChineseHintAreaStartPageCom)*8))
    {
        return;       //������Χ
    }
    pos=y/8;          //�õ�ҳ��ַ       
    
    bx=y%8;           //�õ�����ҳ��ַ��bitλ
    temp=1<<(7-bx);
    if(bit)
    {
        ChineseHintAreaLCDRAMBackupBuf[x][pos]|=temp;
    }
    else 
    {
        ChineseHintAreaLCDRAMBackupBuf[x][pos]&=~temp; 
    }   
}
/** 
 * @brief  ���ַ��ĵ�����Ϣд��ChineseHintAreaLCDRAMBackupBufָ��λ�õ�
 * @note   
 * @param  x: segλ��
 * @param  y: comλ��
 * @param  charbufstartaddress: �ַ�������Ϣ
 * @param  size: �ߴ�
 * @param  displayorclear: ��ʾ�������
 * @retval None
 */
static void InputCharacter_to_ChineseHintAreaLCDRAMBackupBuf(unsigned short x,unsigned short y,const unsigned char* charbufstartaddress,unsigned int size,unsigned char displayorclear)
{
    unsigned char temp;
    unsigned short y0;
    unsigned int t,t1,segnumber,comnumber,bytesnumber; 

    y0 = y;
    segnumber = size/100;
    comnumber = size%100;
    bytesnumber = segnumber*(comnumber/8+((comnumber%8)?1:0));      //�õ���Ҫ��ʾ���õ��ֽ���
    
    for(t=0;t<bytesnumber;t++)                                      //����ʾ���õ��ֽ�ȫ��д��ChineseHintAreaLCDRAMBackupBuf������
    {     
        temp=*(charbufstartaddress+t);
        for(t1=0;t1<8;t1++) 
        {
            if(temp&0x80)
            {
                if(displayorclear == display)      //д1������ʾ
                {
                    ChineseHintAreaLCDRAMBackupBuf_DrawPoint(x,y,1);
                }
                else                              //д0�������
                {
                    ChineseHintAreaLCDRAMBackupBuf_DrawPoint(x,y,0);
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
 * @brief  �õ�ChineseHintAreaLCDRAMBackupBuf����Ч����
 * @note   ע��Ĭ��Ϊ�����ʼ�����������ķ������
 * @retval ��Ч������
 */
static unsigned short Read_SEGNum_ChineseHintAreaLCDRAMBackupBuf(void)
{
    unsigned short i;
    unsigned short len1;
    unsigned short len2;
    short gbk;
    unsigned int sizenumber;
    unsigned int size;

    #if (MeterType == ThreePhaseMeter)
    size = Size_12P12P;
    sizenumber = Size_6P12P;
    #else
    size = Size_14P14P;
    sizenumber = Size_7P14P;
    #endif

    len1 = Read_GBKNum_ChineseHintAreaGBKBuf();
    len2 = 0; 
    for(i=0;i<len1;i++)
    {  
        gbk = Read_ChineseHintAreaGBKBuf(i);
        if((gbk&0x8080) == 0x8080)
        {
            len2 += size/100;
        }
        else
        {
            len2 += sizenumber/100;
        }
    }

    return len2;
}
/** 
 * @brief  ����GBK�뷵���ַ��ֿ���������λ��
 * @note   
 * @param  gbkcode: gbk��
 * @retval ����λ�õ�ָ��
 */
const unsigned char* Get_CharBufAddress(short gbkcode)
{   
    unsigned char i;
    short temp;

    for(i=0;i<GBKNumber;i++)
    {
         temp = charaddressbuf[i].CharGbk;
        if(gbkcode == temp)
        {
            return charaddressbuf[i].CharAddress;
        }
    }
    //�Ҳ������ͷ�������0��λ��
    #if (MeterType == ThreePhaseMeter)
    return &ChineseHint_Char_6p12p[0][0];
    #else
    return &ChineseHint_Char_7p14p[0][0];    
    #endif

}
/** 
 * @brief  ��ChineseHintAreaGBKBuf�е�gbk��ת���ɵ�����Ϣ�浽ChineseBackupBuf
 * @note   
 * @retval None
 */
static void ChineseHintAreaGBKBufToChineseBackupBuf(void)
{
    unsigned char i;
    unsigned char len;
    short tempgbk;
    const unsigned char* address;
    unsigned int sizenumber;
    unsigned int size;
    unsigned short offset;

    Clear_ChineseHintAreaLCDRAMBackupBuf();         //���
    #if (MeterType == ThreePhaseMeter)
    size = Size_12P12P;
    sizenumber = Size_6P12P;
    #else
    size = Size_14P14P;
    sizenumber = Size_7P14P;
    #endif

    offset = 0;
    len = Read_GBKNum_ChineseHintAreaGBKBuf();
    for(i=0;i<len;i++)
    {
        tempgbk = Read_ChineseHintAreaGBKBuf(i);
        address = Get_CharBufAddress(tempgbk);
        if((tempgbk&0x8080) == 0x8080)  //����
        {
            InputCharacter_to_ChineseHintAreaLCDRAMBackupBuf(offset,0,address,size,display);
            offset += size/100;
        }
        else                         //������ĸ
        {
            InputCharacter_to_ChineseHintAreaLCDRAMBackupBuf(offset,0,address,sizenumber,display);
            offset += sizenumber/100;
        }
    }
}

/** 
 * @brief  ��ChineseHintAreaGBKBuf��Ч���ݸ��Ƶ�LCDRAM_Buf
 * @note   
 * @param  chinesehintareaLCDRAMendseg: LCDRAM_Buf�е�������ʾ�����Ƶı߽�
 * @param  offset: ChineseHintAreaGBKBuf��ʼ��ַ��ƫ��
 * @retval None
 */
static void Copy_ChineseHintAreaGBKBuf_To_LCDRAM_Buf(unsigned short chinesehintareaLCDRAMendseg,unsigned short offset)
{
    unsigned short i,j,len;
    unsigned short index;
    len = Read_SEGNum_ChineseHintAreaLCDRAMBackupBuf();
    if(offset>len)
    {
        return;
    }
    if(len<=(chinesehintareaLCDRAMendseg-ChineseHintAreaStartSeg))  //ChineseHintAreaGBKBuf��Ч�ı߽�С�ڵ���������ʾ�����Ƶı߽�
    {
        index = offset;
        for(i=0;i<(len-offset);i++)
        {
            index++;
            for(j=0;j<(ChineseHintAreaEndPageCom-ChineseHintAreaStartPageCom);j++)
            {
                Wirte_LCDRAM_Buf(ChineseHintAreaStartSeg+i,ChineseHintAreaStartPageCom+j,ChineseHintAreaLCDRAMBackupBuf[index][j]);
            }
        }  
    }
    else 
    {
        index = offset;
        for(i=0;i<(chinesehintareaLCDRAMendseg-ChineseHintAreaStartSeg);i++)
        {   
            index++;
            if(index >= len)
            {
                index = 0;
            }
            for(j=0;j<(ChineseHintAreaEndPageCom-ChineseHintAreaStartPageCom);j++)
            {
                Wirte_LCDRAM_Buf(ChineseHintAreaStartSeg+i,ChineseHintAreaStartPageCom+j,ChineseHintAreaLCDRAMBackupBuf[index][j]);
            }
        }
        len = Read_SEGNum_ChineseHintAreaLCDRAMBackupBuf();
    }
}

static void Fill_Char_In_ChineseHintArea( char* strbuf, signed char SplitScreen)
{
 
    unsigned short endseg;
    unsigned short len;
    const unsigned char* addresspoint;
    unsigned int size;

    ChineseHintArea_SplitScreenDisplay = 0; //Ĭ��Ϊ�޷���
    ChineseHintArea_RollDisplay = 0;        //ֹͣ������ʾ
    Clear_ChineseHintAreaGBKBuf();          //���
    Clear_ChineseHintAreaLCDRAMBackupBuf(); //���

    //����ȷ���Ƿ���ʾ��������ȷ��������ʾ��������ʾ�ķ�Χ
    //�жϷ����Ƿ���ʾ
    if(SplitScreen < 0)                    //����ʾ����
    {
        endseg = ChineseHintAreaEndSeg;
        ChineseHintArea_SplitScreenDisplay = 0;
    }
    else if(SplitScreen < 9)              //��ʾ����
    {
        #if (MeterType == ThreePhaseMeter)
        addresspoint = &SplitScreenIcon_13p12p[SplitScreen][0];
        size = Size_13P12P;
        #else
        addresspoint = &SplitScreenIcon_14p14p[SplitScreen][0];
        size = Size_14P14P;
        #endif
        InputCharacter_to_LCDRAM_Buf(SplitWindowAreaStartseg,SplitWindowAreaStartCom,addresspoint,size,display);
        endseg = SplitWindowAreaStartseg-1;       //��ʾ�����ˣ�������ʾ��������ʾ�ķ�Χ����С��
        ChineseHintArea_SplitScreenDisplay = 1; //��ʾ������־λ��1
    }

    StrToChineseHintAreaGBKBuf(strbuf);         //���ַ���ת��GBK�벢����ChineseHintAreaGBKBuf��
    ChineseHintAreaGBKBufToChineseBackupBuf();  //����GBK��Ѱ�ҵ��������ݲ�д��ChineseBackupBuf��
    len = Read_SEGNum_ChineseHintAreaLCDRAMBackupBuf();
    Copy_ChineseHintAreaGBKBuf_To_LCDRAM_Buf(endseg,0);  //����������ʾ��������ʾ�ķ�Χ��ChineseBackupBuf��ʼ��ַ���Ƶ�ChineseHintArea_LCDRAM

    if(len > (endseg-ChineseHintAreaStartSeg))          //Ҫ��ʾ������д����
    {
        strcat(strbuf," ");                            //ĩβ����1���ո���Ϊ����

        StrToChineseHintAreaGBKBuf(strbuf);             //���ַ���ת��GBK�벢����ChineseHintAreaGBKBuf��      
        ChineseHintAreaGBKBufToChineseBackupBuf();      //����GBK��Ѱ�ҵ��������ݲ�д��ChineseBackupBuf��
        len = Read_SEGNum_ChineseHintAreaLCDRAMBackupBuf();
        ChineseHintArea_RollDisplay = 1;                //���ù�����ʾ
    }
}

/** 
 * @brief  ������������д��������ʾ��
 * @note   
 * @param  phase: ��λ
 * @param  engerytype: ��������
 * @param  date: ʱ��
 * @param  rate: ����
 * @retval None
 */
static void Fill_Engery_In_ChineseHintArea(PHASE_TYPE phase,ENERGY_TYPE engerytype,unsigned char date,unsigned char rate)
{
    char strbuf[100] = "";
    char strbuf2[20] = "";
    int num;

    if((date>99)||rate>99)    //�·ݳ���99�£�С���㳬��4λ���߷��ʳ���99��֧�֣�����
    {
        return;
    }
    //ȷ��ʱ��
    if(date == 0)       //��ǰ
    {
        strcat(strbuf,"��ǰ");
    }
    else                //��x��
    {
        strcat(strbuf,"��");
        num  = (int)date;
        strcat(strbuf2,"��");
        sprintf(strbuf,"%s%d%s",strbuf,num,strbuf2);
    }

    //ȷ����λ
    switch(phase)
    {
        case TotalPhase:
            strcat(strbuf,"");
        break;
        case APhase:
            strcat(strbuf,"A��");
        break;
        case BPhase:
            strcat(strbuf,"B��");
        break;
        case CPhase:
            strcat(strbuf,"C��");
        break;
        default:
        break;
    }
    //ȷ����������
    switch(engerytype)
    {
        case CombinedActivePowerEnergy:
            #if (MeterType == ThreePhaseMeter)
            strcat(strbuf,"����й�");
            #else
            strcat(strbuf,"�й�");
            #endif
        break;
        case PositiveActivePowerEnergy:
            strcat(strbuf,"�����й�");
        break;
        case ReverseActivePowerEnergy:
            strcat(strbuf,"�����й�����");
        break;
        case CombinedOneReactivePowerEnergy:
            strcat(strbuf,"����޹�1");
        break;
        case CombinedTwoReactivePowerEnergy:
            strcat(strbuf,"����޹�2");
        break;
        case ReverseReactivePowerEnergy:
            strcat(strbuf,"�����޹�");
        break;
        case FirstQuadrantReactivePowerEnergy:
            strcat(strbuf,"��1�����޹�");
        break;
        case SecondQuadrantReactivePowerEnergy:
            strcat(strbuf,"��2�����޹�");
        break;
        case ThirdQuadrantReactivePowerEnergy:
            strcat(strbuf,"��3�����޹�");
        break;
        case FourthQuadrantReactivePowerEnergy:
            strcat(strbuf,"��4�����޹�");
        break;
        case PositiveApparentEnergy:
            strcat(strbuf,"��������");
        break;
        case ReverseApparentEnergy:
            strcat(strbuf,"��������");
        break;
        default:
            strcat(strbuf,"");
        break;
    }
    //ȷ������
    if(rate == 0)
    {
        strcat(strbuf,"��");
    }
    else
    {
        strcat(strbuf,"T");
        num = (int)rate;
        sprintf(strbuf,"%s%d",strbuf,num);
    }

    //���д��������
    strcat(strbuf,"����");
    //ˢ��LCD_RAM��backupbuf�ĵ�������
    Fill_Char_In_ChineseHintArea(strbuf,-1);
}




/*����ȫ�ֺ���----------------------------------------------------------------*/
/** 
 * @brief  ��ʾģ���ʼ������
 * @note   �򿪺�Ĭ����ʾ�ǿհ�
 * @retval None
 */
extern void Display_Init(void)
{
    ChineseHintArea_RollDisplay = 0;
    ChineseHintArea_SplitScreenDisplay = 0;
    LCD_Init();
}

/** 
 * @brief  ��ʾģ��ر�
 * @note   
 * @retval None
 */
extern void Diplay_Closed(void)
{
    Closed_LCD();
    ChineseHintArea_RollDisplay = 0;
    ChineseHintArea_SplitScreenDisplay = 0;
}
/** 
 * @brief  ������ʾ�����Ʋ��ֹ�����ʾ����
 * @note   �������Ҫ���ڶ�ʱ���У���ʱִ�У���������ʾ��������ʾ����ʱ�����Զ�����
 * @retval None
 */
extern void RollDiplay_ChineseHintArea(void)
{
    static short offset;
    unsigned short endseg;
    unsigned short len;
    
    if(ChineseHintArea_RollDisplay == 1)
    {
        len = Read_SEGNum_ChineseHintAreaLCDRAMBackupBuf();
        if(ChineseHintArea_SplitScreenDisplay == 1)     //���ڷ���
        {
            endseg = SplitWindowAreaStartseg-1;
        }
        else                                            //�����ڷ���
        {
            endseg = ChineseHintAreaEndSeg;
        }
        if(offset >= (len-1))
        {
            offset = offset;
        }
        Copy_ChineseHintAreaGBKBuf_To_LCDRAM_Buf(endseg,offset);  //����������ʾ��������ʾ�ķ�Χ��ChineseBackupBuf��ʼ��ַ���Ƶ�ChineseHintArea_LCDRAM
        
        offset++;
        
        if(offset >= len)
        {
            offset = 0;
        }
    }
    else
    {
        offset = 0;
    }

    Refresh_ChineseHintArea_of_LCD_DDRAM();
}

//����״̬����ָʾ����

#if (MeterType == ThreePhaseMeter)       //����ģʽ
/** 
 * @brief  ��ʾ������״̬
 * @note   
 * @param  number: 1����һ���ޣ�2���ڶ����ޣ�3���������ޣ�4����4���ޣ� ����ֵ�����������ʾ
 * @retval None
 */
extern void Display_QuadrantStatus(unsigned char number)
{
    if((number==0)||(number>4))
    {
        Clear_QuadrantArea_Of_LCDRAM_Buf();
        return;
    }
    Clear_QuadrantArea_Of_LCDRAM_Buf();
    InputCharacter_to_LCDRAM_Buf(QuadrantAreaStartSeg,QuadrantAreaStartPageCom,&QuadrantIcon_12p12p[number-1][0],Size_12P12P,display);
    Refresh_QuadrantArea_of_LCD_DDRAM();
}
#endif

/** 
 * @brief  ��ʾ���߲���ʾ��Կ״̬
 * @note   
 * @param  displayaction: �μ�DISPLAY_ACTION_TYPEö������
 * @retval None
 */
extern void Display_PublicKeyStatus(DISPLAY_ACTION_TYPE displayaction)
{
    if(displayaction == DisplayAction)
    {
        #if (MeterType == ThreePhaseMeter)       //����ģʽ
        InputCharacter_to_LCDRAM_Buf(StatusHintAreaStartSeg,StatusHintAreaStartCom,&StatusHint_char_7p11p[0][0],Size_7P11P,display);
        Refresh_PartArea_of_LCD_DDRAM(StatusHintAreaStartSeg,(StatusHintAreaStartCom/8),(StatusHintAreaStartSeg+Size_7P11P/100),((StatusHintAreaStartCom+Size_7P11P%100)/8+1));
        #else
        InputCharacter_to_LCDRAM_Buf(StatusHintAreaStartSeg,StatusHintAreaStartCom,&StatusHint_char_10p11p[1][0],Size_10P11P,display);
        Refresh_PartArea_of_LCD_DDRAM(StatusHintAreaStartSeg,(StatusHintAreaStartCom/8),(StatusHintAreaStartSeg+Size_10P11P/100),((StatusHintAreaStartCom+Size_10P11P%100)/8+1));
        #endif
    }
    else
    {
        #if (MeterType == ThreePhaseMeter)       //����ģʽ
        Clear_PartArea_of_LCDRAM_Buf(StatusHintAreaStartSeg,StatusHintAreaStartCom,(StatusHintAreaStartSeg+Size_7P11P/100),(StatusHintAreaStartCom+Size_7P11P%100));
        Refresh_PartArea_of_LCD_DDRAM(StatusHintAreaStartSeg,(StatusHintAreaStartCom/8),(StatusHintAreaStartSeg+Size_7P11P/100),((StatusHintAreaStartCom+Size_7P11P%100)/8+1));
        #else
        Clear_PartArea_of_LCDRAM_Buf(StatusHintAreaStartSeg,StatusHintAreaStartCom,(StatusHintAreaStartSeg+Size_10P11P/100),(StatusHintAreaStartCom+Size_10P11P%100));
        Refresh_PartArea_of_LCD_DDRAM(StatusHintAreaStartSeg,(StatusHintAreaStartCom/8),(StatusHintAreaStartSeg+Size_10P11P/100),((StatusHintAreaStartCom+Size_10P11P%100)/8+1));
        #endif        
    }  
}

/** 
 * @brief  ��ʾ���߲���ʾ������֤״̬
 * @note   
 * @param  displayaction: �μ�DISPLAY_ACTION_TYPEö������
 * @retval None
 */
extern void Display_InfraredAuthenticationStatus(DISPLAY_ACTION_TYPE displayaction)
{
    if(displayaction == DisplayAction)
    {
        #if (MeterType == ThreePhaseMeter)       //����ģʽ
        InputCharacter_to_LCDRAM_Buf((StatusHintAreaStartSeg+7),StatusHintAreaStartCom,&StatusHint_char_9p11p[0][0],Size_9P11P,display);
        Refresh_PartArea_of_LCD_DDRAM((StatusHintAreaStartSeg+7),(StatusHintAreaStartCom/8),((StatusHintAreaStartSeg+7)+Size_9P11P/100),((StatusHintAreaStartCom+Size_9P11P%100)/8+1));
        #else
        InputCharacter_to_LCDRAM_Buf((StatusHintAreaStartSeg+10),StatusHintAreaStartCom,&StatusHint_char_13p11p[0][0],Size_13P11P,display);
        Refresh_PartArea_of_LCD_DDRAM((StatusHintAreaStartSeg+10),(StatusHintAreaStartCom/8),((StatusHintAreaStartSeg+10)+Size_13P11P/100),((StatusHintAreaStartCom+Size_13P11P%100)/8+1));
        #endif
    }
    else
    {
        #if (MeterType == ThreePhaseMeter)       //����ģʽ
        Clear_PartArea_of_LCDRAM_Buf((StatusHintAreaStartSeg+7),StatusHintAreaStartCom,((StatusHintAreaStartSeg+7)+Size_9P11P/100),(StatusHintAreaStartCom+Size_9P11P%100));
        Refresh_PartArea_of_LCD_DDRAM((StatusHintAreaStartSeg+7),(StatusHintAreaStartCom/8),((StatusHintAreaStartSeg+7)+Size_9P11P/100),((StatusHintAreaStartCom+Size_9P11P%100)/8+1));
        #else
        Clear_PartArea_of_LCDRAM_Buf((StatusHintAreaStartSeg+10),StatusHintAreaStartCom,((StatusHintAreaStartSeg+10)+Size_13P11P/100),(StatusHintAreaStartCom+Size_13P11P%100));
        Refresh_PartArea_of_LCD_DDRAM((StatusHintAreaStartSeg+10),(StatusHintAreaStartCom/8),((StatusHintAreaStartSeg+10)+Size_13P11P/100),((StatusHintAreaStartCom+Size_13P11P%100)/8+1));
        #endif        
    } 
}

/** 
 * @brief  ��ʾ���߲���ʾ���ܱ����״̬
 * @note   
 * @param  displayaction: �μ�DISPLAY_ACTION_TYPEö������
 * @retval None
 */
extern void Display_SuspendedStatus(DISPLAY_ACTION_TYPE displayaction)
{
    if(displayaction == DisplayAction)
    {
        #if (MeterType == ThreePhaseMeter)       //����ģʽ
        InputCharacter_to_LCDRAM_Buf((StatusHintAreaStartSeg+7+9),StatusHintAreaStartCom,&StatusHint_char_6p11p[0][0],Size_6P11P,display);
        Refresh_PartArea_of_LCD_DDRAM((StatusHintAreaStartSeg+7+9),(StatusHintAreaStartCom/8),((StatusHintAreaStartSeg+7+9)+Size_6P11P/100),((StatusHintAreaStartCom+Size_6P11P%100)/8+1));
        #else
        InputCharacter_to_LCDRAM_Buf((StatusHintAreaStartSeg+10+13),StatusHintAreaStartCom,&StatusHint_char_7p11p[0][0],Size_7P11P,display);
        Refresh_PartArea_of_LCD_DDRAM((StatusHintAreaStartSeg+10+13),(StatusHintAreaStartCom/8),((StatusHintAreaStartSeg+10+13)+Size_7P11P/100),((StatusHintAreaStartCom+Size_7P11P%100)/8+1));
        #endif
    }
    else
    {
        #if (MeterType == ThreePhaseMeter)       //����ģʽ
        Clear_PartArea_of_LCDRAM_Buf((StatusHintAreaStartSeg+7+9),StatusHintAreaStartCom,((StatusHintAreaStartSeg+7+9)+Size_6P11P/100),(StatusHintAreaStartCom+Size_6P11P%100));
        Refresh_PartArea_of_LCD_DDRAM((StatusHintAreaStartSeg+7+9),(StatusHintAreaStartCom/8),((StatusHintAreaStartSeg+7+9)+Size_6P11P/100),((StatusHintAreaStartCom+Size_6P11P%100)/8+1));
        #else
        Clear_PartArea_of_LCDRAM_Buf((StatusHintAreaStartSeg+10+13),StatusHintAreaStartCom,((StatusHintAreaStartSeg+10+13)+Size_7P11P/100),(StatusHintAreaStartCom+Size_7P11P%100));
        Refresh_PartArea_of_LCD_DDRAM((StatusHintAreaStartSeg+10+13),(StatusHintAreaStartCom/8),((StatusHintAreaStartSeg+10+13)+Size_7P11P/100),((StatusHintAreaStartCom+Size_7P11P%100)/8+1));
        #endif        
    } 
}

//����Ŀ������ʾ����
/** 
 * @brief  ��ʾ��������
 * @note  
 * @param  phase: ������λ ����μ�PHASE_TYPEö�� 
 * @param  engerytype: �������࣬����μ�ENERGY_TYPEö��
 * @param  date:    ���ڣ���ʱ֧��0~99��0��ʾ��ǰ  ����������x��
 * @param  rate:    ���� 0~99������0�����ܣ���������Tx
 * @param  engerypoint: ָ������洢�����飬Ĭ��6�ֽ�BCD�룬����ֽڴ����3,4С��
 * @param  decimalpoint: ������ʾ�ĵ�����ʾ��λС����0~4
 * @param  plusminus: �����Ƿ���ʾ���ţ�    plus������ʾ��minus������ʾ
 * @param  displayhighzero: ��λ�Ƿ����㣬����μ�HIGHZERO_TYPEö��
 * @retval None
 */
extern void Display_Engery(PHASE_TYPE phase,ENERGY_TYPE engerytype,unsigned char date,unsigned char rate,unsigned char* engerypoint,unsigned char decimalpoint,PLUS_MINUS plusminus,HIGHZERO_TYPE displayhighzero)
{
    if((date>99)||(decimalpoint>4)||rate>99)    //�·ݳ���99�£�С���㳬��4λ���߷��ʳ���99��֧�֣�����
    {
        return;
    }

    Fill_Engery_In_ChineseHintArea(phase,engerytype,date,rate);



    if((engerytype == CombinedActivePowerEnergy)||(engerytype == PositiveActivePowerEnergy)||(engerytype == ReverseActivePowerEnergy))     //�й���
    {
        //���Kwh����λ��
      //  Fill_Kwh_In_UnitArea();
    }
    else
    {
        //���kvah����λ��
      //  Fill_kvah_In_UnitArea();        
    }


    Refresh_ChineseHintArea_of_LCD_DDRAM();         //ˢ�µ�LCD��������ʾ��
}











/*end-------------------------------------------------------------------------*/
