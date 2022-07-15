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
	//ͨ������
	split(tempycrcb, channels);

	/*ֱ��ͼ���⻯
	��YCrBr��˵����һͨ�����������ݣ���ֱ��ͼֻ�����Ƚ��е���
	����ֻ��Ҫ������һ��ͨ��*/
	equalizeHist(channels[0], channels[0]);
	//�ϲ�ͨ��
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

	/*�����˲�����
	ddepth:ͼ����ȣ�-1��ʾͼ��ԭ��ȣ�ksizeΪ�ں˴�С*/
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

/*�ݶȷ���Ե���*/
void gradientDet()
{
	Mat srcImg, outImg;
	string imgurl = "C:\\my\\��ͼ\\QQ��ͼ20220715092337.jpg";
	srcImg = imread(imgurl);

	//��˹ģ��
	Mat blurImg;
	GaussianBlur(srcImg, blurImg, Size(3, 3),
		0, 0);
	//�Ҷȱ任
	Mat grayImg;
	cvtColor(blurImg, grayImg, COLOR_BGR2GRAY);

	//�����ݶ�
	Mat gradX, gradY;
	Sobel(grayImg, gradX, CV_16S, 1,0,3);
	Sobel(grayImg, gradY, CV_16S, 0, 1, 3);
	//�������ֵ��ת��Ϊ8bit ��ͼ��256λ��
	convertScaleAbs(gradX, gradX);
	convertScaleAbs(gradY, gradY);

	//���ͼ��
	Mat dst;
	addWeighted(gradX, 0.5, gradY, 0.5, 0, dst);
	//��
	imshow("���", dst);
	Mat gradXY = Mat(gradX.size(), gradX.type());
	for (int row = 0; row < gradX.rows; row++) {
		for (int col = 0; col < gradX.cols; col++) {
			int gX = gradX.at<uchar>(row, col);
			int gY = gradY.at<uchar>(row, col);
			//��ֹͼ������ͣ����߽з����������255��ֵ��ת��Ϊ255
			gradXY.at<uchar>(row, col) = saturate_cast<uchar>(gX + gY);
		}
	}
	imshow("GradXY", gradXY);
	waitKey();
	return;
}

/*������˹������*/
void lapDet()
{
	Mat srcImg, outImg;
	string imgurl = "C:\\my\\��ͼ\\QQ��ͼ20220715092337.jpg";
	srcImg = imread(imgurl);

	//��˹ģ��
	Mat blurImg;
	GaussianBlur(srcImg, blurImg, Size(3, 3),
		0, 0);
	//�Ҷȱ任
	Mat grayImg;
	cvtColor(blurImg, grayImg, COLOR_BGR2GRAY);

	//������˹��Ե���
	Laplacian(grayImg, outImg, CV_8U, 3
		, 1, 0, BORDER_DEFAULT);
	imshow("������˹", outImg);
	waitKey();
	return;
}

/*�Աȶ����죬���ȱ䰵ģʽ*/
void contrastLinerDet()
{
	Mat srcImg, outImg, tempRgbImg;
	string imgurl = "D:\\ͼƬ\\xhs\\XHS_16210051495193f56dd56-2e11-3660-97d7-07488a16fe7c.jpg";
	srcImg = imread(imgurl);

	//RGB���룬ÿ��ͨ����������
	vector<Mat>channels;
	split(srcImg, channels);

	//����ͨ���ֱ����
	for (int c = 0; c < 3; c++)
	{
		//X��
		for (int x = 0; x < channels[c].rows; x++)
		{	
			//Y��
			for (int y = 0; y < channels[c].cols; y++)
			{
				//�õ��ʼֵ
				uchar *num = &channels[c].at<uchar>(x, y);
				//���ȱ䰵
				*num = *num / 2;
			}
		}
	}

	//ͨ���ϲ�
	merge(channels, outImg);

	imshow("���ȱ䰵", outImg);
	waitKey();
	return;
}

/*����Ƭ���Ҷ���Ƭ�� 
������ֻ��������150-200������*/
void greySliceDet()
{
	Mat srcImg, outImg, tempImg;
	string imgurl = "D:\\ͼƬ\\xhs\\XHS_16210051495193f56dd56-2e11-3660-97d7-07488a16fe7c.jpg";
	srcImg = imread(imgurl);

	//RGBתYCrBr 
	//ܳ��������ֺ��Ѽǩc(�`_�`)��
	cvtColor(srcImg, tempImg, COLOR_RGB2YCrCb);
	//����ͨ��
	vector<Mat>channels;
	split(tempImg, channels);

	for (int i = 0; i < channels[0].rows; i++)
	{
		for (int j = 0; j < channels[0].cols; j++)
		{
			//�õ��ʼֵ
			uchar *num = &channels[0].at<uchar>(i,j);
			if (*num<150 || *num>200)
			{
				//������ȹ�С���������0
				*num = 0;
			}
			
		}
	}

	merge(channels, tempImg);
	cvtColor(tempImg, outImg, COLOR_YCrCb2RGB);
	imshow("�Ҷ���Ƭ", outImg);
	waitKey();
	return;
}