#include<stdio.h>
#include<stdlib.h>
#include "gif.h"


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
}icontable;//bgr
struct image
{
	int height;
	int width;
	struct RGB **rgb;
};

int main(int argc, char* argv[])
{   
	store(argv[1]);
	struct ICONDIR I;
	struct ICONDIRENTRY h;
	struct BITMAPINFOHEADER infoheader;

	FILE *fp;
	fp = fopen(argv[2],"wb");


    // header
	I.reserved = 0;
	I.imgtype = 1;
	I.no_of_img =1;
	fwrite(&I,sizeof(struct ICONDIR),1,fp);
	

   
	
	//Icon direntry
	h.width = source.W;
	h.height =source.H;
	h.colorPalette = 0;
	h.reserved =0;
	h.colorPlanes = 1;
	h.bitsPerPixel = 32;
	h.size_bitmapdata = 40+(h.height*4*h.width)+(h.height*4*h.width)/32;
	h.offset_bmp = 22;

	fwrite(&h,sizeof(struct ICONDIRENTRY),1,fp);


	// Bitmapinfo
    infoheader.header_size =40;
    infoheader.width =source.W;
    infoheader.height = 2*source.H;
    infoheader.colorPlanes = 1;
    infoheader.bitsPerPixel =32;
    infoheader.compMethod = 0;
    infoheader.sizeOfRawBitmapData = (h.height*4*h.width)+(h.height*4*h.width)/32;
    infoheader.horRes = 0;
    infoheader.VerRes =0;
    infoheader.colorsused=0;
    infoheader.colorsimportant=0;
    fwrite(&infoheader,sizeof(struct BITMAPINFOHEADER),1,fp);
    icontable *data;
    FILE *fp2;
    fp2=fopen("RGB_data.gif","rb");
    unsigned char r[h.height*h.width],g[h.height*h.width],b[h.height*h.width];
    int i=0;
    while(getc(fp2)!=EOF)
    {	fseek(fp2,-1,SEEK_CUR);
    	r[i]=getc(fp2);
    	g[i]=getc(fp2);
    	b[i]=getc(fp2);
    	i++;
    }
    for(i=h.width*(h.height-1);i>=0;i-=h.width)
    {
    	for(int j=i;j<i+h.width;j++)
    	{
    		fputc(b[j],fp);
    		fputc(g[j],fp);
    		fputc(r[j],fp);
    		fputc(255,fp);
    	}

    }
    for(i=0;i<(h.height*4*h.width)/32;i++)
    	fputc(0,fp);

    fclose(fp2);
    fclose(fp);
}


























