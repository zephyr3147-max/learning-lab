//#include <iostream>
//using namespace std;
//#include <string>
//
//struct student
//{
//	string name;
//	int score;
//};
//
//struct teacher
//{
//	string teacher_name;
//	struct student arr_stu[5];
//};
//
//void Cin_my(struct teacher arrt[], int len)
//{
//	for (int i = 0; i < 3; i++)
//	{
//		cout << "请输入第"<<i + 1<<"个老师的名字"<<"\n";
//		cin >> arrt[i].teacher_name;
//		for (int j = 0; j < 5; j++)
//		{
//			cout << "请输入第" << j + 1<< "个学生的名字"<<"\n";
//			cin >> arrt[i].arr_stu[j].name;
//			cout << "请输入第" << j + 1<< "个学生的分数"<<"\n";
//			cin >> arrt[i].arr_stu[j].score;
//		}
//	}
//}
// 
//void Print(struct teacher* arrt, int len)
//{
//	for (int i = 0; i < 3; i++)
//	{
//		cout << arrt[i].teacher_name<<"\n";
//		for (int j = 0; j < 5; j++)
//		{
//			cout << arrt[i].arr_stu[j].name<<" ";
//			cout << arrt[i].arr_stu[j].score<<"\n";
//		}
//	}
//}
//
//int main()
//{
//	struct teacher arr_tea[3];
//	Cin_my(arr_tea,3);
//	Print(arr_tea, 3);
//	return 0;
//}
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;
#define num 5

struct hero 
{
	string name;
	int age;
	string sex;
};

void Cin_my(struct hero *arr,int len)
{
	for (int i = 0; i < len; i++)
	{
		cin >> arr[i].name;
		arr[i].age = rand()%100;
		cin >> arr[i].sex;
	}
}

void Bubble_sort(struct hero* arr, int len)
{
	
	for (int i = 0; i < len-1; i++)
	{
		int temp1 = 0;
		string temp2;
		string temp3;
		for (int j = 0; j < len - 1 - i; j++)
		{
			
			if (arr[j].age > arr[j + 1].age)
			{
				temp1 = arr[j].age;
				arr[j].age = arr[j + 1].age;
				arr[j + 1].age = temp1;

				temp2 = arr[j].sex;
				arr[j].sex = arr[j + 1].sex;
				arr[j + 1].sex = temp2;

				temp3 = arr[j].name;
				arr[j].name = arr[j + 1].name;
				arr[j + 1].name = temp3;
			}
		}
	}
}

void Print (struct hero* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i].name<<" ";
		cout << arr[i].age <<" ";
		cout << arr[i].sex <<"\n";
	}
}

int main()
{
	srand((unsigned int)time(NULL));
	struct hero arr[num];
	Cin_my(arr, num);
	Bubble_sort(arr, num);
	Print(arr, num);

	return 0;
}