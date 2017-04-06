#include "MyFun.h"
#define HIGH 255
#define LOW 0


//һ��΢�ֱ�Ե���
void Differential(BYTE *image_in, BYTE *image_out, int xsize, int ysize, float amp)
{
/*////////////////////////////////////////////////////////////////////
// ���ߣ����
//�����б� 
//image_in			����ͼ���ָ��
//image_out		���ͼ���ָ��
//xsize				ͼ��Ŀ�
//ysize				ͼ��ĸ�
//amp					�������ֵ����
////////////////////////////////////////////////////////////////////*/
	static int cx[9] = { 0, 0, 0,
		0, 1, 0,
		0, 0, -1 };
	static int cy[9] = { 0, 0, 0,
		0, 0, 1,
		0, -1, 0 };
	int d[9];
	int i, j, dat;
	float xx = 0.0, yy = 0.0, zz = 0.0;
	for (j = 1; j < ysize - 1; j++)
	{
		for (i = 1; i < xsize - 1; i++)
		{
			d[0] = *(image_in + (j - 1)*xsize + i - 1);
			d[1] = *(image_in + (j - 1)*xsize + i);
			d[2] = *(image_in + (j - 1)*xsize + i + 1);
			d[3] = *(image_in + j *xsize + i - 1);
			d[4] = *(image_in + j *xsize + i);
			d[5] = *(image_in + j *xsize + i + 1);
			d[6] = *(image_in + (j + 1)*xsize + i - 1);
			d[7] = *(image_in + (j + 1)*xsize + i - 1);
			d[8] = *(image_in + (j + 1)*xsize + i - 1);

			xx = (float)(cx[0] * d[0] + cx[1] * d[1] + cx[2] * d[2] + cx[3] * d[3] + cx[4] * d[4] + cx[5] * d[5] + cx[6] * d[6] + cx[7] * d[7] + cx[8] * d[8]);
			yy = (float)(cy[0] * d[0] + cy[1] * d[1] + cy[2] * d[2] + cy[3] * d[3] + cy[4] * d[4] + cy[5] * d[5] + cy[6] * d[6] + cy[7] * d[7] + cy[8] * d[8]);

			zz = (float)(amp *sqrt(xx*xx + yy*yy));
			dat = (int)zz;
			if (dat > 255)
			{
				dat = 255;
			}
			*(image_out + j*xsize + i) = dat;
		}
	}
}

//����΢�ֱ�Ե���
void Differential2(BYTE *image_in, BYTE *image_out, int xsize, int ysize, float amp)
{
/*////////////////////////////////////////////////////////////////////
// ���ߣ����
//�����б�
//image_in			����ͼ���ָ��
//image_out		���ͼ���ָ��
//xsize				ͼ��Ŀ�
//ysize				ͼ��ĸ�
//amp					�������ֵ����
////////////////////////////////////////////////////////////////////*/
	static int c[9] = { -1, -1, -1,
							-1, 8, -1,
							-1, -1, -1 };
	int d[9];
	int i, j, dat;
	float z=0.0, zz = 0.0;
	for (j = 1; j < ysize - 1; j++)
	{
		for (i = 1; i < xsize - 1; i++)
		{
			d[0] = *(image_in + (j - 1)*xsize + i - 1);
			d[1] = *(image_in + (j - 1)*xsize + i);
			d[2] = *(image_in + (j - 1)*xsize + i + 1);
			d[3] = *(image_in + j *xsize + i - 1);
			d[4] = *(image_in + j *xsize + i);
			d[5] = *(image_in + j *xsize + i + 1);
			d[6] = *(image_in + (j + 1)*xsize + i - 1);
			d[7] = *(image_in + (j + 1)*xsize + i - 1);
			d[8] = *(image_in + (j + 1)*xsize + i - 1);
			z = (float)(c[0] * d[0] + c[1] * d[1] + c[2] * d[2] + c[3] * d[3] + c[4] * d[4] + c[5] * d[5] + c[6] * d[6] + c[7] * d[7] + c[8] * d[8]);
			zz = amp*z;
			dat = (int)zz;
			if (dat<0)
			{
				dat = -dat;
			}
			if (dat>255)
			{
				dat = 255;
			}
			*(image_out + j*xsize + i) = dat;
		}
	}
}

