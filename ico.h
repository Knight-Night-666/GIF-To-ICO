#include<stdio.h>
#include<stdlib.h>

#pragma pack (1)
struct ICONDIR
{
	unsigned short int reserved;
	unsigned short int imgtype;
	unsigned short int no_of_img;
};
struct ICONDIRENTRY
{
	unsigned char width;
	unsigned char height;
	unsigned char colorPalette;
	unsigned char reserved;
	unsigned short int colorPlanes;
	unsigned short int bitsPerPixel;
	unsigned int size_bitmapdata;
	unsigned int offset_bmp;
};
struct BITMAPINFOHEADER
{
	unsigned int header_size;
	int width;
	int height;
	unsigned short int colorPlanes;
	unsigned short int bitsPerPixel;
	unsigned int compMethod;
	unsigned int sizeOfRawBitmapData;
	unsigned int horRes;
	unsigned int VerRes;
	unsigned int colorsused;
	unsigned int colorsimportant;
};
typedef struct  RGB
{	
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char alpha_val;
}icontable;