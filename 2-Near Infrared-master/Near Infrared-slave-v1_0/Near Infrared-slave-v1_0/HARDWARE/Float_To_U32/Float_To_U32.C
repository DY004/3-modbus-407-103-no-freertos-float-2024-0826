#include "Float_To_U32.h"
#include "gpio.h"
//#include "key.h"
#include "delay.h"
#include "sys.h"
#include "modbus.h"
/*此处有用到保持寄存器的数组usSRegHoldBuf，这个我项目由于要多次使用到，我已经把
这个保持寄存器定义为了全局变量*/
uint16_t  usSRegHoldBuf[S_REG_HOLDING_NREGS] ;//保持寄存器
/*浮点数与IEEE754格式转换*/
typedef union                                        
{
   float ul_Temp;
   u8  uc_Buf[4];//小数转换成IEEE754格式的数组
   u16 us_Buf[2];//用于modbus协议小数转换的数组
}un_DtformConver; 
//此方式和1.0其实差不多，不过这个方式可以运用到的别的小数转换成IEEE754的场合
/* 定义保存和差积商的结构体 */
//struct my_retrun {
//    float sum;
//    float defference;
//    int product;
//    int quotient;
//};

//struct my_retrun ret;    // 保存结果

float  ABC[2] ;//保持寄存器


float DataConvertFloat(u16 HoldAddr)
{
	//方式零-验证有问题，会掉精度
//	 un_DtformConver  Data;
//	 float temp;
//	 Data.uc_Buf[1] = (u8 )(modbus.rcbuf[HoldAddr]&0xff);//得到保持寄存器HoldAddr的低8位
//	 Data.uc_Buf[0] = (u8 )(modbus.rcbuf[HoldAddr]>>8);//得到保持寄存器HoldAddr的高8位
//	 Data.uc_Buf[3] = (u8 )(modbus.rcbuf[HoldAddr+2]&0xff);//保持寄存器(HoldAddr+1)的低8位
//	 Data.uc_Buf[2]= (u8 )(modbus.rcbuf[HoldAddr+2]>>8);//保持寄存器(HoldAddr+1)的高8位
//	 temp = Data.ul_Temp;//得到小数
	//方式零-验证有问题，会掉精度

	
	//	 适配成适合自己的代码
	//方式一-验证没有问题-OK
//	 un_DtformConver  Data,you[100];
//	 float temp;
//	 you[0].uc_Buf[3] = (u8)(modbus.rcbuf[HoldAddr+2]);//保持寄存器(HoldAddr+1)的高8位
//	 you[0].uc_Buf[2] = (u8)(modbus.rcbuf[HoldAddr+3]);//保持寄存器(HoldAddr+1)的低8位
//	 you[0].uc_Buf[1] = (u8)(modbus.rcbuf[HoldAddr]);//得到保持寄存器HoldAddr的高8位
//	 you[0].uc_Buf[0]= (u8)(modbus.rcbuf[HoldAddr+1]);//得到保持寄存器HoldAddr的低8位
//	 temp = you[0].ul_Temp;//得到小数	
	//方式一-验证没有问题-OK
	
	
	//方式五-验证浮点数锯传输-多个浮点数读取，也是没有问题的
	
	
	
	 un_DtformConver  Data,you[100];
	 float temp,temp2;
	 //第一个数据转换
	 you[0].uc_Buf[3] = (u8)(modbus.rcbuf[HoldAddr+2]);//保持寄存器(HoldAddr+1)的高8位
	 you[0].uc_Buf[2] = (u8)(modbus.rcbuf[HoldAddr+3]);//保持寄存器(HoldAddr+1)的低8位
	 you[0].uc_Buf[1] = (u8)(modbus.rcbuf[HoldAddr]);//得到保持寄存器HoldAddr的高8位
	 you[0].uc_Buf[0]= (u8)(modbus.rcbuf[HoldAddr+1]);//得到保持寄存器HoldAddr的低8位
	 temp = you[0].ul_Temp;//得到小数
	 
	 //第二个数据转换
	 
	 you[1].uc_Buf[3] = (u8)(modbus.rcbuf[HoldAddr+6]);//保持寄存器(HoldAddr+1)的高8位
	 you[1].uc_Buf[2] = (u8)(modbus.rcbuf[HoldAddr+7]);//保持寄存器(HoldAddr+1)的低8位
	 you[1].uc_Buf[1] = (u8)(modbus.rcbuf[HoldAddr+4]);//得到保持寄存器HoldAddr的高8位
	 you[1].uc_Buf[0]= (u8)(modbus.rcbuf[HoldAddr+5]);//得到保持寄存器HoldAddr的低8位
	
	 temp2 = you[1].ul_Temp;//得到小数
	 
	 
	 printf("temp= %.2f ,temp2= %.2f\r\n",temp,temp2);
	
	
	//方式五-验证浮点数锯传输-多个浮点数读取，也是没有问题的
	
	
	
	
	
	
	
//	you.uc_Buf[0] = Data.uc_Buf[0];
//	you.uc_Buf[1] = Data.uc_Buf[1];
//	you.uc_Buf[2] = Data.uc_Buf[2];
//	you.uc_Buf[3] = Data.uc_Buf[3];
//	printf("you.ul_Temp= %.2f \r\n",Data.ul_Temp);


	//方式二-验证没有问题-OK
//	*((char*)(&temp))=Data.uc_Buf[3];
//	*((char*)(&temp)+1)=Data.uc_Buf[2];
//	*((char*)(&temp)+2)=Data.uc_Buf[1];
//	*((char*)(&temp)+3)=Data.uc_Buf[0];
//	printf("temp= %.2f \r\n",temp);
	//方式二
	
	//方式三-验证没有问题-OK
//	*((char*)(&temp))=(char)modbus.rcbuf[HoldAddr+1];
//	*((char*)(&temp)+1)=(char)modbus.rcbuf[HoldAddr];
//	*((char*)(&temp)+2)=(char)modbus.rcbuf[HoldAddr+3];
//	*((char*)(&temp)+3)=(char)modbus.rcbuf[HoldAddr+2];
//	printf("temp= %.2f \r\n",temp);
	//方式三


	
//	printf("Data.uc_Buf[0]= %X \r\n",Data.uc_Buf[0]);
//	printf("Data.uc_Buf[1]= %X \r\n",Data.uc_Buf[1]);
//	printf("Data.uc_Buf[2]= %X \r\n",Data.uc_Buf[2]);
//	printf("Data.uc_Buf[3]= %X \r\n",Data.uc_Buf[3]);
    return 0;


	
}


	
	
	






