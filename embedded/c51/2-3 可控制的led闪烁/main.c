#include <REGX52.H>

void Delay1ms(unsigned int xms)	//@12.000MHz
{
		while(xms)
		{
				unsigned char data i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
	xms--;
		}
}

void main()
{
		P2 = 0xFE;
		Delay1ms(500);
		P2 = 0xFD;
		Delay1ms(500);
		P2 = 0xFB;
		Delay1ms(500);
		P2 = 0xF7;
		Delay1ms(500);
		P2 = 0xEF;
		Delay1ms(500);
		P2 = 0xDF;
		Delay1ms(500);
		P2 = 0xBF;
		Delay1ms(500);
		P2 = 0x7F;
		Delay1ms(500);
}