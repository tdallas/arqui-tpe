/* sampleCodeModule.c */

#include <stdio.h>

int main()
{
	char c;
	while(1){
		if((c = getchar()) != EOF){
			putchar(c);
			printf("hola %d", 5);
		}
	}

	return 0;
}