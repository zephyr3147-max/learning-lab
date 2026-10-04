#include "SList.h"
#include <stdio.h>

static void PrintSep(const char* title)
{
	printf("\n===== %s ====\n", title);
}

int main(void)
{
	PrintSep("用例1：新建空表");
	LinkList L = SListInit();
	if (L == NULL)
	{
		printf("初始化失败\n");
		return 1;
	}
	printf("表长 = %d （应为0）\n", SListLength(L));
	printf("空表打印：");



	PrintSep("用例2：尾插1~5");
	Node* tail = L;
	for (int i = 1; i <= 5; i++)
	{
		int j = 0;
		scanf_s("%d", &j);
		SListPushBack(&tail,j);
	}
	printf("链表:");
	SListPrint(L);
	printf("表长 = %d （应为 5）  \n", SListLength(L));


	PrintSep("用例3：按位查找");
	ElemType x = -1;
	if (SListGetElem(L, 3, &x))
	{
		printf("第3个 = %d（应为3） \n", x);
	}
	if (!SListGetElem(L, 99, &x))
	{
		printf("第99个：越界，返回失败 \n");
	}


	PrintSep("用例4：按位删除");
	printf("删1（删首）: %s\n", SListDelValue(L, 1) ? "成功" : "失败");
	printf("删5（删尾）: %s\n", SListDelValue(L, 5) ? "成功" : "失败");
	printf("删99（不存在）: %s\n", SListDelValue(L, 99) ? "成功" : "失败");
	printf("链表：");
	SListPrint(L);

	PrintSep("用例5");
	ElemType a[] = { 10,20,30 };
	int len = 0;
	LinkList L2 = SListCreateFromArray(a, 3, &len);
	printf("链表:");
	SListPrint(L2);
	printf("表长 = %d （应为3）\n", len);

	PrintSep("用例 6");
	SListDestroy(&L);
	SListDestroy(&L2);
	printf("%s\n", L == NULL ? "yes" : "no");
	
	return 0;
}