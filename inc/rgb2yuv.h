
#ifndef RGB2YUV_DEFINE
#define RGB2YUV_DEFINE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct RGB888
{
	unsigned int uiWidth;
	unsigned int uiHeight;
	unsigned char* pRGB;

	RGB888(unsigned int uiWidth, unsigned int uiHeight)
	{
		this->uiWidth = uiWidth;
		this->uiHeight = uiHeight;
		this->pRGB = new unsigned char[uiWidth * uiHeight * 3];
	}
	
	~RGB888()
	{
		this->uiWidth = 0;
		this->uiHeight = 0;
		if (this->pRGB)
		{
			delete[](this->pRGB);
			this->pRGB = NULL;
 		}
	}
};

struct YUV420I
{
	unsigned int uiWidth;
	unsigned int uiHeight;

	unsigned int uiWidthUV;
	unsigned int uiHeightUV;

	unsigned char* pYUV;

	YUV420I(unsigned int uiWidth, unsigned int uiHeight)
	{
		this->uiWidth = uiWidth;
		this->uiHeight = uiHeight;

		this->uiWidthUV = ceil(((float)uiWidth)/2.0);
		this->uiHeightUV = ceil(((float)uiHeight)/2.0);

		this->pYUV = 
			new unsigned char[uiWidth * uiHeight + (this->uiWidthUV) * (this->uiHeightUV) * 2];
	}

	~YUV420I()
	{
		this->uiWidth = 0;
		this->uiHeight = 0;

		this->uiWidthUV = 0;
		this->uiHeightUV = 0;

		if (this->pYUV)
		{
			delete[](this->pYUV);
			this->pYUV = NULL;
		}
	}

};

struct YUV420P
{
	unsigned int uiWidth;
	unsigned int uiHeight;

	unsigned int uiWidthUV;
	unsigned int uiHeightUV;

	unsigned char* pYUV;

	YUV420P(unsigned int uiWidth, unsigned int uiHeight)
	{
		this->uiWidth = uiWidth;
		this->uiHeight = uiHeight;

		this->uiWidthUV = ceil((float)uiWidth / 2.0);
		this->uiHeightUV = ceil((float)uiHeight / 2.0);

		this->pYUV =
			new unsigned char[uiWidth * uiHeight + (this->uiWidthUV) * (this->uiHeightUV) * 2];
	}

	~YUV420P()
	{
		this->uiWidth = 0;
		this->uiHeight = 0;

		this->uiWidthUV = 0;
		this->uiHeightUV = 0;

		if (this->pYUV)
		{
			delete[](this->pYUV);
			this->pYUV = NULL;
		}
	}
};

struct YUV422I
{
	unsigned int uiWidth;
	unsigned int uiHeight;

	unsigned int uiWidthUV;
	unsigned int uiHeightUV;

	unsigned char* pYUV;

	YUV422I(unsigned int uiWidth, unsigned int uiHeight)
	{
		this->uiWidth = uiWidth;
		this->uiHeight = uiHeight;

		this->uiWidthUV = ceil((float)uiWidth / 2.0);
		this->uiHeightUV = uiHeight;

		this->pYUV =
			new unsigned char[uiWidth * uiHeight + (this->uiWidthUV) * uiHeight * 2];
	}

	~YUV422I()
	{
		this->uiWidth = 0;
		this->uiHeight = 0;

		this->uiWidthUV = 0;
		this->uiHeightUV = 0;

		if (this->pYUV)
		{
			delete[](this->pYUV);
			this->pYUV = NULL;
		}
	}
};

struct YUV422P
{
	unsigned int uiWidth;
	unsigned int uiHeight;

	unsigned int uiWidthUV;
	unsigned int uiHeightUV;

	unsigned char* pYUV;

	YUV422P(unsigned int uiWidth, unsigned int uiHeight)
	{
		this->uiWidth = uiWidth;
		this->uiHeight = uiHeight;

		this->uiWidthUV = ceil((float)uiWidth / 2.0);
		this->uiHeightUV = uiHeight;

		this->pYUV =
			new unsigned char[uiWidth * uiHeight + (this->uiWidthUV) * uiHeight * 2];
	}

	~YUV422P()
	{
		this->uiWidth = 0;
		this->uiHeight = 0;

		this->uiWidthUV = 0;
		this->uiHeightUV = 0;

		if (this->pYUV)
		{
			delete[](this->pYUV);
			this->pYUV = NULL;
		}
	}
};

class rgb2yuv
{
public:
	rgb2yuv();
	~rgb2yuv();

	int RGB2YUV420I(RGB888 &sRGB888, YUV420I &sYUV420I);

	int RGB2YUV420P(RGB888 &sRGB888, YUV420P &sYUV420P);

	int RGB2YUV422I(RGB888 &sRGB888, YUV422I &sYUV422I);

	int RGB2YUV422P(RGB888 &sRGB888, YUV422P &sYUV422P);

private:

};

#endif // !RGB2YUV_DEFINE
