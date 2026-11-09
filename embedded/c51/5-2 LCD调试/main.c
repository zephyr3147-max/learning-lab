#include <REGX52.H>
#include "LCD1602.h"

void main()
{
	LCD_Init();
	LCD_ShowChar(1,1,'A');            //第1行第1列显示字符A
	LCD_ShowString(1,3,"Hello");      //第1行第3列开始显示字符串
	LCD_ShowNum(1,9,123,3);           //第1行第9列开始显示3位无符号数
	LCD_ShowSignedNum(1,13,-66,2);    //第1行第13列开始显示有符号数（含负号）
	LCD_ShowHexNum(2,1,0xA8,2);       //第2行第1列开始显示2位十六进制
	LCD_ShowBinNum(2,4,0xAA,8);       //第2行第4列开始显示8位二进制
	while(1)
	{

	}
}
