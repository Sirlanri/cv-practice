/*灰度的相关操作*/

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/*灰度反转*/
void greyTrans()
{
	Mat sourceimg, outimg, greyimg;
	sourceimg = imread("D:\\图片\\xhs\\XHS_1608302862803120701da-2ca7-3818-863c-4ec3e6bf44dc.jpg");
	if (sourceimg.empty())
	{
		cout << "读取错误" << endl;
		return ;
	}
	//显示原图
	imshow("source", sourceimg);

	//灰度化
	cvtColor(sourceimg, greyimg, COLOR_BGR2GRAY);
	imshow("灰色", greyimg);

	//反转
	outimg = greyimg.clone();
	for (int i = 0; i < greyimg.rows; i++)
	{
		for (int j = 0; j < greyimg.cols; j++)
		{
			//操作像素
			outimg.at<uchar>(i, j) = 255 - greyimg.at<uchar>(i, j);
		}
	}
	imshow("out", outimg);

	waitKey(0);
	return;

}

/*对数变换 s=c*log(1+r)*/
void logTrans()
{
	int c = 10;	//公式中的c值
	Mat sourceimg, outimg, greyimg;
	sourceimg = imread("D:\\图片\\xhs\\XHS_164492201799301022f01kj447s26nyy010s7n4i0mnf46a.jpg");
	if (sourceimg.empty())
	{
		cout << "读取错误" << endl;
		return;
	}
	//显示原图
	imshow("source", sourceimg);

	//灰度化
	cvtColor(sourceimg, greyimg, COLOR_BGR2GRAY);
	//imshow("灰色", greyimg);

	outimg = greyimg.clone();
	for (int i = 0; i < greyimg.rows; i++)
	{
		for (int j = 0; j < greyimg.cols; j++)
		{
			//操作像素 公式 s=c*log(1+r)
			int r = greyimg.at<uchar>(i, j);
			outimg.at<uchar>(i, j) = c * log((double)(r+1));
		}
	}
	imshow("out", outimg);
	waitKey(0);
}

/*图像相减*/
void subtractTrans()
{
	Mat backimg, frontimg,resimg;
	backimg = imread("C:\\my\\截图\\20220707142927.png");
	frontimg = imread("C:\\my\\截图\\20220707142913.png");
	//检测长宽
	if (backimg.rows!=frontimg.rows||backimg.cols!=frontimg.cols)
	{	
		cout << "图片长宽不合" << endl;
		return;
	}

	absdiff(frontimg, backimg, resimg);
	imshow("刻晴", resimg);
	
	waitKey();
	return;

}