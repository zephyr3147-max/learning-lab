#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int n;
	int k;
	scanf("%d %d",&n,&k);

	int* values = (int*)malloc(n * sizeof(int));
	int* queue = (int*)malloc(n * sizeof(int));
	if(values == NULL || queue == NULL)
	{
		return 0;
	}

	for(int i = 0; i < n; ++i)
	{
		scanf("%d",&values[i]);
	}

	int head = 0;
	int tail = 0;
	for(int i = 0; i < n; ++i)
	{
		while(head < tail && queue[head] <= values[i])
		{
			++head;
		}

		while(head < tail && values[queue[tail -1]] <= values[i])
		{
			--tail;
		}


	}

}

