//COMPLETAR .h CON CADA FUNCION
#include <stdlib.h>

#define IS_DIGIT(character) ((character - '0') >= 0 && (character - '0') <= 9)

unsigned long int rand_next = 1;

/*
 *  int rand()
 *      Taken from the K&R C programming language book. Page 46.
 *      returns a pseudo-random integer of 0..32767. Note that
 *      this is compatible with the System V function rand(), not
 *      with the bsd function rand() that returns 0..(2**31)-1.
 */
int rand()
{
	rand_next = rand_next * 1103515245 + 12345;
	return ((unsigned int)(rand_next / 65536) % 32768);
}

/*
 *  srand(seed)
 *      companion routine to rand(). Initializes the seed.
 */
void srand(unsigned int seed)
{
	rand_next = seed;
}

int isAlpha(char *c) {
	return IS_DIGIT(*c) ? 0 : 1;
}

// Parameters: Char pointer
// Return values: 2 if float, 1 if int, 0 if not num
//fixme estaria bueno hacer un refactor
int isDigit(char *string)
{

	int isFloat = 0;
	//Check wether it could by negative number
	if (*string == '-')
	{
		string++;
	}

	if (!IS_DIGIT(*string))
	{
		return 0;
	}
	string++;

	while (*string != '\0')
	{
		int dotRead = 0;		
		if (!IS_DIGIT(*string))
		{
			if (*string == '.'){
				if (dotRead > 0)
					return 0;
				isFloat++;
				dotRead++;
				string++;				
			}
			else
			{
				return 0;
			}
		}
		string++;
	}

	return 1 + isFloat;
}