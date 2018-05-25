/* sampleCodeModule.c */

#include <stdio.h>

int main()
{
	char c;
	while(1){
		if((c = getChar()) != EOF){
			putChar(c);
		}
	}

	return 0;
}