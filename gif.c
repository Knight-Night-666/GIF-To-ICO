#include<stdio.h>
#include"gif.h"
void store(const char *argv)
{	
	char ch;
	FILE *fpr;				// Points to file memory
	GIFHEAD *gHead = (GIFHEAD*)malloc(sizeof(GIFHEAD));	
	fpr = fopen(argv,"rb");

	// HEADER
	fread(&(gHead->Signature),sizeof(BYTE),3,fpr);						// Signature

	fread(&(gHead->Version),sizeof(BYTE),3,fpr);						// Version
	// Logical Descriptor
	fread(&(gHead->ScreenWidth),sizeof(WORD),1,fpr);					// ScreenWidth
	fread(&(gHead->ScreenHeight),sizeof(WORD),1,fpr);
	source.W=gHead->ScreenWidth;
	source.H=gHead->ScreenHeight;					// ScreenHeight
	fread(&(gHead->Packed),sizeof(BYTE),1,fpr);							// Packed
	int sizOfGloColTable = noOfBits(gHead->Packed,0);					// Size of Global Color Table
	LONG noOfGloColTabEnt = (1L << (sizOfGloColTable + 1));				// No of Global Color Table Entries
	int bitsPerColor = noOfBits(gHead->Packed,1);						// Bits per Color
	int gloFlag = nThBit(gHead->Packed,7);								// Global Color Table Exists or not
	fread(&(gHead->BackgroundColor),sizeof(BYTE),1,fpr);				// Background Color (Ingnore for 87a)
	fread(&(gHead->AspectRatio),sizeof(BYTE),1,fpr);					// Aspect Ratio (1-255) for calc of Pixel Aspect Ratio
	int pixAsRat = (gHead->AspectRatio+15)/64;

	// GLOBAL COLOR TABLE
	LONG colorTableSize = gloFlag*(3L * (1L << (sizOfGloColTable + 1)));
	int noOfStructsUsed = colorTableSize/sizeof(GIFCOLORTABLE);
	GIFCOLORTABLE table[noOfStructsUsed];
	FILE *fp1;
	int i = 0;
	while(i<noOfStructsUsed)
	{
		fread(&((table + i)->Red),sizeof(BYTE),1,fpr);
		fread(&((table + i)->Green),sizeof(BYTE),1,fpr);
		fread(&((table + i)->Blue),sizeof(BYTE),1,fpr);
		i++;
	}

	// LOCAL IMAGE DESCRIPTOR
	GIFIMGDESC *gImgDes = (GIFIMGDESC*)malloc(sizeof(GIFIMGDESC));

	fread(&(gImgDes->Separator),sizeof(BYTE),1,fpr);					// Separator Character
	fread(&(gImgDes->Left),sizeof(WORD),1,fpr);							// X Position
	fread(&(gImgDes->Top),sizeof(WORD),1,fpr);							// Y Position
	fread(&(gImgDes->Width),sizeof(WORD),1,fpr);						// Width of image
	fread(&(gImgDes->Height),sizeof(WORD),1,fpr);						// Height of image
	fread(&(gImgDes->Packed),sizeof(BYTE),1,fpr);						// Packed
	int locColTabFlag = nThBit(gImgDes->Packed,0);						// Local Color Table Flag
	int interlaceFlag = nThBit(gImgDes->Packed,1);						// Interlace Flag	// Local Color Sort Flag (0 for 87a)
	int sizOfLocColTab = noOfBits(gImgDes->Packed,5);					// Size of Local Color Table
	// LOCAL COLOR TABLE
	LONG colTableSize = locColTabFlag*(3L * (1L << (sizOfLocColTab + 1)));
	noOfStructsUsed = colTableSize/sizeof(GIFCOLORTABLE);
	GIFCOLORTABLE locTable[noOfStructsUsed];

	i = 0;
	while(i<noOfStructsUsed)
	{
		fread(&((locTable + i)->Red),sizeof(BYTE),1,fpr);
		fread(&((locTable + i)->Green),sizeof(BYTE),1,fpr);
		fread(&((locTable + i)->Blue),sizeof(BYTE),1,fpr);
		i++;
	}
	char c;
	FILE *fp2;
	fp2=fopen("RGB_data.gif","wb");
	
	fseek(fpr,2,SEEK_CUR);
	long int img_start=ftell(fpr);
	fseek(fpr,0,SEEK_END);
	long int img_end=ftell(fpr);
	fseek(fpr,img_start+1,SEEK_SET);
	
	while(ftell(fpr)<img_end-4)
	{		
			if((int)getc(fpr)==(gHead->ScreenHeight+1))
			{
				fseek(fpr,1,SEEK_CUR);
				continue;
			}
			fseek(fpr,-1,SEEK_CUR);
			c=getc(fpr);
			fwrite((table+c),sizeof(GIFCOLORTABLE),1,fp2);
	}
	free(gImgDes);
	free(gHead);
	fclose(fpr);
	fclose(fp2);
	
}
int nThBit(int no, int n)// finds bit on the nth place
{
	return (no & (1 << n)) >> n	;
}

int noOfBits(int a, int lsb)// finds size of each pixels using the first three bits of Packed
{
	int b[3];
	int j = 0;
	for(int i=lsb ; i<lsb+3 ; i++)
		b[j++] = nThBit(a,i);
	return (b[2] * 4 + b[1] * 2 + b[0] * 1);
}