/*空间域增强*/
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/*直方图均衡*/
void histogramTrans()
{
	Mat srcImg, outImg,tempycrcb;
	string imgurl = "D:\\图片\\xhs\\XHS_16210051495193f56dd56-2e11-3660-97d7-07488a16fe7c.jpg";
	srcImg = imread(imgurl);

	//色彩空间转换Ycrcb
	cvtColor(srcImg, tempycrcb, COLOR_BGR2YCrCb);
	vector<Mat>channels;
	split(tempycrcb, channels);
	//直方图均衡化
	equalizeHist(channels[0], channels[0]);
	merge(channels, tempycrcb);
	cvtColor(tempycrcb, outImg, COLOR_YCrCb2BGR);
	imshow("直方图均衡", outImg);
	waitKey();
	return;
}

/*平滑滤波*/
void smoothFilterTrans()
{
	Mat srcImg, medianImg,blurImg,boxblurImg;
	string imgurl = "C:\\my\\截图\\QQ截图20220715084643.jpg";
	srcImg = imread(imgurl);

	//线性滤波操作
	boxFilter(srcImg, boxblurImg, -1, Size(7, 7));
	blur(srcImg, blurImg, Size(7, 7));
	imshow("方框滤波", boxblurImg);
	imshow("均值滤波", blurImg);

	//非线性滤波：中值滤波
	medianBlur(srcImg, medianImg, 7);
	imshow("中值滤波", medianImg);
	waitKey();
	return;
}