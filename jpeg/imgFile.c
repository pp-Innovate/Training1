#include "imgFile.h"

int imread(char *fileName,ImageTypeDef *outImg)
{
	FILE *fp;

	if(!(fp = fopen(fileName,"rb")))
		return -1;

	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo,fp);
	jpeg_read_header(&cinfo,true);

	cinfo.out_color_space = JCS_YCbCr;

	jpeg_start_decompress(&cinfo);

	outImg->width = cinfo.output_width;
	outImg->height = cinfo.output_height;
	outImg->maxIntensity = 255;

	long int pixels = outImg->width*outImg->height;

	outImg->data = (unsigned char *)malloc(pixels);

	unsigned char *buffer = (unsigned char *)malloc(cinfo.output_width*cinfo.output_components);

	unsigned char *ptr = (unsigned char *)outImg->data;
	while(cinfo.output_scanline < cinfo.output_height)
	{
		jpeg_read_scanlines(&cinfo,(JSAMPARRAY)&buffer,1);

		int i;
		for(i = 0;i < cinfo.output_width;i++)
		{
			*ptr = *(buffer + i*cinfo.output_components);
			ptr++;
		}
	}

	free(buffer);
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	fclose(fp);

	return 0;
}

int imwrite(char *fileName,ImageTypeDef *inImg)
{
	FILE *fp;

	if(!(fp = fopen(fileName,"wb")))
		return -1;

	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo,fp);

	cinfo.image_width = inImg->width;
	cinfo.image_height = inImg->height;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_YCbCr;

	jpeg_set_defaults(&cinfo);
	jpeg_start_compress(&cinfo,true);

	unsigned char *buffer = (unsigned char *)malloc(cinfo.image_width*cinfo.input_components);
	memset(buffer,127,cinfo.image_width*cinfo.input_components);

	unsigned char *ptr = (unsigned char *)inImg->data;
	while(cinfo.next_scanline < cinfo.image_height)
	{
		int i;
		for(i = 0;i < cinfo.image_width;i++)
		{
			*(buffer + i*cinfo.input_components) = *ptr;
			ptr++;
		}

		jpeg_write_scanlines(&cinfo,(JSAMPARRAY)&buffer,1);
	}

	free(buffer);
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);

	fclose(fp);

	return 0;
}
