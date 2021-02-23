#include <stdio.h>
#include <stdlib.h>

int nThBit(int no, int n);	// finds bit on the nth place
int noOfBits(int a, int lsb);	// finds size of each pixels using the first three bits of Packed


typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef long LONG;

#pragma pack(1)
typedef struct gifHeader 	// For the GIFHeader
{
	// Header
	BYTE Signature[3];     	// Header Signature (always "GIF")
	BYTE Version[3];       	// GIF format version("87a")
	// Logical Screen Descriptor
	WORD ScreenWidth;      	// Width of Display Screen in Pixels
	WORD ScreenHeight;     	// Height of Display Screen in Pixels
	BYTE Packed;           	// Screen and Color Map Information
	BYTE BackgroundColor;  	// Background Color Index
	BYTE AspectRatio;      	// Pixel Aspect Ratio
} GIFHEAD;

typedef struct _GifColorTable
{
  BYTE Red;          		// Red Color Element
  BYTE Green;        		// Green Color Element
  BYTE Blue;         		// Blue Color Element
} GIFCOLORTABLE;
typedef struct _GifImageDescriptor
{
  BYTE Separator;    		// Image Descriptor identifier
  WORD Left;         		// X position of image on the display
  WORD Top;          		// Y position of image on the display
  WORD Width;        		// Width of the image in pixels
  WORD Height;       		// Height of the image in pixels
  BYTE Packed;       		// Image and Color Table Data Information
} GIFIMGDESC;
typedef struct dimensions
{
	BYTE W;
	BYTE H;
}dimensions;
dimensions source;
void store(const char *argv);
int nThBit(int no, int n);	// finds bit on the nth place
int noOfBits(int a, int lsb);	// finds size of each pixels using the first three bits of Packed

