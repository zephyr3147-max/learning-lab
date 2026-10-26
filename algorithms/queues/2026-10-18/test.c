//
//#include <stdio.h>
//
//int ElemRemove(int* num, int size, int val)
//{
//	int src = 0;
//	int dst = 0;
//	
//	while(src < size)
//	{
//		if (num[src] != val)
//		{
//			num[dst] = num[src];
//			src++;
//			dst++;
//		}
//		else
//		{
//			src++;
//		}
//	}
//
//	return dst;
//}
//
//int main()
//{
//	int val = 2;
//	int num[6] = { 1,2,3,4,5,6 };
//	int i = ElemRemove(num, 6, val);
//	for (int i = 0; i < 5; i++)
//	{
//		printf("%d", num[i]);
//	}
//}