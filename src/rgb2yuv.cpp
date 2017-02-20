
#include "rgb2yuv.h"

#define MY(a,b,c) (( a*  0.2989  + b*  0.5866  + c*  0.1145))
#define MU(a,b,c) (( a*(-0.1688) + b*(-0.3312) + c*  0.5000 + 128))
#define MV(a,b,c) (( a*  0.5000  + b*(-0.4184) + c*(-0.0816) + 128))

//´óÐ¡ÅÐ¶Ï
#define DY(a,b,c) (MY(a,b,c) > 255 ? 255 : (MY(a,b,c) < 0 ? 0 : MY(a,b,c)))
#define DU(a,b,c) (MU(a,b,c) > 255 ? 255 : (MU(a,b,c) < 0 ? 0 : MU(a,b,c)))
#define DV(a,b,c) (MV(a,b,c) > 255 ? 255 : (MV(a,b,c) < 0 ? 0 : MV(a,b,c)))

rgb2yuv::rgb2yuv()
{
}

rgb2yuv::~rgb2yuv()
{
}

int rgb2yuv::RGB2YUV422I(RGB888 &sRGB888, YUV422I &sYUV422I)
{
	if (sRGB888.uiWidth != sYUV422I.uiWidth)
	{
		printf("The RGB width not fit YUV422I width.\n");
		return -1;
	}

	if (sRGB888.uiHeight != sYUV422I.uiHeight)
	{
		printf("The RGB height not fit YUV422I height.\n");
		return -1;
	}

	unsigned int uiWidth = sRGB888.uiWidth;
	unsigned int uiHeight = sRGB888.uiHeight;

	unsigned int uiWidthUV = sYUV422I.uiWidthUV;
	unsigned int uiHeightUV = sYUV422I.uiHeightUV;

	unsigned int uiTotalNum = uiWidth * uiHeight
		+ uiWidthUV * uiHeightUV * 2;

	unsigned char* pRBuf = sRGB888.pRGB;
	unsigned char* pGBuf = sRGB888.pRGB + 1;
	unsigned char* pBBuf = sRGB888.pRGB + 2;

	unsigned char* pYBuf = sYUV422I.pYUV + 1;
	unsigned char* pUBuf = sYUV422I.pYUV;
	unsigned char* pVBuf = sYUV422I.pYUV + 2;

	for (unsigned int i = 0; i < uiHeight; i++)
	{
		unsigned char* pYTemp = pYBuf;
		unsigned char* pUTemp = pUBuf;
		unsigned char* pVTemp = pVBuf;
		unsigned int totalLen = uiWidth + uiWidthUV * 2;

		for (unsigned int j = 0; j < uiWidth; j++)
		{
			*pYTemp = (unsigned char)(DY(*pRBuf, *pGBuf, *pBBuf));

			if (j % 2 == 0)
			{
				*pUTemp = (unsigned char)(DU(*pRBuf, *pGBuf, *pBBuf));
				*pVTemp = (unsigned char)(DV(*pRBuf, *pGBuf, *pBBuf));

				pUTemp = ((pUTemp + 4) > (pUBuf + totalLen)) ? pUTemp : pUTemp + 4;
				pVTemp = ((pVTemp + 4) > (pUBuf + totalLen)) ? pVTemp : pVTemp + 4;
			}
			
			pYTemp = ((pYTemp + 2) > (pUBuf + totalLen)) ? pYTemp : pYTemp + 2;
			pRBuf = ((pRBuf + 3) > (sRGB888.pRGB + uiWidth * uiHeight * 3)) ? pRBuf : pRBuf + 3;
			pGBuf = ((pGBuf + 3) > (sRGB888.pRGB + uiWidth * uiHeight * 3)) ? pGBuf : pGBuf + 3;
			pBBuf = ((pBBuf + 3) > (sRGB888.pRGB + uiWidth * uiHeight * 3)) ? pBBuf : pBBuf + 3;
		}
		pYBuf = ((pYBuf + totalLen) > (sYUV422I.pYUV + uiTotalNum)) ? pYBuf : pYBuf + totalLen;
		pUBuf = ((pUBuf + totalLen) > (sYUV422I.pYUV + uiTotalNum)) ? pUBuf : pUBuf + totalLen;
		pVBuf = ((pVBuf + totalLen) > (sYUV422I.pYUV + uiTotalNum)) ? pVBuf : pVBuf + totalLen;
	}

	return 0;
}

