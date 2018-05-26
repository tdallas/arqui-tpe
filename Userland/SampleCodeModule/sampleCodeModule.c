/* sampleCodeModule.c */

#include <stdio.h>

int main()
{
	char c;
	while(1){
		if((c = getchar()) != EOF){
			putchar(c);
		}
	}

	return 0;
}