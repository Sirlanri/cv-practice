/*灰度的相关操作*/

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/*灰度反转*/
void reverseGrey()
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