int rgb2yuv::RGB2YUV420I(RGB888 &sRGB888, YUV420I &sYUV420I)
{
	if (sRGB888.uiWidth != sYUV420I.uiWidth)
	{
		printf("The RGB width not fit YUV422I width.\n");
		return -1;
	}

	if (sRGB888.uiHeight != sYUV420I.uiHeight)
	{
		printf("The RGB height not fit YUV422I height.\n");
		return -1;
	}

	unsigned int uiWidth = sRGB888.uiWidth;
	unsigned int uiHeight = sRGB888.uiHeight;

	unsigned int uiWidthUV = sYUV420I.uiWidthUV;
	unsigned int uiHeightUV = sYUV420I.uiHeightUV;

	unsigned int uiTotalNum = uiWidth * uiHeight
		+ uiWidthUV * uiHeightUV * 2;

	unsigned char* pRBuf = sRGB888.pRGB;
	unsigned char* pGBuf = sRGB888.pRGB + 1;
	unsigned char* pBBuf = sRGB888.pRGB + 2;

	unsigned char* pYBuf = sYUV420I.pYUV + 1;
	unsigned char* pUBuf = sYUV420I.pYUV;
	unsigned char* pVBuf = sYUV420I.pYUV + 2;

	for (unsigned int i = 0; i < uiHeight; i++)
	{
		unsigned char* pYTemp = pYBuf;
		unsigned char* pUTemp = pUBuf;
		unsigned char* pVTemp = pVBuf;
		unsigned int totalLen;

		if (i % 2 == 0)
		{
			totalLen = uiWidth + uiWidthUV * 2;
			for (unsigned int j = 0; j < uiWidth; j ++)
			{
				*pYTemp = (unsigned char)(DY(*pRBuf, *pGBuf, *pBBuf));
				if (j % 2 == 0)
				{
					*pUTemp = (unsigned char)(DU(*pRBuf, *pGBuf, *pBBuf));
					*pVTemp = (unsigned char)(DV(*pRBuf, *pGBuf, *pBBuf));

					pUTemp = ((pUTemp + 4) > (pUBuf + totalLen)) ? pUTemp : pUTemp + 4;
					pVTemp = ((pVTemp + 4) > (pUBuf + totalLen)) ? pVTemp : pVTemp + 4;
				}
				pYTemp = ((pYTemp + 2) > (pUBuf + totalLen)) ? pYTemp : pYTemp + 2;
				pRBuf = ((pRBuf + 3) > (sRGB888.pRGB + uiWidth * uiHeight * 3)) ? pRBuf : pRBuf + 3;
				pGBuf = ((pGBuf + 3) > (sRGB888.pRGB + uiWidth * uiHeight * 3)) ? pGBuf : pGBuf + 3;
				pBBuf = ((pBBuf + 3) > (sRGB888.pRGB + uiWidth * uiHeight * 3)) ? pBBuf : pBBuf + 3;
			}
		}
		else
		{
			totalLen = uiWidth;
			for (unsigned int j = 0; j < uiWidth; j++)
			{
				*pYTemp = (unsigned char)(DY(*pRBuf, *pGBuf, *pBBuf));
				pYTemp = ((pYTemp + 1) > (pUBuf + totalLen)) ? pYTemp : pYTemp + 1;
				pRBuf = ((pRBuf + 3) > (sRGB888.pRGB + uiWidth * uiHeight * 3)) ? pRBuf : pRBuf + 3;
				pGBuf = ((pGBuf + 3) > (sRGB888.pRGB + uiWidth * uiHeight * 3)) ? pGBuf : pGBuf + 3;
				pBBuf = ((pBBuf + 3) > (sRGB888.pRGB + uiWidth * uiHeight * 3)) ? pBBuf : pBBuf + 3;
			}
		}

		pYBuf = ((pYBuf + totalLen) > (sYUV420I.pYUV + uiTotalNum)) ? pYBuf : pYBuf + totalLen;
		pUBuf = ((pUBuf + totalLen) > (sYUV420I.pYUV + uiTotalNum)) ? pUBuf : pUBuf + totalLen;
		pVBuf = ((pVBuf + totalLen) > (sYUV420I.pYUV + uiTotalNum)) ? pVBuf : pVBuf + totalLen;
	}

	return 0;
}

