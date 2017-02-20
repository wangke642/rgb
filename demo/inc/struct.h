
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
	uint16_t	bfType;			//2 Bytes������Ϊ"BM"����0x424D ����Windowsλͼ�ļ�
	uint32_t	bfSize;			//4 Bytes������BMP�ļ��Ĵ�С
	uint16_t	bfReserved1;	//2 Bytes��������Ϊ0
	uint16_t	bfReserved2;	//2 Bytes��������Ϊ0
	uint32_t	bfOffBits;		//4 Bytes���ļ���ʼλ�õ�ͼ���������ݵ��ֽ�ƫ����
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct _tagBMP_INFOHEADER
{
	uint32_t	biSize;			//4 Bytes��INFOHEADER�ṹ���С�����������汾I NFOHEADER����������
	int32_t		biWidth;		//4 Bytes��ͼ���ȣ�������Ϊ��λ��
	int32_t		biHeight;		//4 Bytes��ͼ��߶ȣ�+��ͼ��洢˳��ΪBottom2Top��-��Top2Bottom
	uint16_t	biPlanes;		//2 Bytes��ͼ������ƽ�棬BMP�洢RGB���ݣ������Ϊ1
	uint16_t	biBitCount;		//2 Bytes��ͼ������λ��
	uint32_t	biCompression;	//4 Bytes��0����ѹ����1��RLE8��2��RLE4
	uint32_t	biSizeImage;	//4 Bytes��4�ֽڶ����ͼ�����ݴ�С
	int32_t		biXPelsPerMeter;//4 Bytes��������/�ױ�ʾ��ˮƽ�ֱ���
	int32_t		biYPelsPerMeter;//4 Bytes��������/�ױ�ʾ�Ĵ�ֱ�ֱ���
	uint32_t	biClrUsed;		//4 Bytes��ʵ��ʹ�õĵ�ɫ����������0��ʹ�����еĵ�ɫ������
	uint32_t	biClrImportant;	//4 Bytes����Ҫ�ĵ�ɫ����������0�����еĵ�ɫ����������Ҫ
}BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct _tagRGBQUAD
{
	uint8_t		rgbBlue;		//ָ����ɫǿ��
	uint8_t		rgbGreen;		//ָ����ɫǿ��
	uint8_t		rgbRed;			//ָ����ɫǿ��
//	uint8_t		rgbReserved;	//����������Ϊ0
} RGBQUAD, *PRGBQUAD;

#pragma pack ()

#endif