/*阈值分割相关函数*/

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//滑块的值
int value = 125;
//过程图和最终渲染出的图,TransImg不应该被修改
Mat TransImg,OutImg;

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
*/
int * generateHistogram(Mat img)
{
	//hist即为所需的直方图数组
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