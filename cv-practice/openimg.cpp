#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

/* 最基础的读取，显示一张图像
相当于CV里的helloworld？*/
void readimg()
{
	String imgName("C:\\my\\截图\\QQ截图20220624190041.png"); //反斜杠 需要转义
	Mat image;
	image = imread(imgName, IMREAD_COLOR);
	namedWindow("ricocooooo的偷拍", WINDOW_AUTOSIZE);
	imshow("ricocooooo的偷拍", image);
	waitKey(0);
	return;
}

int main()
{
	readimg();
	return 0;
}