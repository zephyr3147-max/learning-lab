#include <REGX52.H>

unsigned char table[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void Delay(x)	//@12.000MHz
{
	unsigned char data i, j;

	while(x--)
	{
		i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
	}	
}

void Digital(unsigned char led,unsigned char number)
{
	switch(led)
	{
		case 1:P2_4 = 1;P2_3 = 1;P2_2 = 1;break;
		case 2:P2_4 = 1;P2_3 = 1;P2_2 = 0;break;
		case 3:P2_4 = 1;P2_3 = 0;P2_2 = 1;break;
		case 4:P2_4 = 1;P2_3 = 0;P2_2 = 0;break;
		case 5:P2_4 = 0;P2_3 = 1;P2_2 = 1;break;
		case 6:P2_4 = 0;P2_3 = 1;P2_2 = 0;break;
		case 7:P2_4 = 0;P2_3 = 0;P2_2 = 1;break;
		case 8:P2_4 = 0;P2_3 = 0;P2_2 = 0;break;
	}
	
	P0 = table[number];
	Delay(500);
	P0 = 0x00;
}
void main()
{
	
	while(1)
	{
		Digital(1,1);
		Digital(2,2);
		Digital(4,4);
		Digital(5,5);
		Digital(6,6);
		Digital(7,7);
		Digital(8,8);
	}
}