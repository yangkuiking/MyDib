#pragma once
#include <Windows.h>
typedef unsigned char	BYTE;
class MyDib
{
public:
	MyDib();
	~MyDib();
	int	 GetWidth();//�õ�ͼ��Ŀ�
	int	 GetHeight();//�õ�ͼ��ĸ�
	int  GetBiBitCount();//�õ�ͼ���Ƕ���λ��
	int	  GetSize();//�õ�ͼ��Ĵ�С
public:
	bool Open(char* pzFileName);//����·����ͼ��
	bool Save(char* pzFileName);//����·������ͼ��
	BYTE * GetBits();//�õ�λͼ�����ݵ�ָ��
	void SetBits(BYTE *image_in);//����λͼ�����ݵ�ָ��
	void Close();//�ر���Դ
public:
	BYTE		*m_pDib;//����ָ��
	BYTE		*m_pDibBits;//ָ��ͼ������
	BITMAPFILEHEADER bmpFileHeader;//����λͼ�ļ�ͷ����Ϣ
};