//��ֵ��
void Binary(BYTE *image_in, BYTE *image_out, int xsize, int ysize ,int threshold/*��ֵ*/)
{
	/*////////////////////////////////////////////////////////////////////
	// ���ߣ����
	//�����б�
	//image_in			����ͼ���ָ��
	//image_out		���ͼ���ָ��
	//xsize				ͼ��Ŀ�
	//ysize				ͼ��ĸ�
	///////////////////////////////////////////////////////////////////*/
	for (int i = 0; i < ysize; i++)
	{
		for (int j = 0; j < xsize;j++)
		{
			if (*(image_in+i*xsize+j)<threshold)
			{
				*(image_out + i*xsize + j) = 255;
			}
			else
			{
				*(image_out + i*xsize + j) = 0;
			}
		}
	}
}

//��һ��ָ����ָ������ݸ�����һ��
void Image_To_Image(BYTE *image_des, BYTE *image_src, int Image_size)
{
/*////////////////////////////////////////////////////////////////////
// ���ߣ����
//�����б� 
//image_des			Ҫ���ı��ָ��
//image_src				ͼ���ָ��
//Image_size			ͼ���ж��ٸ����أ�8λͼ  
//��image_src��ָ������ݸ���image_des
////////////////////////////////////////////////////////////////////*/
	for (int i = 0; i < Image_size; i++)
	{
		*(image_des + i) = *(image_src + i);
	}
}

int cconc(int inb[9])
{
	int i, icn;
	icn = 0;
	for (i = 0; i < 8;i+=2)
	{
		if (inb[i]==0)
		{
			if (inb[i+1]==HIGH || inb[i+2]==HIGH)
			{
				icn++;
			}
		}
	}
	return icn;
}

//��ֵ��ͼ���ϸ��
void Thinning(BYTE *image_in, BYTE *image_out, int xsize, int ysize)
{
/*////////////////////////////////////////////////////////////////////
// ���ߣ����
//�����б� 
//image_in			����ͼ���ָ��
//image_out		���ͼ���ָ��
//xsize				ͼ��Ŀ�
//ysize				ͼ��ĸ�
////////////////////////////////////////////////////////////////////*/
	int ia[9], ic[9], i, ix, iy, m, ir, iv, iw;
	for (iy = 0; iy < ysize;iy++)
	{
		for (ix = 0; ix < xsize; ix++)
		{
			*(image_out + iy*xsize + ix) = *(image_in + iy*xsize + ix);
		}
	}
	m = 100;
	ir = 1;
	while (ir!=0)
	{
		ir = 0;
		for (iy = 1; iy < ysize-1; iy++)
		{
			for (ix = 1; ix < xsize - 1; ix++)
			{
				if (*(image_out + iy*xsize + ix) !=HIGH)
				{
					continue;
				}
				ia[0] = *(image_out + iy * xsize + ix + 1);
				ia[1] = *(image_out + (iy - 1)*xsize + ix + 1);
				ia[2] = *(image_out + (iy - 1)*xsize + ix);
				ia[3] = *(image_out + (iy - 1) *xsize + ix - 1);
				ia[4] = *(image_out + iy *xsize + ix - 1);
				ia[5] = *(image_out + (iy + 1)*xsize + ix - 1);
				ia[6] = *(image_out + (iy + 1)*xsize + ix);
				ia[7] = *(image_out + (iy + 1)*xsize + ix + 1);
				for (i = 0; i < 8;i++)
				{
					if (ia[i]==m)
					{
						ia[i] = HIGH;
						ic[i] = 0;
					}
					else
					{
						if (ia[i]<HIGH)
						{
							ia[i] = 0;
						}
						ic[i] = ia[i];
					}
				}
				ia[8] = ia[0];
				ic[8] = ic[0];
				if (ia[0]+ia[2]+ia[4]+ia[6]==HIGH*4)
				{
					continue;
				}
				for (i = 0, iv = 0, iw = 0; i < 8;i++)
				{
					if (ia[i]==HIGH)
					{
						iv++;
					}
					if (ic[i]==HIGH)
					{
						iw++;
					}
				}
				if (iv<=1)
				{
					continue;
				}
				if (iw==0)
				{
					continue;
				}
				if (cconc(ia)!=1)
				{
					continue;
				}
				if (*(image_out+(iy-1)*xsize+ix)==m)
				{
					ia[2] = 0;
					if (cconc(ia)!=1)
					{
						continue;
					}
					ia[2] = HIGH;
				}
				if (*(image_out + iy *xsize + ix-1) == m)
				{
					ia[4] = 0;
					if (cconc(ia)!=1)
					{
						continue;
					}
					ia[4] = HIGH;
				}
				*(image_out + iy*xsize + ix) = m;
				ir++;
			}
			
		}
		m++;
	}

	for (iy = 0; iy < ysize; iy++)
	{
		for (ix = 0; ix < xsize; ix++)
		{
			if (*(image_out + iy*xsize + ix)<HIGH)
			{
				*(image_out + iy*xsize + ix) = 0;
			}
		}
	}
}

