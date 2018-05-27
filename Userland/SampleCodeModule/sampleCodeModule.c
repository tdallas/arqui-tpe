#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	char c;
	printf("Epoch Time: %d. ", time(NULL));
	printTime();
	/*char string[10];
	scanf("string=%s", string);
	printf(", el string es:%s", string);*/
	while(1){
		if((c = getchar()) != EOF){
			putchar(c);
		}
	}

	return 0;
}