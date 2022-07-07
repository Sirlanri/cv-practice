/*�Ҷȵ���ز���*/

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/*�Ҷȷ�ת*/
void greyTrans()
{
	Mat sourceimg, outimg, greyimg;
	sourceimg = imread("D:\\ͼƬ\\xhs\\XHS_1608302862803120701da-2ca7-3818-863c-4ec3e6bf44dc.jpg");
	if (sourceimg.empty())
	{
		cout << "��ȡ����" << endl;
		return ;
	}
	//��ʾԭͼ
	imshow("source", sourceimg);

	//�ҶȻ�
	cvtColor(sourceimg, greyimg, COLOR_BGR2GRAY);
	imshow("��ɫ", greyimg);

	//��ת
	outimg = greyimg.clone();
	for (int i = 0; i < greyimg.rows; i++)
	{
		for (int j = 0; j < greyimg.cols; j++)
		{
			//��������
			outimg.at<uchar>(i, j) = 255 - greyimg.at<uchar>(i, j);
		}
	}
	imshow("out", outimg);

	waitKey(0);
	return;

}

/*�����任 s=c*log(1+r)*/
void logTrans()
{
	int c = 10;	//��ʽ�е�cֵ
	Mat sourceimg, outimg, greyimg;
	sourceimg = imread("D:\\ͼƬ\\xhs\\XHS_164492201799301022f01kj447s26nyy010s7n4i0mnf46a.jpg");
	if (sourceimg.empty())
	{
		cout << "��ȡ����" << endl;
		return;
	}
	//��ʾԭͼ
	imshow("source", sourceimg);

	//�ҶȻ�
	cvtColor(sourceimg, greyimg, COLOR_BGR2GRAY);
	//imshow("��ɫ", greyimg);

	outimg = greyimg.clone();
	for (int i = 0; i < greyimg.rows; i++)
	{
		for (int j = 0; j < greyimg.cols; j++)
		{
			//�������� ��ʽ s=c*log(1+r)
			int r = greyimg.at<uchar>(i, j);
			outimg.at<uchar>(i, j) = c * log((double)(r+1));
		}
	}
	imshow("out", outimg);
	waitKey(0);
}

/*ͼ�����*/
void subtractTrans()
{
	Mat backimg, frontimg,resimg;
	backimg = imread("C:\\my\\��ͼ\\20220707142927.png");
	frontimg = imread("C:\\my\\��ͼ\\20220707142913.png");
	//��ⳤ��
	if (backimg.rows!=frontimg.rows||backimg.cols!=frontimg.cols)
	{	
		cout << "ͼƬ������" << endl;
		return;
	}

	absdiff(frontimg, backimg, resimg);
	imshow("����", resimg);
	
	waitKey();
	return;

}