//�ƶ�ƽ����
void Image_smooth(BYTE *image_in, BYTE *image_out, int xsize, int ysize)
{
	/*////////////////////////////////////////////////////////////////////
	// ���ߣ����
	//�����б�
	//image_in			����ͼ���ָ��
	//image_out		���ͼ���ָ��
	//xsize				ͼ��Ŀ�
	//ysize				ͼ��ĸ�
	////////////////////////////////////////////////////////////////////*/
	int i, j, buf;
	for (i = 1; i < ysize - 1;i++)
	{
		for (j = 1; j < xsize-1; j++)
		{
			buf = (int)(*(image_in + (i - 1)*xsize + j - 1)) + (int)(*(image_in + (i - 1)*xsize + j)) + (int)(*(image_in + (i - 1)*xsize + j + 1))
				+ (int)(*(image_in + i*xsize + j - 1)) + (int)(*(image_in + i *xsize + j)) + (int)(*(image_in + i*xsize + j + 1))
				+ (int)(*(image_in + (i + 1)*xsize + j - 1)) + (int)(*(image_in + (i + 1)*xsize + j)) + (int)(*(image_in + (i + 1)*xsize + j + 1));
			*(image_out + i*xsize + j) = (BYTE)(buf / 9);
		}
	}
}

//��ֵ�˲�
void Median(BYTE *image_in, BYTE *image_out, int xsize, int ysize)
{
	/*////////////////////////////////////////////////////////////////////
	// ���ߣ����
	//�����б�
	//image_in			����ͼ���ָ��
	//image_out		���ͼ���ָ��
	//xsize				ͼ��Ŀ�
	//ysize				ͼ��ĸ�
	////////////////////////////////////////////////////////////////////*/
	int i, j;
	unsigned char	c[9];
	for (j = 1; j < ysize - 1; j++)
	{
		for (i = 1; i < xsize - 1; i++)
		{
			c[0] = *(image_in + (j - 1)*xsize + i - 1);
			c[1] = *(image_in + (j - 1)*xsize + i);
			c[2] = *(image_in + (j - 1)*xsize + i + 1);
			c[3] = *(image_in + j *xsize + i - 1);
			c[4] = *(image_in + j *xsize + i);
			c[5] = *(image_in + j *xsize + i + 1);
			c[6] = *(image_in + (j + 1)*xsize + i - 1);
			c[7] = *(image_in + (j + 1)*xsize + i - 1);
			c[8] = *(image_in + (j + 1)*xsize + i - 1);
			*(image_out + j*xsize + i) = median_value(c);
		}
	}
}

