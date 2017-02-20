
#ifndef STRUCT_DEFINE
#define STRUCT_DEFINE

typedef signed char  int8_t;
typedef signed short int16_t;
typedef signed int   int32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

#pragma pack (1)

typedef struct tagBITMAPFILEHEADER
{
	uint16_t	bfType;			//2 Bytes，必须为"BM"，即0x424D 才是Windows位图文件
	uint32_t	bfSize;			//4 Bytes，整个BMP文件的大小
	uint16_t	bfReserved1;	//2 Bytes，保留，为0
	uint16_t	bfReserved2;	//2 Bytes，保留，为0
	uint32_t	bfOffBits;		//4 Bytes，文件起始位置到图像像素数据的字节偏移量
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct _tagBMP_INFOHEADER
{
	uint32_t	biSize;			//4 Bytes，INFOHEADER结构体大小，存在其他版本I NFOHEADER，用作区分
	int32_t		biWidth;		//4 Bytes，图像宽度（以像素为单位）
	int32_t		biHeight;		//4 Bytes，图像高度，+：图像存储顺序为Bottom2Top，-：Top2Bottom
	uint16_t	biPlanes;		//2 Bytes，图像数据平面，BMP存储RGB数据，因此总为1
	uint16_t	biBitCount;		//2 Bytes，图像像素位数
	uint32_t	biCompression;	//4 Bytes，0：不压缩，1：RLE8，2：RLE4
	uint32_t	biSizeImage;	//4 Bytes，4字节对齐的图像数据大小
	int32_t		biXPelsPerMeter;//4 Bytes，用象素/米表示的水平分辨率
	int32_t		biYPelsPerMeter;//4 Bytes，用象素/米表示的垂直分辨率
	uint32_t	biClrUsed;		//4 Bytes，实际使用的调色板索引数，0：使用所有的调色板索引
	uint32_t	biClrImportant;	//4 Bytes，重要的调色板索引数，0：所有的调色板索引都重要
}BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct _tagRGBQUAD
{
	uint8_t		rgbBlue;		//指定蓝色强度
	uint8_t		rgbGreen;		//指定绿色强度
	uint8_t		rgbRed;			//指定红色强度
//	uint8_t		rgbReserved;	//保留，设置为0
} RGBQUAD, *PRGBQUAD;

#pragma pack ()

#endif