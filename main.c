//**********通过74HC595芯片串转并，输送相应字节到点阵，从而控制点阵显示汉字**************//
#include <reg51.h>
#include <intrins.h>
typedef unsigned char u8;
typedef unsigned int u16;

sbit SRCLK=P3^6;		//移位寄存器时钟
sbit RCLK=P3^5;		//储存器时钟
sbit SER=P3^4;		//串行数据输入

u8 ledwei[]=       //位选，后面会取反，使能(让段码输入进来)
{
	0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80
};

u8 code ledduan[]=     //段选，存放相应的段码
{
	/*--  心形图像  --*/
/*--  宽度x高度=16x16  --*/
0xC0,0xE0,0xF0,0xF8,0xF8,0xF0,0xE0,0xC0,0xE0,0xF0,0xF8,0xF8,0xF0,0xE0,0xC0,0x00,
0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,
};
void delay(u16 i)
{
	while(i--);
}
void hc595sendbyte(u8 dat1,u8 dat2,u8 dat3,u8 dat4)  //发送4个字节数据
{
	u8 i;
	for(i=0;i<8;i++)
	{
		SER=dat1>>7;  //接收的数据，高位移到最低位，以位输送后还是要其最高位
		dat1<<=1;  //次位变最高位
		SRCLK=0;  //使移位寄存器时钟出现上升沿
		_nop_();
		_nop_();
		SRCLK=1;
	}
	
	for(i=0;i<8;i++)
	{
		SER=dat2>>7;  //接收的数据，高位移到最低位，以位输送后还是要其最高位
		dat2<<=1;  //次位变最高位
		SRCLK=0;  //使移位寄存器时钟出现上升沿
		_nop_();
		_nop_();
		SRCLK=1;
	}
	
	for(i=0;i<8;i++)
	{
		SER=dat3>>7;  //接收的数据，高位移到最低位，以位输送后还是要其最高位
		dat3<<=1;  //次位变最高位
		SRCLK=0;  //使移位寄存器时钟出现上升沿
		_nop_();
		_nop_();
		SRCLK=1;
	}
	
	for(i=0;i<8;i++)
	{
		SER=dat4>>7;  //接收的数据，高位移到最低位，以位输送后还是要其最高位
		dat4<<=1;  //次位变最高位
		SRCLK=0;  //使移位寄存器时钟出现上升沿
		_nop_();
		_nop_();
		SRCLK=1;
	}
	
	RCLK=0;  //字节移向储存器，由上升沿触发
	_nop_();
	_nop_();
	RCLK=1;
}
void main ()
{
	u8 a;
	
	while (1)
	{	
		for(a=0;a<16;a++)    //一个循环16次，因有16位码，且采用循环逐段扫描，先是上面两个，后下面两个 
		{
			hc595sendbyte(~ledwei[a+16],~ledwei[a],ledduan[16+a],ledduan[a]);   //先使能，再送段码
			delay(10);
		}
		}
	
}