/*小波变换相关代码*/

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/*Harr小波的解析表达式*/
int harrExpress(float x)
{
	if (x>=0 && x<0.5)
	{
		return 1;
	}
	if (x>=0.5 && x<1)
	{	
		return -1;
	}
	return 0;
}

/*Harr小波的尺度函数*/
int harrScale(float x)
{
	if (x>=0 && x<1)
	{
		return 1;
	}
	return 0;
}
