/*阈值分割相关函数*/

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//滑块的值
int value = 125;
//过程图和最终渲染出的图,TransImg不应该被修改
Mat TransImg,OutImg;
//直方图数据列表
int Hist[256];

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

/*半阈值化分割 执行函数，适用于白底
* 小于阈值的部分全部设置为0，剩下的像素值全部保留
* 与其他函数共享value和transImg，OutImg*/
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
	imshow("半阈值化", OutImg);
}

/*半阈值化分割 控制函数
* 和阈值化分割共享全局变量，不可同时调用两个函数
*/
void halfThres()
{
	Mat srcImg, grayImg;
	srcImg = imread("D:\\图片\\xhs\\XHS_1637717979603a0e53773-dbc0-393a-b102-4e27310656b5.jpg");
	cvtColor(srcImg, TransImg, COLOR_BGR2GRAY);
	OutImg = TransImg.clone();
	namedWindow("半阈值化");

	//创建输入滑块
	createTrackbar("灰度阈值", "半阈值化", &value, 255, halfThresDo);
	halfThresDo(125, NULL);
	imshow("半阈值化", TransImg);
	waitKey();
}

/*生成图像的直方图
* 传入Mat，返回数组，数组角标为[0,255]，值为其对应的数据
* 数组的形式为第一个int的指针（辣鸡C艹）
* 注：此函数存在问题，不可用，应使用generateHistogram2代替
*/
int * generateHistogram(Mat img)
{
	//hist即为所需的直方图数组
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

/*利用极大值和极小值寻找谷底及其阈值
* 适用于双峰形直方图
*/
void findThresByMaxMin()
{
	Mat srcImg, grayImg;
	srcImg = imread("E:\\opencv4.png",IMREAD_GRAYSCALE);
	int* hist = generateHistogram(srcImg);
	
	int maxnum=hist[0], minnum = 44, maxnum2 = 0, minindex = 0;
	for (int i = 1; i < 255; i++)
	{	
		//寻找局部极大值
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
		//寻找局部极小值
		if (hist[i]<minnum)
		{	
			minnum = hist[i];
			minindex = i;
		}
	}
	cout << "极大值为 " << maxnum << " " << maxnum2 << endl;
	cout << "极小值为 " << minnum << " 下标:" << minindex<<endl;

	//计算K
	int k = minnum / maxnum2;
	cout << "K: " << k << endl;
	return;
}

/*生成直方图，直接调用全局变量Hist*/
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

/*类二值图像阈值的选取 回调函数
* 白底黑字，灰度值大的（纸面）全部设置255，灰度值小（黑色文字）设置为0
*/
void binaryLikeThresDo(int,void* param)
{
	OutImg = TransImg.clone();

	//通过直方图数据，获取满足百分比的阈值
	int total = TransImg.cols * TransImg.rows;	//总像素数目
	int count = 0;	//记录已统计的数目
	int index=0; //记录阈值的下标
	double perValue = (double)value / 100;
	int pixNum = total * perValue;	//阈值以下的像素数应该大于pixNum
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
	imshow("类二值", OutImg);
}
/*类二值图像阈值的选取，控制函数
* 专门用于处理文本照片，通过手动调节滑块，控制文字占比，实时输出结果，选择最优解
*/
void binaryLikeThres()
{
	Mat srcImg, grayImg;
	srcImg = imread("C:\\my\\截图\\QQ图片20220817095728.jpg");
	cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
	TransImg = grayImg.clone();
	generateHistogram2(TransImg);
	namedWindow("类二值", WINDOW_AUTOSIZE);
	//创建滑块
	value = 50;
	createTrackbar("文字百分比", "类二值", &value, 100, binaryLikeThresDo);

	imshow("类二值", TransImg);
	waitKey();
}

/*迭代式阈值选取
* 首选获取直方图数组，然后计算灰度均值，随后不断迭代逼近
*/
void iterativeThres()
{
	Mat srcImg, grayImg;
	srcImg = imread("C:\\my\\截图\\QQ图片20220817095728.jpg");
	cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
	generateHistogram2(grayImg);
	int t=128;
	
	int oldt=0,u1,u2;
	//将t设置为初始阈值
	while (true)
	{	
		//u为总灰度数
		u1 = u2 = 0;
		//pix为像素数目
		int pix1=0 , pix2 = 0;
		for (int i = 0; i < 256; i++)
		{	
			if (i<=t)
			{
				//u1为小于阈值
				u1 += i * Hist[i];
				pix1 += Hist[i];
			}
			else
			{
				//u2为大于阈值的部分
				u2 += i * Hist[i];
				pix2 += Hist[i];
			}
		}
		
		//aveu为两个区域的平均灰度值，使用un的总灰度值/像素数
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

	cout << "阈值为：" << t << endl;
	return;
}