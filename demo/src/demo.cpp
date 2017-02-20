
#include "struct.h"
#include "rgb2yuv.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("The arguments is not right\n");
		return -1;
	}

	int ret;
	unsigned int iWidth, iHeight;
	unsigned short iBitCount;
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	RGBQUAD rgbInfo;
	rgb2yuv cRgb2Yuv;

	FILE* fp = fopen(argv[1], "rb");
	if (fp == NULL)
	{
		printf("BMP file open error\n");
		return -1;
	}

	fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	if (0x4D42 != fileHeader.bfType)
	{
		printf("BMP file Type is not right\n");
		return -1;
	}

	fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

	iBitCount = infoHeader.biBitCount;
	if (24 != iBitCount)
	{
		printf("BMP file is not RGB888 format\n");
		return -1;
	}

	iWidth = infoHeader.biWidth;
	iHeight = infoHeader.biHeight;

	RGB888 sRgb888(iWidth, iHeight);

	unsigned char* pRGB = sRgb888.pRGB;

	unsigned char* pRBuf = sRgb888.pRGB;
	unsigned char* pGBuf = sRgb888.pRGB + 1;
	unsigned char* pBBuf = sRgb888.pRGB + 2;

	unsigned int iStep = iWidth * 3;
	unsigned int iOffset = (iWidth * 3) % 4;

	if (iOffset != 0)
	{
		iOffset = 4 - iOffset;
	}

	for (unsigned int i = 0; i < iHeight; i++)
	{
		for (unsigned int j = 0; j < iWidth * 3; j+=3)
		{
			fread(&rgbInfo, sizeof(RGBQUAD), 1, fp);

			pRGB[(iHeight - 1 - i) * iWidth * 3 + j] = rgbInfo.rgbRed;
			pRGB[(iHeight - 1 - i) * iWidth * 3 + j + 1] = rgbInfo.rgbGreen;
			pRGB[(iHeight - 1 - i) * iWidth * 3 + j + 2] = rgbInfo.rgbBlue;
		}
		if (iOffset != 0)
		{
			fseek(fp, iOffset, SEEK_CUR);
		}
	}

	YUV422P sYuv422P(iWidth, iHeight);
	YUV422I sYuv422I(iWidth, iHeight);
	YUV420P sYuv420P(iWidth, iHeight);
	YUV420I sYuv420I(iWidth, iHeight);

	ret = cRgb2Yuv.RGB2YUV422P(sRgb888, sYuv422P);
	if (-1 == ret)
	{
		printf("RGB2YUV422P error\n");
		return -1;
	}

	ret = cRgb2Yuv.RGB2YUV422I(sRgb888, sYuv422I);
	if (-1 == ret)
	{
		printf("RGB2YUV422I error\n");
		return -1;
	}

	ret = cRgb2Yuv.RGB2YUV420P(sRgb888, sYuv420P);
	if (-1 == ret)
	{
		printf("RGB2YUV420P error\n");
		return -1;
	}

	ret = cRgb2Yuv.RGB2YUV420I(sRgb888, sYuv420I);
	if (-1 == ret)
	{
		printf("RGB2YUV420I error\n");
		return -1;
	}
	
	FILE *fpYUV422P = fopen("test_yuv422p.yuv", "wb");
	if (NULL == fpYUV422P)
	{
		printf("test_yuv422p file open error\n");
		return -1;
	}

	FILE *fpYUV422I = fopen("test_yuv422i.yuv", "wb");
	if (NULL == fpYUV422I)
	{
		printf("test_yuv422i file open error\n");
		return -1;
	}

	FILE *fpYUV420P = fopen("test_yuv420p.yuv", "wb");
	if (NULL == fpYUV420P)
	{
		printf("test_yuv420p file open error\n");
		return -1;
	}

	FILE *fpYUV420I = fopen("test_yuv420i.yuv", "wb");
	if (NULL == fpYUV420I)
	{
		printf("test_yuv420i file open error\n");
		return -1;
	}

	fwrite(sYuv422P.pYUV, sYuv422P.uiWidth*sYuv422P.uiHeight +
		sYuv422P.uiWidthUV*sYuv422P.uiHeightUV * 2, 1, fpYUV422P);
	fwrite(sYuv422I.pYUV, sYuv422I.uiWidth*sYuv422I.uiHeight +
		sYuv422I.uiWidthUV*sYuv422I.uiHeightUV * 2, 1, fpYUV422I);
	fwrite(sYuv420P.pYUV, sYuv420P.uiWidth*sYuv420P.uiHeight +
		sYuv420P.uiWidthUV*sYuv420P.uiHeightUV * 2, 1, fpYUV420P);
	fwrite(sYuv420I.pYUV, sYuv420I.uiWidth*sYuv420I.uiHeight +
		sYuv420I.uiWidthUV*sYuv420I.uiHeightUV * 2, 1, fpYUV420I);

	if (fp)
	{
		fclose(fp);
	}
	if (fpYUV422P)
	{
		fclose(fpYUV422P);
	}
	if (fpYUV422I)
	{
		fclose(fpYUV422I);
	}
	if (fpYUV420P)
	{
		fclose(fpYUV420P);
	}
	if (fpYUV420I)
	{
		fclose(fpYUV420I);
	}

	return 0;
}