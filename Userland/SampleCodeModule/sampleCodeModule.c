#include <stdio.h>
#include <constantPrints.h>
#include <stdlib.h>
#include <blobsFront.h>

int main()
{
	printf("Epoch Time: %d.\n", time(NULL));
	printTime();
	printDate();
	printTimeUTC();
	/*int num[1];
	while (1)
	{
		if (scanf("num=%d", num) > 0)
		{
			printf(", el num es:%d.\n", num[0]);
		}
		//clearWorkSpace();
	}
	char c;
	while (1)
	{
		if ((c = getchar()) != EOF)
		{
			putchar(c);
		}
	}*/

	iniciarBlobWars();

	return 0;
}