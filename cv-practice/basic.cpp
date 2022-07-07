/*�Ҷȵ���ز���*/

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/*�Ҷȷ�ת*/
void reverseGrey()
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
void logtrans()
{
	int c = 6;	//��ʽ�е�cֵ
	Mat sourceimg, outimg, greyimg;
	sourceimg = imread("D:\\ͼƬ\\xhs\\XHS_160584013425731f1cca6-eebf-3668-943d-e5c4ba28f3a0.jpg");
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