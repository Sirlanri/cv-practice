/*С���任��ش���*/

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/*HarrС���Ľ������ʽ*/
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

/*HarrС���ĳ߶Ⱥ���*/
int harrScale(float x)
{
	if (x>=0 && x<1)
	{
		return 1;
	}
	return 0;
}
