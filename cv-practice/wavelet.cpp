/*С���任��ش���*/

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/*HarrС���Ľ������ʽ*/
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

/*HarrС���ĳ߶Ⱥ���*/
int harrScale(float x)
{
	if (x>=0 && x<1)
	{
		return 1;
	}
	return 0;
}

/*С���任 ���ƺ���*/
void waveletTrans()
{
	Mat srcImg, outImg, transImg;
	//������PS����ͼ��256*256,8bit�Ҷ�ͼ
	srcImg = imread("E:\\������Ӿ�2.jpg");
	//��¡һ��Դͼ�񣬱��ڽ��жԱ�
	transImg = srcImg.clone();

	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			transImg.at<uchar>(i, j) = 0;
		}
	}
}