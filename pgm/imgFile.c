#include "imgFile.h"

int imread(char *fileName,ImageTypeDef *outImg)
{
	FILE *fp;

	/* 打开文件 */
	if(!(fp = fopen(fileName,"r")))
		return -1;

	char type[3];

	/* 格式化读取pgm图像文件的信息头 */
	fscanf(fp,"%s\n%d %d\n%d\n",type,&outImg->width,&outImg->height,&outImg->maxIntensity);

	/* 只针对P5类型的pgm文件 */
	if(strcmp(type,"P5"))
	{
		if(!strcmp(type,"P2"))
			printf("Do not support P2 file type!\n");
		else
			printf("Unknown file type!\n");

		fclose(fp);

		return -1;
	}

	long int pixels = outImg->width*outImg->height;

	/* 为图像数据分配内存，并从文件中块读取图像数据 */
	if(outImg->maxIntensity <= 255)      //每个像素用单字节存储
	{
		outImg->data = (unsigned char *)malloc(pixels);
		fread((unsigned char *)outImg->data,1,pixels,fp);
	}
	else                                 //每个像素用两个字节存储
	{
		outImg->data = (unsigned short *)malloc(pixels);
		fread((unsigned short *)outImg->data,2,pixels,fp);
	}

	/* 关闭文件流 */
	fclose(fp);

	return 0;
}

int imwrite(char *fileName,ImageTypeDef *inImg)
{
	FILE *fp;

	/* 打开文件 */
	if(!(fp = fopen(fileName,"w")))
		return -1;

	/* 格式化输出pgm图像文件的信息头 */
	fprintf(fp,"P5\n%d %d\n%d\n",inImg->width,inImg->height,inImg->maxIntensity);

	long int pixels = inImg->width*inImg->height;

	/* 块写入图像数据 */
	if(inImg->maxIntensity <= 255)
		fwrite((unsigned char *)inImg->data,1,pixels,fp);
	else
		fwrite((unsigned short *)inImg->data,2,pixels,fp);

	/* 关闭文件流 */
	fclose(fp);

	return 0;
}
