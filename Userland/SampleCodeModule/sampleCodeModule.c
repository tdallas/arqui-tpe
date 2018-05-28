#include <stdio.h>
#include <constantPrints.h>
#include <stdlib.h>

int main()
{
	char c;
	printf("Epoch Time: %d.\n", time(NULL));
	printTime();
	printDate();
	printTimeUTC();
	int num[1];
	while (1)
	{
		if (scanf("num=%d", num) > 0)
		{
			printf(", el num es:%d.\n", num[0]);
		}
		else
		{
			putchar('\n');
		}
	}
	while (1)
	{
		if ((c = getchar()) != EOF)
		{
			putchar(c);
		}
	}

	return 0;
}