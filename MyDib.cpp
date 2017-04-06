#include "MyDib.h"
#include <stdio.h>


MyDib::MyDib()
{
	this->m_pDib = NULL;
}


MyDib::~MyDib()
{
	Close();
}

int	 MyDib::GetWidth()
{
	return ((BITMAPINFOHEADER *)m_pDib)->biWidth;
}
int	 MyDib::GetHeight()
{
	return	((BITMAPINFOHEADER *)m_pDib)->biHeight;
}
int  MyDib::GetBiBitCount()
{
	if (m_pDib != NULL)
		return ((BITMAPINFOHEADER *)m_pDib)->biBitCount;
	return 0;
}

int	 MyDib::GetSize()
{
	return  ((BITMAPINFOHEADER *)m_pDib)->biWidth*((BITMAPINFOHEADER *)m_pDib)->biHeight;
}

bool MyDib::Open(char* pzFileName)
{
	FILE *fp;
	int nBmpFileHeaderSize;
	//λͼ�ļ�ͷ,��Сռ14���ֽ�
	nBmpFileHeaderSize = sizeof(BITMAPFILEHEADER);

	fp = fopen(pzFileName, "rb");
	if (!fp)
		goto exit;
	fread((void *)&bmpFileHeader, nBmpFileHeaderSize, 1, fp);

	//�ж��ļ��ǲ���bmp�ļ�
	if (bmpFileHeader.bfType != *((WORD *)"BM"))
		goto failure;

	//�����ڴ�,�������λͼ�ļ�ͷ+��ɫ��+����
	m_pDib = (BYTE *)malloc((bmpFileHeader.bfSize - nBmpFileHeaderSize)*sizeof(BYTE));

	//�����ڴ�ʧ�ܾ�ȥfailure
	if (!m_pDib)
		goto failure;
	memset(m_pDib, 0, bmpFileHeader.bfSize - nBmpFileHeaderSize);

	//�Ѷ�ȡ����Ϣ������m_pDib��ָ����ڴ���
	fread(m_pDib, 1, bmpFileHeader.bfSize - nBmpFileHeaderSize, fp);


	if (((BITMAPINFOHEADER *)m_pDib)->biSizeImage == 0 )
	{
		
		BITMAPINFOHEADER *pDib = (BITMAPINFOHEADER *)m_pDib;

		//����λͼ�Ĵ�С
		pDib->biSizeImage = ((((pDib->biWidth*pDib->biBitCount) + 31)&~31) >> 3)*pDib->biHeight;
		printf("%d", pDib->biSizeImage);
	}

	m_pDibBits = GetBits();
	fclose(fp);
	return TRUE;

failure:
	fclose(fp);
exit:
	Close();
	return FALSE;
}

bool MyDib::Save(char* pzFileName)
{
	FILE *fp;
	int nBmpFileHeaderSize;
	RGBQUAD rgb[256];
	//λͼ�ļ�ͷ,��Сռ14���ֽ�
	nBmpFileHeaderSize = sizeof(BITMAPFILEHEADER);

	fp = fopen(pzFileName, "wb");
	if (!fp)
		goto exit;
	//д�ļ�ͷ��Ϣ
	fwrite(&bmpFileHeader, nBmpFileHeaderSize,1,fp);
	//д��Ϣͷ��Ϣ
	BITMAPINFOHEADER*   bi = (BITMAPINFOHEADER *)m_pDib;
	fwrite(bi, bi->biSize, 1, fp);
	//�ж�m_pDib�ǲ��Ƿ���ʧ��
	if (!m_pDib)
		goto failure;

	//���ļ���д���ɫ��
	for (int i = 0, j = 0; i < 256; i++)
	{
			rgb[i].rgbBlue = i;
			rgb[i].rgbGreen = i;
			rgb[i].rgbRed = i;
			rgb[i].rgbReserved = 0;
	}
	fwrite(&rgb, sizeof(rgb), 1, fp);
	//���ļ���д��λͼ��Ϣ
	fwrite(m_pDibBits, this->GetSize(),1,fp);
	 
	fclose(fp);
	return TRUE;

failure:
	Close();
exit:
	return FALSE;

}

BYTE* MyDib::GetBits()
{
	//the size of the color map is determined by the number
	//of RGBQUAD structures presend.
	//it also depends on the bit_depth of the Dib
	DWORD dwNumColors, dwColorTableSize;
	BITMAPINFOHEADER *lpDib = (BITMAPINFOHEADER *)m_pDib;

	WORD wBitCount = lpDib->biBitCount;

	if (lpDib->biSize >= 36)
		dwNumColors = lpDib->biClrUsed;
	else
		dwNumColors = 0;

	if (dwNumColors == 0)
	{
		if (wBitCount != 24)
			dwNumColors = 1L << wBitCount;
		else
			dwNumColors = 0;
	}

	dwColorTableSize = dwNumColors*sizeof(RGBQUAD);

	return m_pDib + (lpDib->biSize + dwColorTableSize);
}

void MyDib::Close()
{
	if (this->m_pDib != NULL)
	{
		free (m_pDib);
		m_pDib = NULL;
	}
}

void MyDib::SetBits(BYTE *image_in)
{
	this->m_pDibBits = image_in;
}
