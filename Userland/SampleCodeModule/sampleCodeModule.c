#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	char c;
	printf("Epoch Time: %d. ", time(NULL));
	printTime();
	printf(",%d,", -25);
	while(1){
		if((c = getchar()) != EOF){
			putchar(c);
		}
	}

	return 0;
}