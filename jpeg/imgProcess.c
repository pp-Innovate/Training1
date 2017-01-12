#include "imgProcess.h"

int thresholding(ImageTypeDef *inImg,ImageTypeDef *outImg,int threshold)
{
	int pixels = inImg->width*inImg->height;

	outImg->width = inImg->width;
	outImg->height = inImg->height;
	outImg->maxIntensity = 255;
	outImg->data = (unsigned char *)malloc(pixels);

	int i;

	if(inImg->maxIntensity <= 255)
		for(i = 0;i < pixels;i++)
			if(*((unsigned char *)inImg->data + i) < threshold)
				*((unsigned char *)outImg->data + i) = 0;
			else
				*((unsigned char *)outImg->data + i) = 255;
	else
		for(i = 0;i < pixels;i++)
			if(*((unsigned short *)inImg->data + i) < threshold)
				*((unsigned char *)outImg->data + i) = 0;
			else
				*((unsigned char *)outImg->data + i) = 255;

	return 0;
}

