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
	String imgName("C:\\my\\��ͼ\\QQ��ͼ20220624190041.png"); //��б�� ��Ҫת��
	Mat image;
	image = imread(imgName, IMREAD_COLOR);
	namedWindow("ricocooooo��͵��", WINDOW_AUTOSIZE);
	imshow("ricocooooo��͵��", image);
	waitKey(0);
	return;
}

int main()
{
	readimg();
	return 0;
}