#pragma once 
#include "MyDib.h"
#include <math.h>

//һ��΢�ֱ�Ե���
void Differential(BYTE *image_in, BYTE *image_out, int xsize, int ysize, float amp);

//����΢�ֱ�Ե���
void Differential2(BYTE *image_in, BYTE *image_out, int xsize, int ysize, float amp);

//��ֵ��
void Binary(BYTE *image_in, BYTE *image_out, int xsize, int ysize, int threshold = 100/*��ֵ*/);

//��һ��ָ����ָ������ݸ�����һ��
void Image_To_Image(BYTE *image_des, BYTE *image_src, int Image_size);

int cconc(int inb[9]);

//��ֵ��ͼ���ϸ��
void Thinning(BYTE *image_in, BYTE *image_out, int xsize, int ysize);

//�ƶ�ƽ����
void Image_smooth(BYTE *image_in, BYTE *image_out, int xsize, int ysize);

//��ֵ�˲�
void Median(BYTE *image_in, BYTE *image_out, int xsize, int ysize);

//���������м�ֵ
int median_value(BYTE c[9]);

//��ʴ����
void Erodible(BYTE *image_in, BYTE *image_out, int xsize, int ysize);

//���ʹ���
void Dilation(BYTE *image_in, BYTE *image_out, int xsize, int ysize);

//��ֵ�������ֵ������ֵ
void Mean_method(BYTE *image_in, BYTE *image_out, int xsize, int ysize);

//����ĳ��ĻҶ�ֵ
int GetGray(BYTE * image_in, int xsize, int x, int y);

//�ڰױ任
void Back_White(BYTE *image_des, int image_size);

void NiBlack(BYTE *image_in, BYTE *image_out, int xsize, int ysize);