//���������м�ֵ
int median_value(BYTE c[9])
{
	int i, j, buf;
	for (j = 0; j < 8;j++)
	{
		for (i = 0; i < 8;i++)
		{
			if (c[i+1]<c[i])
			{
				buf = c[i + 1];
				c[i + 1] = c[i];
				c[i] = buf;
			}
		}
	}
	return c[4];
}

//��ʴ����
void Erodible(BYTE *image_in, BYTE *image_out, int xsize, int ysize)
{
	/*////////////////////////////////////////////////////////////////////
	// ���ߣ����
	//�����б�
	//image_in			����ͼ���ָ��
	//image_out		���ͼ���ָ��
	//xsize				ͼ��Ŀ�
	//ysize				ͼ��ĸ�
	////////////////////////////////////////////////////////////////////*/
	int i, j;
	for (i = 1; i < ysize - 1;i++)
	{
		for (j = 1; j < xsize;j++)
		{
			*(image_out + i*xsize + j) = *(image_in + i*xsize + j);
			//�������Χ�˸�����һ���ǰ׵�ͱ��
			if (*(image_in + (i - 1)*xsize + j-1) == LOW)
				*(image_out + i*xsize + j) = LOW;
			if (*(image_in + (i - 1)*xsize + j) == LOW)
				*(image_out + i*xsize + j) = LOW;
			if (*(image_in + (i - 1)*xsize + j+1) == LOW)
				*(image_out + i*xsize + j) = LOW;
			if (*(image_in + i *xsize + j - 1) == LOW)
				*(image_out + i*xsize + j) = LOW;
			if (*(image_in + i *xsize + j + 1) == LOW)
				*(image_out + i*xsize + j) = LOW;
			if (*(image_in + (i + 1)*xsize + j) == LOW)
				*(image_out + i*xsize + j) = LOW;
			if (*(image_in + (i + 1)*xsize + j) == LOW)
				*(image_out + i*xsize + j) = LOW;
			if (*(image_in + (i + 1)*xsize + j) == LOW)
				*(image_out + i*xsize + j) = LOW;

		}
	}
}

//���ʹ���
void Dilation(BYTE *image_in, BYTE *image_out, int xsize, int ysize)
{
	/*////////////////////////////////////////////////////////////////////
	// ���ߣ����
	//�����б�
	//image_in			����ͼ���ָ��
	//image_out		���ͼ���ָ��
	//xsize				ͼ��Ŀ�
	//ysize				ͼ��ĸ�
	////////////////////////////////////////////////////////////////////*/
	int i, j;
	for (i = 1; i < ysize - 1; i++)
	{
		for (j = 1; j < xsize; j++)
		{
			*(image_out + i*xsize + j) = *(image_in + i*xsize + j);
			//�������Χ�˸�����һ���ǰ׵�ͱ��
			if (*(image_in + (i - 1)*xsize + j - 1) == HIGH)
				*(image_out + i*xsize + j) = HIGH;
			if (*(image_in + (i - 1)*xsize + j) == HIGH)
				*(image_out + i*xsize + j) = HIGH;
			if (*(image_in + (i - 1)*xsize + j + 1) == HIGH)
				*(image_out + i*xsize + j) = HIGH;
			if (*(image_in + i *xsize + j - 1) == HIGH)
				*(image_out + i*xsize + j) = HIGH;
			if (*(image_in + i *xsize + j + 1) == HIGH)
				*(image_out + i*xsize + j) = HIGH;
			if (*(image_in + (i + 1)*xsize + j) == HIGH)
				*(image_out + i*xsize + j) = HIGH;
			if (*(image_in + (i + 1)*xsize + j) == HIGH)
				*(image_out + i*xsize + j) = HIGH;
			if (*(image_in + (i + 1)*xsize + j) == HIGH)
				*(image_out + i*xsize + j) = HIGH;

		}
	}
}

