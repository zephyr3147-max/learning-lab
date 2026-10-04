////寻找缺失的数字
//#include <iostream>
//using namespace std;
//
//
//int missingNumber(const int* num, int numssize)
//{
//	int x = 0;
//	for (int i = 0; i < numssize; ++i)
//	{
//		x ^= *(num + i);    
//	}
//
//	for (int j = 0; j < numssize + 1; ++j)
//	{
//		x ^= j;
//	}
//
//	return x;
//}
//
//int  main()
//{
//	const int arr[10] = { 0,1,2,3,4,5,6,8,9,10 };
//	int ms = missingNumber(arr, 10);
//	cout << ms << "\n";
//	return 0;
//}

//向右旋转数组
// 
//#include <iostream>
//using namespace std;
//
//void Reverse(int* nums, int left, int right)
//{
//	while (right > left)
//	{
//		int temp;
//		temp = nums[left];
//		nums[left] = nums[right];
//		nums[right] = temp;
//		left++;
//		right--;
//	}
//}
//
//void rotate(int* num, int numssize, int k)
//{
//	if (k >= numssize)
//	{
//		k = k % numssize;//k是后k个元素
//	}
//	Reverse(num, numssize - k, numssize - 1);
//	Reverse(num, 0, numssize - k - 1);
//	Reverse(num, 0, numssize - 1);
//}
//int main()
//{
//	int arr[7] = { 1,2,3,4,5,6,7 };
//	rotate(arr, 7, 7);
//	for (int i = 0; i < 7; i++)
//	{
//		cout << arr[i];
//	}
//	return 0;
//}

//#include <iostream>
//using namespace std;
//
//int removeElement(int* num,int val,int numsSize)
//{
//	int slow = 0;
//	for (int fast = 0; fast < numsSize; fast++)
//	{
//		if (num[fast] != val)
//		{
//			num[slow] = num[fast];
//			slow++;
//		}
//	}
//	return slow;
//}
//
//int main()
//{
//	int arr[10] = { 1,2,3,4,2,2,2,5,8,9};
//	int x = removeElement(arr, 2, 10);
//
//	cout << x;
//	return 0;
//}

