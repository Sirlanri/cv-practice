/*��ֵ�ָ���غ���*/

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//�����ֵ
int value = 125;
//����ͼ��������Ⱦ����ͼ,TransImg��Ӧ�ñ��޸�
Mat TransImg,OutImg;

/*��ֵ���ָִ�к���*/
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
	imshow("��ֵ��", OutImg);
}

/*��򵥵���ֵ���ָ� ֻ�ָ�һ��*/
void singleThres()
{
	Mat srcImg, grayImg;
	srcImg = imread("C:\\my\\��ͼ\\QQ��ͼ20220715092337.jpg");
	cvtColor(srcImg, TransImg, COLOR_BGR2GRAY);
	OutImg = TransImg.clone();
	namedWindow("��ֵ��");
	

	//�������뻬��
	createTrackbar("�Ҷ���ֵ", "��ֵ��", &value, 255, singleThresDo);
	singleThresDo(125,NULL);
	imshow("��ֵ��", TransImg);
	waitKey();
}