#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;


/* ������Ķ�ȡ����ʾһ��ͼ��
�൱��CV���helloworld��*/
void readimg()
{
	String imgName("D:\\ͼƬ\\xhs\\XHS_1608302862803120701da-2ca7-3818-863c-4ec3e6bf44dc.jpg"); //��б�� ��Ҫת��
	Mat image;
	image = imread(imgName, IMREAD_COLOR);
	namedWindow("ricocooooo��͵��", WINDOW_AUTOSIZE);
	imshow("ricocooooo��͵��", image);
	waitKey(0);
	return;
}

