////#include <iostream>
////using namespace std;
////
////int Add(int num1, int num2);
////
////int main()
////{
////	int a = 0;
////	const int* p = &a;
////
////	int b = 1;
////	int* const g = &b;
////
////	int c = Add(a, b);
////	cout << c;
////	return 0;
////}
////
////int Add(int num1, int num2) 
////{
////	return num1 + num2;
////}
////
//#include <iostream>
//using namespace std;
//
//int main()
//{
//	int arr[3] = { 1,2,3 };
//	int* p = arr;
//	for (int i = 0; i < 3; i++)
//	{
//		cout << *p;
//		p++;
//	}
//
//	return 0;
//}
#include <iostream>
using namespace std;
void Bubblesort(int* arr, int len);
void Print(int* arr, int len);

int main()
{
	int arr[10] = { 1,3,2,5,6,8,9,0,4,7 };
	Bubblesort(arr, sizeof(arr) / sizeof(int));
	Print(arr, sizeof(arr) / sizeof(int));
}

void Bubblesort(int* arr, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			int temp = 0;
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void Print(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i];
	}
}