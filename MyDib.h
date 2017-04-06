#pragma once
#include <Windows.h>
typedef unsigned char	BYTE;
class MyDib
{
public:
	MyDib();
	~MyDib();
	int	 GetWidth();//得到图像的宽
	int	 GetHeight();//得到图像的高
	int  GetBiBitCount();//得到图像是多少位的
	int	  GetSize();//得到图像的大小
public:
	bool Open(char* pzFileName);//根据路径打开图像
	bool Save(char* pzFileName);//根据路径保存图像
	BYTE * GetBits();//得到位图纯数据的指针
	void SetBits(BYTE *image_in);//设置位图纯数据的指针
	void Close();//关闭资源
public:
	BYTE		*m_pDib;//过渡指针
	BYTE		*m_pDibBits;//指向图像数据
	BITMAPFILEHEADER bmpFileHeader;//保存位图文件头的信息
};

