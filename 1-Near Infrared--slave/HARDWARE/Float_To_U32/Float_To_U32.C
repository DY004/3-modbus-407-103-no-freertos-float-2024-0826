#include "Float_To_U32.h"
#include "gpio.h"
#include "key.h"
#include "delay.h"
#include "sys.h"
#include "string.h"
#include "stdio.h"

/*此处有用到保持寄存器的数组usSRegHoldBuf，这个我项目由于要多次使用到，我已经把
这个保持寄存器定义为了全局变量*/
u16 usSRegHoldBuf[S_REG_HOLDING_NREGS] ;//保持寄存器 

/*浮点数与IEEE754格式转换*/
typedef union                                        
{
   float ul_Temp;
   u8  uc_Buf[4];//小数转换成IEEE754格式的数组
   u16 us_Buf[2];//用于modbus协议小数转换的数组
}un_DtformConver; 


union float_data
{
    float f_data;
    uint8_t byte[4];
};

//此方式和1.0其实差不多，不过这个方式可以运用到的别的小数转换成IEEE754的场合
void Float_To_U32(float value,float value2, uint16_t Holdaddr)
{
	//方式一，传输单个数据，没有问题-OK
//	un_DtformConver Data,you[100];
//	Data.ul_Temp = value;//获取小数值
//	usSRegHoldBuf[Holdaddr] = Data.us_Buf[0];//获取低16位
//	usSRegHoldBuf[Holdaddr+1] = Data.us_Buf[1];//获取高16位
//	printf("%X\r\n",usSRegHoldBuf[0]);
//	printf("%X\r\n",usSRegHoldBuf[1]);
	//方式一，传输单个数据，没有问题-OK
	
	//方式二，传输多个浮点数据
	un_DtformConver Data,you[100];
	you[0].ul_Temp = value;//获取第一个需要传输的浮点数
	you[1].ul_Temp = value2;//获取第二个需要传输的浮点数
	
	usSRegHoldBuf[Holdaddr] = you[0].us_Buf[0];//第一个浮点数获取低16位，要要传输的值，通过联合体，赋值到
	usSRegHoldBuf[Holdaddr+1] = you[0].us_Buf[1];//第一个浮点数获取高16位
	
	usSRegHoldBuf[Holdaddr+2] = you[1].us_Buf[0];//第二个浮点数，获取低16位，要要传输的值，通过联合体，赋值到
	usSRegHoldBuf[Holdaddr+3] = you[1].us_Buf[1];//第二个浮点数，获取高16位
	
	
	printf("%X\r\n",usSRegHoldBuf[0]);
	printf("%X\r\n",usSRegHoldBuf[1]);
	printf("%X\r\n",usSRegHoldBuf[2]);
	printf("%X\r\n",usSRegHoldBuf[3]);
	
	



}


	
	
	






