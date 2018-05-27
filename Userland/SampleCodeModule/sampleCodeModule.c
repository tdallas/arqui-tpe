#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	char c;
	printf("Epoch Time: %d. ", time(NULL));
	printTime();
	putchar('\n');
	int num[1];
	while(1){
		scanf("%d", num);
		printf(", el num es:%d", num[0]);
		putchar('\n');
	}
	while(1){
		if ((c = getchar()) != EOF)
		{
			putchar(c);
		}
	}

	return 0;
}