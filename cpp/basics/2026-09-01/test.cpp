//////////////#include <iostream>
//////////////using namespace std;
//////////////int main()
//////////////{
//////////////	int a = 190;
//////////////	cout << "流畅\n" << 111 << a<<"\n";
//////////////	float b = 7877773.27777775;
//////////////	cout << "\nfloat = " << b;
//////////////	return 0;
//////////////}
////////////#include <iostream>
////////////using namespace std;
////////////
////////////int main()
////////////{
////////////	cout << "aaaaa\t"<<"b\n";
////////////	cout << "aa\t"<<"b\n";
////////////	cout << "aaaaa\t"<<"b\n";
////////////	cout << "\\\n";
////////////	cout << "\n";
////////////
////////////	return 0;
////////////}
//////////#include <iostream>
//////////using namespace std;
//////////#include <string.h>
//////////int main()
//////////{
//////////	string name = "流畅按时打卡哈萨克的";
//////////	cin >> name;
//////////	if (name == "mike")
//////////	{
//////////		cout << "yes";
//////////
//////////	}
//////////	else
//////////		cout << "no";
//////////	return 0;
//////////
////////// }
////////#include <iostream>
////////using namespace std;
////////#include <ctime>
////////int main()
////////{
////////	srand((unsigned int)time(NULL));
////////	int num = rand() % 100 + 1;
////////	int cai = 0;
////////	while (num != cai)
////////	{
////////		cout << "猜数字\n";
////////		cin >> cai;
////////		if (cai == num)
////////			cout << "猜对了\n";
////////		else if (cai < num)
////////			cout << "猜小了\n";
////////		else
////////			cout << "猜大了\n";
////////	}
////////	return 0;
////////}
//////#include <iostream>
//////using namespace std;
//////int main()
//////{
//////	int num = 0;
//////	do
//////	{
//////		if(num)
//////	} while ();
//////	{
//////
//////	}
//////	return 0;
//////}
////#include <iostream>
////using namespace std;
////int main()
////{
////	for (int i = 9; i > 0; i--)
////	{
////		for (int j = 9; j < i; j--)
////		{
////			cout<<"\t" << j << "*" << i << "=" << j * i;
////		}
////	}
////	return 0;
////}
////
//#include <iostream>
//using namespace std;
//int main()
//{
//    // i 行，1~9
//    for (int i = 1; i <= 9; i++)
//    {
//        // 先打印空格占位，实现靠右
//        for (int k = 1; k < i; k++)
//        {
//            cout << "\t";
//        }
//        // 输出算式
//        for (int j = i; j <= 9; j++)
//        {
//            cout << i << "*" << j << "=" << i * j << "\t";
//        }
//        cout << endl;
//    }
//    return 0;
////}
#include <iostream>
using namespace std;
int main()
{
	cout << "这本书怎么样\n";
	int coment = 0;
	cin >> coment;
	switch (coment)
	{
	case 1:
		cout << "very good\n";
		cout << "1111";
		break;
	case 2:
		cout << "good";
		break;
	case 3:
		cout << "laji";
		break;
	default :
		cout << "please choose right ";
		break;
	}
	return 0;
}