int rgb2yuv::RGB2YUV422P(RGB888 &sRGB888, YUV422P &sYUV422P)
{
	if (sRGB888.uiWidth != sYUV422P.uiWidth)
	{
		printf("The RGB width not fit YUV422I width.\n");
		return -1;
	}

	if (sRGB888.uiHeight != sYUV422P.uiHeight)
	{
		printf("The RGB height not fit YUV422I height.\n");
		return -1;
	}
	
	unsigned int uiWidth = sRGB888.uiWidth;
	unsigned int uiHeight = sRGB888.uiHeight;

	unsigned int uiWidthUV = sYUV422P.uiWidthUV;
	unsigned int uiHeightUV = sYUV422P.uiHeightUV;

	unsigned int uiTotalNum = uiWidth * uiHeight
		+ uiWidthUV * uiHeightUV * 2;

	unsigned char* pRBuf = sRGB888.pRGB;
	unsigned char* pGBuf = sRGB888.pRGB + 1;
	unsigned char* pBBuf = sRGB888.pRGB + 2;

	unsigned char* pYBuf = sYUV422P.pYUV;
	unsigned char* pUBuf = sYUV422P.pYUV + uiWidth * uiHeight;
	unsigned char* pVBuf = sYUV422P.pYUV + uiWidth * uiHeight + uiWidthUV * uiHeightUV;

	for (unsigned int i = 0; i < uiHeight; i ++)
	{
		for (unsigned int j = 0; j < uiWidth; j ++)
		{
			*pYBuf = (unsigned char)(DY(*pRBuf, *pGBuf, *pBBuf));

			if (j % 2 == 0)
			{
				*pUBuf = (unsigned char)(DU(*pRBuf, *pGBuf, *pBBuf));
				*pVBuf = (unsigned char)(DV(*pRBuf, *pGBuf, *pBBuf));
// 				pUBuf++;
// 				pVBuf++;
				pUBuf = ((pUBuf + 1) > (sYUV422P.pYUV + uiTotalNum)) ? pUBuf : pUBuf + 1;
				pVBuf = ((pVBuf + 1) > (sYUV422P.pYUV + uiTotalNum)) ? pVBuf : pVBuf + 1;
			}

// 			pYBuf++;
// 			pRBuf += 3;
// 			pGBuf += 3;
// 			pBBuf += 3;
			pYBuf = ((pYBuf + 1) > (sYUV422P.pYUV + uiTotalNum)) ? pYBuf : pYBuf + 1;
			pRBuf = ((pRBuf + 3) > (sRGB888.pRGB + uiWidth * uiHeight * 3)) ? pRBuf : pRBuf + 3;
			pGBuf = ((pGBuf + 3) > (sRGB888.pRGB + uiWidth * uiHeight * 3)) ? pGBuf : pGBuf + 3;
			pBBuf = ((pBBuf + 3) > (sRGB888.pRGB + uiWidth * uiHeight * 3)) ? pBBuf : pBBuf + 3;
		}
	}

	return 0;
}

int rgb2yuv::RGB2YUV420P(RGB888 &sRGB888, YUV420P &sYUV420P)
{
	if (sRGB888.uiWidth != sYUV420P.uiWidth)
	{
		printf("The RGB width not fit YUV422I width.\n");
		return -1;
	}

	if (sRGB888.uiHeight != sYUV420P.uiHeight)
	{
		printf("The RGB height not fit YUV422I height.\n");
		return -1;
	}

	unsigned int uiWidth = sRGB888.uiWidth;
	unsigned int uiHeight = sRGB888.uiHeight;

	unsigned int uiWidthUV = sYUV420P.uiWidthUV;
	unsigned int uiHeightUV = sYUV420P.uiHeightUV;

	unsigned int uiTotalNum = uiWidth * uiHeight
		+ uiWidthUV * uiHeightUV * 2;

	unsigned char* pRBuf = sRGB888.pRGB;
	unsigned char* pGBuf = sRGB888.pRGB + 1;
	unsigned char* pBBuf = sRGB888.pRGB + 2;

	unsigned char* pYBuf = sYUV420P.pYUV;
	unsigned char* pUBuf = sYUV420P.pYUV + uiWidth * uiHeight;
	unsigned char* pVBuf = sYUV420P.pYUV + uiWidth * uiHeight + uiWidthUV * uiHeightUV;

	for (unsigned int i = 0; i < uiHeight; i++)
	{
		for (unsigned int j = 0; j < uiWidth; j++)
		{
			*pYBuf = (unsigned char)(DY(*pRBuf, *pGBuf, *pBBuf));
			
			if (j % 2 == 0 && i % 2 == 0)
			{
				*pUBuf = (unsigned char)(DU(*pRBuf, *pGBuf, *pBBuf));
				*pVBuf = (unsigned char)(DV(*pRBuf, *pGBuf, *pBBuf));
// 				pUBuf++;
// 				pVBuf++;
				pUBuf = ((pUBuf + 1) > (sYUV420P.pYUV + uiTotalNum)) ? pUBuf : pUBuf + 1;
				pVBuf = ((pVBuf + 1) > (sYUV420P.pYUV + uiTotalNum)) ? pVBuf : pVBuf + 1;
			}

			pYBuf = ((pYBuf + 1) > (sYUV420P.pYUV + uiTotalNum)) ? pYBuf : pYBuf + 1;
			pRBuf = ((pRBuf + 3) > (sRGB888.pRGB + uiWidth * uiHeight * 3)) ? pRBuf : pRBuf + 3;
			pGBuf = ((pGBuf + 3) > (sRGB888.pRGB + uiWidth * uiHeight * 3)) ? pGBuf : pGBuf + 3;
			pBBuf = ((pBBuf + 3) > (sRGB888.pRGB + uiWidth * uiHeight * 3)) ? pBBuf : pBBuf + 3;
		}
	}

	return 0;
}