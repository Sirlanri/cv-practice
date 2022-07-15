/*�ռ�����ǿ*/
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/*ֱ��ͼ����*/
void histogramTrans()
{
	Mat srcImg, outImg,tempycrcb;
	string imgurl = "D:\\ͼƬ\\xhs\\XHS_16210051495193f56dd56-2e11-3660-97d7-07488a16fe7c.jpg";
	srcImg = imread(imgurl);

	//ɫ�ʿռ�ת��Ycrcb
	cvtColor(srcImg, tempycrcb, COLOR_BGR2YCrCb);
	vector<Mat>channels;
	split(tempycrcb, channels);
	//ֱ��ͼ���⻯
	equalizeHist(channels[0], channels[0]);
	merge(channels, tempycrcb);
	cvtColor(tempycrcb, outImg, COLOR_YCrCb2BGR);
	imshow("ֱ��ͼ����", outImg);
	waitKey();
	return;
}

/*ƽ���˲�*/
void smoothFilterTrans()
{
	Mat srcImg, medianImg,blurImg,boxblurImg;
	string imgurl = "C:\\my\\��ͼ\\QQ��ͼ20220715084643.jpg";
	srcImg = imread(imgurl);

	//�����˲�����
	boxFilter(srcImg, boxblurImg, -1, Size(7, 7));
	blur(srcImg, blurImg, Size(7, 7));
	imshow("�����˲�", boxblurImg);
	imshow("��ֵ�˲�", blurImg);

	//�������˲�����ֵ�˲�
	medianBlur(srcImg, medianImg, 7);
	imshow("��ֵ�˲�", medianImg);
	waitKey();
	return;
}