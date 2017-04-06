#pragma once 
#include "MyDib.h"
#include <math.h>

//一阶微分边缘检测
void Differential(BYTE *image_in, BYTE *image_out, int xsize, int ysize, float amp);

//二阶微分边缘检测
void Differential2(BYTE *image_in, BYTE *image_out, int xsize, int ysize, float amp);

//二值化
void Binary(BYTE *image_in, BYTE *image_out, int xsize, int ysize, int threshold = 100/*阈值*/);

//把一个指针所指向的内容赋给另一个
void Image_To_Image(BYTE *image_des, BYTE *image_src, int Image_size);

int cconc(int inb[9]);

//二值化图像的细化
void Thinning(BYTE *image_in, BYTE *image_out, int xsize, int ysize);

//移动平均法
void Image_smooth(BYTE *image_in, BYTE *image_out, int xsize, int ysize);

//中值滤波
void Median(BYTE *image_in, BYTE *image_out, int xsize, int ysize);

//返回数组中间值
int median_value(BYTE c[9]);

//腐蚀处理
void Erodible(BYTE *image_in, BYTE *image_out, int xsize, int ysize);

//膨胀处理
void Dilation(BYTE *image_in, BYTE *image_out, int xsize, int ysize);

//均值方法求二值化的阈值
void Mean_method(BYTE *image_in, BYTE *image_out, int xsize, int ysize);

//返回某点的灰度值
int GetGray(BYTE * image_in, int xsize, int x, int y);

//黑白变换
void Back_White(BYTE *image_des, int image_size);

void NiBlack(BYTE *image_in, BYTE *image_out, int xsize, int ysize);