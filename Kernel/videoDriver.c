#include <videoDriver.h>

static vbe *vbeStruct = (vbe *)0x0000000000005C00; //Sacado de sysvar.asm en Bootloader/Pure64/src
static unsigned int actualX = 0;
static unsigned int actualY = 0;
static unsigned char backgroundR = 0;
static unsigned char backgroundG = 0;
static unsigned char backgroundB = 0;

unsigned char *getFrameBuffer()
{
	unsigned char *result = 0;
	result += vbeStruct->framebuffer;
	return result;
}

void printPixel(unsigned int x, unsigned int y, unsigned char R, unsigned char G, unsigned char B)
{
	if (((x >= 0) && (x <= vbeStruct->width) && (y >= 0) && (y <= vbeStruct->height)))
	{
		unsigned char *pixel = getFrameBuffer() + 3 * (x + y * vbeStruct->width);
		*pixel = B;
		*(pixel + 1) = G;
		*(pixel + 2) = R;
	}
}

void printChar(unsigned char c, unsigned char R, unsigned char G, unsigned char B)
{
	if (c == 0)
	{
		return;
	}
	else if (c == '\n')
	{
		newLine();
	}
	else if (c == '\t')
	{
		printString("    ", R, G, B);
	}
	else if (c == '\b')
	{
		backSpace();
	}
	else
	{
		if (actualX >= vbeStruct->width)
		{
			newLine();
		}
		unsigned char *charPixelMap = fontPixelMap(c);
		unsigned char charPixel;

		for (int y = 0; y < FONT_HEIGHT; y++)
		{
			for (int x = 0; x < FONT_WIDTH; x++)
			{
				charPixel = charPixelMap[y];
				charPixel >>= FONT_WIDTH - x;

				if (charPixel % 2 == 1)
				{
					printPixel(actualX + x, actualY + y, R, G, B);
				}
				else
				{
					printPixel(actualX + x, actualY + y, backgroundR, backgroundG, backgroundB);
				}
			}
		}
		actualX += FONT_WIDTH;
	}
}

void newLine()
{
	actualX = 0;
	actualY += FONT_HEIGHT;
	if (actualY >= vbeStruct->height)
	{
		actualY -= FONT_HEIGHT;
		shiftScreen();
	}
}

void shiftScreen()
{
	unsigned char *video = getFrameBuffer();
	memcpy(video, video + 3 * vbeStruct->width * FONT_HEIGHT, 3 * vbeStruct->width * (vbeStruct->height - FONT_HEIGHT));
	for (int y = actualY; y < vbeStruct->height; y++)
	{
		for (int x = 0; x < vbeStruct->width; x++)
		{
			printPixel(x, y, backgroundR, backgroundG, backgroundB);
		}
	}
}

void backSpace()
{
	if (actualX >= FONT_WIDTH)
	{
		actualX -= FONT_WIDTH;
		for (int y = 0; y < FONT_HEIGHT; y++)
		{
			for (int x = 0; x < FONT_WIDTH; x++)
			{
				printPixel(actualX + x, actualY + y, backgroundR, backgroundG, backgroundB);
			}
		}
	}
	else if (actualX == 0 && actualY != 0)
	{
		actualY -= FONT_HEIGHT;
		actualX = vbeStruct->width;
		backSpace();
	}
}

void printBackGround()
{
	for (int y = 0; y < vbeStruct->height; y++)
	{
		for (int x = 0; x < vbeStruct->width; x++)
		{
			printPixel(x, y, backgroundB, backgroundG, backgroundR);
		}
	}
	actualX = 0;
	actualY = 0;
}

void setBackGroundColor(unsigned char R, unsigned char G, unsigned char B){
	backgroundR = R;
	backgroundG = G;
	backgroundB = B;
}

void printString(const char *str, unsigned char R, unsigned char G, unsigned char B)
{
	int i;
	while (str[i] != 0)
	{
		printChar(str[i++], R, G, B);
	}
}