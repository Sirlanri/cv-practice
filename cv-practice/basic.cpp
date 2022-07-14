/*�Ҷȵ���ز���*/

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/*�Ҷȷ�ת*/
void greyTrans()
{
	Mat sourceimg, outimg, greyimg,verifyimg;
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

	//��֤
	verifyimg = greyimg.clone();
	for (int i = 0; i < greyimg.rows; i++)
	{
		for (int j = 0; j < greyimg.cols; j++)
		{
			//��������
			verifyimg.at<uchar>(i, j) = 255 - outimg.at<uchar>(i, j);
		}
	}
	imshow("verify", verifyimg);

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

/*ͼ���ƶ�*/
void moveTrans()
{
	string imgurl = "D:\\ͼƬ\\xhs\\XHS_16174260196810d6143e5-342a-357f-a0ee-ef27ce75ab46.jpg";
	Mat sourceImg, movedImg;
	sourceImg = imread(imgurl);

	//moveΪ�任����2��3�У�X��+25��Y��+30
	Mat move = (Mat_<double>(2, 3) << 1, 0, 25, 0, 1, 10);
	warpAffine(sourceImg, movedImg, move,sourceImg.size());
	imshow("�ƶ�", movedImg);
	waitKey();
	return;
}

/*ͼ����ת*/
void rotateTrans()
{
	string imgurl = "D:\\ͼƬ\\xhs\\XHS_16174260196810d6143e5-342a-357f-a0ee-ef27ce75ab46.jpg";
	Mat sourceImg, rotatedImg,rotate;
	sourceImg = imread(imgurl);
	//��ת���� ����Ϊ ���ĵ㡢��ת�Ƕȡ�ˮƽ������
	rotate = getRotationMatrix2D(Point((sourceImg.cols - 1) / 2, (sourceImg.rows - 1) / 2), 90, 1);
	warpAffine(sourceImg, rotatedImg, rotate, sourceImg.size());
	imshow("��ת", rotatedImg);
	waitKey();
	return;

}

/*��ת*/
void flipTrans()
{
	string imgurl = "D:\\ͼƬ\\xhs\\XHS_16174260196810d6143e5-342a-357f-a0ee-ef27ce75ab46.jpg";
	Mat sourceImg, outImg1,outImg2,outImg3;
	sourceImg = imread(imgurl);
	flip(sourceImg, outImg1, 0);
	flip(sourceImg, outImg2, 1);
	flip(sourceImg, outImg3, -1);
	imshow("���·�ת", outImg1);
	imshow("���ҷ�ת", outImg2);
	imshow("�Խ��߷�ת", outImg3);
	waitKey();
	return;
}

/*ת�ñ任*/
void posiTrans()
{
	string imgurl = "D:\\ͼƬ\\xhs\\XHS_16174260196810d6143e5-342a-357f-a0ee-ef27ce75ab46.jpg";
	Mat sourceImg, outImg;
	sourceImg = imread(imgurl);
	//XY�����ػ���
	transpose(sourceImg, outImg);
	imshow("ת�ñ任", outImg);
	waitKey();
	return;
}