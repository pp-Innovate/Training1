#ifndef __IMGFILE_H
#define __IMGFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int width;         //图像宽度
	int height;        //图像高度
	int maxIntensity;  //最大灰度取值
	void *data;        //图像数据区指针
}ImageTypeDef;

int imread(char *fileName,ImageTypeDef *outImg);
int imwrite(char *fileName,ImageTypeDef *inImg);

#endif /* __IMGFILE_H */

