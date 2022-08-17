/*��ֵ�ָ���غ���*/

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//�����ֵ
int value = 125;
//����ͼ��������Ⱦ����ͼ,TransImg��Ӧ�ñ��޸�
Mat TransImg,OutImg;
//ֱ��ͼ�����б�
int Hist[256];

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
* ע���˺����������⣬�����ã�Ӧʹ��generateHistogram2����
*/
int * generateHistogram(Mat img)
{
	//hist��Ϊ�����ֱ��ͼ����
	int arr[256] = {};

	for (int i = 0; i < img.rows; i++)
	{	
		for (int j = 0; j < img.cols; j++)
		{	
			int pix = img.at<uchar>(i, j);
			arr[pix]++;
		}
	}
	return arr;
}

/*���ü���ֵ�ͼ�СֵѰ�ҹȵ׼�����ֵ
* ������˫����ֱ��ͼ
*/
void findThresByMaxMin()
{
	Mat srcImg, grayImg;
	srcImg = imread("E:\\opencv4.png",IMREAD_GRAYSCALE);
	int* hist = generateHistogram(srcImg);
	
	int maxnum=hist[0], minnum = 44, maxnum2 = 0, minindex = 0;
	for (int i = 1; i < 255; i++)
	{	
		//Ѱ�Ҿֲ�����ֵ
		if (hist[i]>hist[i-1] && hist[i]>hist[i+1])
		{
			if (maxnum<hist[i])
			{
				maxnum = hist[i];
			}
			else
			{
				if (maxnum2<hist[i])
				{
					maxnum2 = hist[i];
				}
			}
		}
		//Ѱ�Ҿֲ���Сֵ
		if (hist[i]<minnum)
		{	
			minnum = hist[i];
			minindex = i;
		}
	}
	cout << "����ֵΪ " << maxnum << " " << maxnum2 << endl;
	cout << "��СֵΪ " << minnum << " �±�:" << minindex<<endl;

	//����K
	int k = minnum / maxnum2;
	cout << "K: " << k << endl;
	return;
}

/*����ֱ��ͼ��ֱ�ӵ���ȫ�ֱ���Hist*/
void generateHistogram2(Mat img)
{
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			int pix = img.at<uchar>(i, j);
			Hist[pix]++;
		}
	}
}

/*���ֵͼ����ֵ��ѡȡ �ص�����
* �׵׺��֣��Ҷ�ֵ��ģ�ֽ�棩ȫ������255���Ҷ�ֵС����ɫ���֣�����Ϊ0
*/
void binaryLikeThresDo(int,void* param)
{
	OutImg = TransImg.clone();

	//ͨ��ֱ��ͼ���ݣ���ȡ����ٷֱȵ���ֵ
	int total = TransImg.cols * TransImg.rows;	//��������Ŀ
	int count = 0;	//��¼��ͳ�Ƶ���Ŀ
	int index=0; //��¼��ֵ���±�
	double perValue = (double)value / 100;
	int pixNum = total * perValue;	//��ֵ���µ�������Ӧ�ô���pixNum
	for (int i = 0; i < 256; i++)
	{	
		if (count>=pixNum)
		{
			index = i;
			break;
		}
		else
		{
			count += Hist[i];
		}
	}

	for (int i = 0; i < TransImg.rows; i++)
	{
		for (int j = 0; j < TransImg.cols; j++)
		{
			uchar pix = TransImg.at<uchar>(i, j);
			if (pix >= index)
			{
				OutImg.at<uchar>(i, j) = 255;
			}
			else
			{
				OutImg.at<uchar>(i, j) = 0;
			}
		}
	}
	imshow("���ֵ", OutImg);
}
/*���ֵͼ����ֵ��ѡȡ�����ƺ���
* ר�����ڴ����ı���Ƭ��ͨ���ֶ����ڻ��飬��������ռ�ȣ�ʵʱ��������ѡ�����Ž�
*/
void binaryLikeThres()
{
	Mat srcImg, grayImg;
	srcImg = imread("C:\\my\\��ͼ\\QQͼƬ20220817095728.jpg");
	cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
	TransImg = grayImg.clone();
	generateHistogram2(TransImg);
	namedWindow("���ֵ", WINDOW_AUTOSIZE);
	//��������
	value = 50;
	createTrackbar("���ְٷֱ�", "���ֵ", &value, 100, binaryLikeThresDo);

	imshow("���ֵ", TransImg);
	waitKey();
}

/*����ʽ��ֵѡȡ
* ��ѡ��ȡֱ��ͼ���飬Ȼ�����ҶȾ�ֵ����󲻶ϵ����ƽ�
*/
void iterativeThres()
{
	Mat srcImg, grayImg;
	srcImg = imread("C:\\my\\��ͼ\\QQͼƬ20220817095728.jpg");
	cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
	generateHistogram2(grayImg);
	int t=128;
	
	int oldt=0,u1,u2;
	//��t����Ϊ��ʼ��ֵ
	while (true)
	{	
		//uΪ�ܻҶ���
		u1 = u2 = 0;
		//pixΪ������Ŀ
		int pix1=0 , pix2 = 0;
		for (int i = 0; i < 256; i++)
		{	
			if (i<=t)
			{
				//u1ΪС����ֵ
				u1 += i * Hist[i];
				pix1 += Hist[i];
			}
			else
			{
				//u2Ϊ������ֵ�Ĳ���
				u2 += i * Hist[i];
				pix2 += Hist[i];
			}
		}
		
		//aveuΪ���������ƽ���Ҷ�ֵ��ʹ��un���ܻҶ�ֵ/������
		int aveu1 = u1 / pix1;
		int aveu2 = u2 / pix2;
		t = (aveu1+	aveu2 )/ 2;
		if (oldt==t)
		{
			break;
		}
		else 
		{
			oldt = t;
		}
	}

	cout << "��ֵΪ��" << t << endl;
	return;
}