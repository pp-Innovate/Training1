#ifndef __IMGFILE_H
#define __IMGFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <jpeglib.h>

typedef struct
{
	int width;
	int height;
	int maxIntensity;
	void *data;
}ImageTypeDef;

int imread(char *fileName,ImageTypeDef *outImg);
int imwrite(char *fileName,ImageTypeDef *inImg);

#endif /* __IMGFILE_H */

