/*小波变换相关代码*/

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/*Harr小波的解析表达式*/
int harrExpress(float x)
{
	if (x>=0 && x<0.5)
	{
		return 1;
	}
	if (x>=0.5 && x<1)
	{	
		return -1;
	}
	return 0;
}

/*Harr小波的尺度函数*/
int harrScale(float x)
{
	if (x>=0 && x<1)
	{
		return 1;
	}
	return 0;
}

/*小波变换 控制函数*/
void waveletTrans()
{
	Mat srcImg, outImg, transImg;
	//特意用PS做的图，256*256,8bit灰度图
	srcImg = imread("E:\\计算机视觉2.jpg");
	//克隆一下源图像，便于进行对比
	transImg = srcImg.clone();

	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			transImg.at<uchar>(i, j) = 0;
		}
	}
}