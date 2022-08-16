/*��ֵ�ָ���غ���*/

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//�����ֵ
int value = 125;
//����ͼ��������Ⱦ����ͼ,TransImg��Ӧ�ñ��޸�
Mat TransImg,OutImg;

/*��ֵ���ָִ�к����������ڰ׵�*/
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

/*��򵥵���ֵ���ָ� ֻ�ָ�һ�Σ���ֵ��������*/
void singleThres()
{
	Mat srcImg, grayImg;
	srcImg = imread("D:\\ͼƬ\\xhs\\XHS_1637717979603a0e53773-dbc0-393a-b102-4e27310656b5.jpg");
	cvtColor(srcImg, TransImg, COLOR_BGR2GRAY);
	OutImg = TransImg.clone();
	namedWindow("��ֵ��");
	
	//�������뻬��
	createTrackbar("�Ҷ���ֵ", "��ֵ��", &value, 255, singleThresDo);
	singleThresDo(125,NULL);
	imshow("��ֵ��", TransImg);
	waitKey();
}

/*����ֵ���ָ� ִ�к����������ڰ׵�
* С����ֵ�Ĳ���ȫ������Ϊ0��ʣ�µ�����ֵȫ������
* ��������������value��transImg��OutImg*/
void halfThresDo(int, void* param)
{
	for (int i = 0; i < TransImg.rows; i++)
	{
		for (int j = 0; j < TransImg.cols; j++)
		{
			uchar pix = TransImg.at<uchar>(i, j);
			if (pix >= value)
			{
				OutImg.at<uchar>(i, j) = 255;
			}
			else
			{
				OutImg.at<uchar>(i, j) = pix;
			}
		}
	}
	imshow("����ֵ��", OutImg);
}

/*����ֵ���ָ� ���ƺ���
* ����ֵ���ָ��ȫ�ֱ���������ͬʱ������������
*/
void halfThres()
{
	Mat srcImg, grayImg;
	srcImg = imread("D:\\ͼƬ\\xhs\\XHS_1637717979603a0e53773-dbc0-393a-b102-4e27310656b5.jpg");
	cvtColor(srcImg, TransImg, COLOR_BGR2GRAY);
	OutImg = TransImg.clone();
	namedWindow("����ֵ��");

	//�������뻬��
	createTrackbar("�Ҷ���ֵ", "����ֵ��", &value, 255, halfThresDo);
	halfThresDo(125, NULL);
	imshow("����ֵ��", TransImg);
	waitKey();
}

/*����ͼ���ֱ��ͼ
* ����Mat���������飬����Ǳ�Ϊ[0,255]��ֵΪ���Ӧ������
* �������ʽΪ��һ��int��ָ�루����Cܳ��
*/
int * generateHistogram(Mat img)
{
	//hist��Ϊ�����ֱ��ͼ����
	//int (*hist)= new int[256];
	//cout << *hist << endl;
	int arr[256] = {};
	int (*hist) = arr;

	for (int i = 0; i < img.rows; i++)
	{	
		for (int j = 0; j < img.cols; j++)
		{	
			int pix = img.at<uchar>(i, j);
			arr[pix]++;
		}
	}
	return hist;
}

/*���ü���ֵ�ͼ�СֵѰ�ҹȵ׼�����ֵ
* ������˫����ֱ��ͼ
*/
void findThresByMaxMin()
{
	Mat srcImg, grayImg;
	srcImg = imread("E:\\opencv4.png");
	int* hist = generateHistogram(srcImg);

}