//��ֵ�������ֵ������ֵ
void Mean_method(BYTE *image_in, BYTE *image_out, int xsize, int ysize)
{
	/*////////////////////////////////////////////////////////////////////
	// ���ߣ����
	//�����б�
	//image_in			����ͼ���ָ��
	//image_out		���ͼ���ָ��
	//xsize				ͼ��Ŀ�
	//ysize				ͼ��ĸ�
	////////////////////////////////////////////////////////////////////*/
	int sum = 0;
	int i, j, h, k;;//����ѭ��
	int T = 0;//��ֵ
	int num = 0;//�����Լ�
	int w_size = 7;//���ڴ�СΪ2*w_size+1
	int Area = (2 * w_size + 1)*(2 * w_size + 1);
	int *d = (int *)malloc(sizeof(int)*Area);//����ռ�

	for (j = w_size; j < ysize - w_size; j++)
	{
		for (i = w_size; i < xsize - w_size; i++)
		{
			sum = 0;
			num = 0;
			for (h = 0; h < 2 * w_size + 1; h++)
			{
				for (k = 0; k < 2 * w_size + 1; k++)
				{
					d[num++] = GetGray(image_in, xsize, i + w_size - k, j + w_size - h);
				}
			}
			for (h = 0; h < Area; h++)
			{
				sum += d[h];
			}
			T = sum / Area;
			*(image_out + j *xsize + i) = *(image_in + j *xsize + i) > T ? 255 : 0;
		}
	}
	free(d);
}
//����ĳ��ĻҶ�ֵ
int GetGray(BYTE * image_in, int xsize, int x, int y)
{
	return *(image_in + y *xsize + x);
}

//��ɫ��ת
void Back_White(BYTE *image_des, int image_size)
{
	for (int i = 0; i < image_size; i++)
	{
		if (*(image_des + i) == 0)
		{
			*(image_des + i) = 255;
		}
		else
		{
			*(image_des + i) = 0;
		}
	}
}

//NiBlack ģ����ֵ�ָ�
void NiBlack(BYTE *image_in, BYTE *image_out, int xsize, int ysize)
{
	/*////////////////////////////////////////////////////////////////////
	// ���ߣ����
	//�����б�
	//image_in			����ͼ���ָ��
	//image_out		���ͼ���ָ��
	//xsize				ͼ��Ŀ�
	//ysize				ͼ��ĸ�
	////////////////////////////////////////////////////////////////////*/

	int sum = 0;
	int i, j, h, k;;//����ѭ��
	int Average = 0;//ƽ��ֵ
	int num = 0;//�����Լ�
	int w_size = 7;//���ڴ�СΪ2*w_size+1
	int Area = (2 * w_size + 1)*(2 * w_size + 1);
	int *d = (int *)malloc(sizeof(int)*Area);//����ռ�
	int T = 0;//��ֵ
	int S = 0;//��׼��
	
	for (j = w_size; j < ysize - w_size; j++)
	{
		for (i = w_size; i < xsize - w_size; i++)
		{
			sum = 0;
			num = 0;
			for (h = 0; h < 2 * w_size + 1; h++)
			{
				for (k = 0; k < 2 * w_size + 1; k++)
				{
					d[num++] = GetGray(image_in, xsize, i + w_size - k, j + w_size - h);		//��area�����ڵ�����ֵ
				}
			}
			for (h = 0; h <Area; h++)
			{
				sum += d[h];//���ܺ�
			}
			Average = sum / Area;
			sum = 0;
			for (h = 0; h < Area; h++)
			{
				sum += (d[h] * d[h]);
			}
			S = sqrt((float)sum);
			S = S / Area;
 			T = Average + 0.05*S;//ȷ����ֵ
			*(image_out + j *xsize + i) = *(image_in + j *xsize + i) > T ? 255 : 0;
		}
	}
	free(d);

}