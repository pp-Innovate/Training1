#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "imgFile.h"
#include "imgProcess.h"

void printHelpMessage(void);
bool checkFileName(char *fileName);

char inputFileName[256];
char outputFileName[256];
int threshold = 128;

int main(int argc, char *argv[])
{
	int opt;

	if(argc == 1)
	{
		printHelpMessage();
		return 0;
	}

	while((opt = getopt(argc,argv,"hi:o:t:")) != -1)
	{
		switch(opt)
		{
		case 'h':printHelpMessage();return 0;
		case 'i':strcpy(inputFileName,optarg);break;
		case 'o':strcpy(outputFileName,optarg);break;
		case 't':threshold = atoi(optarg);break;
		default:printf("Invalid argument %c\n",opt);return -1;
		}
	}

	if(checkFileName(inputFileName) != true)
	{
		printf("Invalid input file %s\n",inputFileName);
		return -1;
	}

	if(checkFileName(outputFileName) != true)
	{
		printf("Invalid output file %s\n",outputFileName);
		return -1;
	}

	ImageTypeDef img,img_thr;
	struct timeval before,after;

	if(imread(inputFileName,&img))
	{
		printf("Can not read file: %s\n",inputFileName);
		return -1;
	}

	gettimeofday(&before,NULL);
	thresholding(&img,&img_thr,threshold);
	gettimeofday(&after,NULL);

	if(imwrite(outputFileName,&img_thr))
	{
		printf("Can not save file: %s\n",outputFileName);
		return -1;
	}

	free(img.data);
	free(img_thr.data);

	printf("Thresholding completed, using %ldus\n",(after.tv_sec - before.tv_sec)*1000000 + (after.tv_usec - before.tv_usec));

	return 0;
}

bool checkFileName(char *fileName)
{
	char *ptr;

	ptr = strrchr(fileName,'.');
	if(!ptr)
		return false;
	else if(strcmp(ptr,".jpg") != 0)
		return false;
	else
		return true;
}

void printHelpMessage(void)
{
	printf("This is a image processing demo.\n");
	printf("Author: 彭澎,1631552pp@tongji.edu.cn\n\n");
	printf("Usage:\n");
	printf("\t demo [options] ...\n\n");
	printf("Options:\n");
	printf("\t-h\tprint this help message.\n");
	printf("\t-i\tinput image file, it should be a .jpg file.\n");
	printf("\t-o\toutput image file, it should be a .jpg file.\n");
	printf("\t-t\tset threshold, default 128.\n");
}
