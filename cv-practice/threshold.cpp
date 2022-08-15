/*阈值分割相关函数*/

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//滑块的值
int value = 125;
//过程图和最终渲染出的图,TransImg不应该被修改
Mat TransImg,OutImg;

/*阈值化分割，执行函数，适用于白底*/
void singleThresDo(int,void* param)
{
	for (int i = 0; i < TransImg.rows; i++)
	{
		for (int j = 0; j < TransImg.cols; j++)
		{
			uchar pix = TransImg.at<uchar>(i, j);
			if (pix>=value)
			{	
				OutImg.at<uchar>(i,j) = 255;
			}
			else
			{
				OutImg.at<uchar>(i, j) = 0;
			}
		}
	}
	imshow("阈值化", OutImg);
}

/*最简单的阈值化分割 只分割一次，阈值滑块输入*/
void singleThres()
{
	Mat srcImg, grayImg;
	srcImg = imread("D:\\图片\\xhs\\XHS_1637717979603a0e53773-dbc0-393a-b102-4e27310656b5.jpg");
	cvtColor(srcImg, TransImg, COLOR_BGR2GRAY);
	OutImg = TransImg.clone();
	namedWindow("阈值化");
	
	//创建输入滑块
	createTrackbar("灰度阈值", "阈值化", &value, 255, singleThresDo);
	singleThresDo(125,NULL);
	imshow("阈值化", TransImg);
	waitKey();
}