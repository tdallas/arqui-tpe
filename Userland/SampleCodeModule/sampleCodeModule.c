/* sampleCodeModule.c */

#include <stdio.h>
#include <time.h>

int main()
{
	char c;
	printf("Epoch Time: %d. ", time(NULL));
	printTime();
	while(1){
		if((c = getchar()) != EOF){
			putchar(c);
		}
	}

	return 0;
}