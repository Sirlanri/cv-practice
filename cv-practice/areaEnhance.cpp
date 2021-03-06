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
	//通道分离
	split(tempycrcb, channels);

	/*直方图均衡化
	对YCrBr来说，第一通道是亮度数据，本直方图只对亮度进行调整
	所以只需要操作第一个通道*/
	equalizeHist(channels[0], channels[0]);
	//合并通道
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

	/*线性滤波操作
	ddepth:图像深度，-1表示图像原深度，ksize为内核大小*/
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

/*梯度法边缘检测*/
void gradientDet()
{
	Mat srcImg, outImg;
	string imgurl = "C:\\my\\截图\\QQ截图20220715092337.jpg";
	srcImg = imread(imgurl);

	//高斯模糊
	Mat blurImg;
	GaussianBlur(srcImg, blurImg, Size(3, 3),
		0, 0);
	//灰度变换
	Mat grayImg;
	cvtColor(blurImg, grayImg, COLOR_BGR2GRAY);

	//求方向梯度
	Mat gradX, gradY;
	Sobel(grayImg, gradX, CV_16S, 1,0,3);
	Sobel(grayImg, gradY, CV_16S, 0, 1, 3);
	//计算绝对值并转换为8bit （图像256位）
	convertScaleAbs(gradX, gradX);
	convertScaleAbs(gradY, gradY);

	//混合图像
	Mat dst;
	addWeighted(gradX, 0.5, gradY, 0.5, 0, dst);
	//？
	imshow("混合", dst);
	Mat gradXY = Mat(gradX.size(), gradX.type());
	for (int row = 0; row < gradX.rows; row++) {
		for (int col = 0; col < gradX.cols; col++) {
			int gX = gradX.at<uchar>(row, col);
			int gY = gradY.at<uchar>(row, col);
			//防止图像过饱和，或者叫防溢出？超过255的值都转换为255
			gradXY.at<uchar>(row, col) = saturate_cast<uchar>(gX + gY);
		}
	}
	imshow("GradXY", gradXY);
	waitKey();
	return;
}

/*拉普拉斯算子锐化*/
void lapDet()
{
	Mat srcImg, outImg;
	string imgurl = "C:\\my\\截图\\QQ截图20220715092337.jpg";
	srcImg = imread(imgurl);

	//高斯模糊
	Mat blurImg;
	GaussianBlur(srcImg, blurImg, Size(3, 3),
		0, 0);
	//灰度变换
	Mat grayImg;
	cvtColor(blurImg, grayImg, COLOR_BGR2GRAY);

	//拉普拉斯边缘检测
	Laplacian(grayImg, outImg, CV_8U, 3
		, 1, 0, BORDER_DEFAULT);
	imshow("拉普拉斯", outImg);
	waitKey();
	return;
}

/*对比度拉伸，均匀变暗模式*/
void contrastLinerDet()
{
	Mat srcImg, outImg, tempRgbImg;
	string imgurl = "D:\\图片\\xhs\\XHS_16210051495193f56dd56-2e11-3660-97d7-07488a16fe7c.jpg";
	srcImg = imread(imgurl);

	//RGB分离，每个通道单独处理
	vector<Mat>channels;
	split(srcImg, channels);

	//三个通道分别遍历
	for (int c = 0; c < 3; c++)
	{
		//X轴
		for (int x = 0; x < channels[c].rows; x++)
		{	
			//Y轴
			for (int y = 0; y < channels[c].cols; y++)
			{
				//该点初始值
				uchar *num = &channels[c].at<uchar>(x, y);
				//均匀变暗
				*num = *num / 2;
			}
		}
	}

	//通道合并
	merge(channels, outImg);

	imshow("均匀变暗", outImg);
	waitKey();
	return;
}

/*窗切片（灰度切片） 
本函数只保留亮度150-200的像素*/
void greySliceDet()
{
	Mat srcImg, outImg, tempImg;
	string imgurl = "D:\\图片\\xhs\\XHS_16210051495193f56dd56-2e11-3660-97d7-07488a16fe7c.jpg";
	srcImg = imread(imgurl);

	//RGB转YCrBr 
	//艹这个破名字好难记ヽ(ー_ー)ノ
	cvtColor(srcImg, tempImg, COLOR_RGB2YCrCb);
	//分离通道
	vector<Mat>channels;
	split(tempImg, channels);

	for (int i = 0; i < channels[0].rows; i++)
	{
		for (int j = 0; j < channels[0].cols; j++)
		{
			//该点初始值
			uchar *num = &channels[0].at<uchar>(i,j);
			if (*num<150 || *num>200)
			{
				//如果亮度过小或过大，则变成0
				*num = 0;
			}
			
		}
	}

	merge(channels, tempImg);
	cvtColor(tempImg, outImg, COLOR_YCrCb2RGB);
	imshow("灰度切片", outImg);
	waitKey();
	return;
}