/*基于跟踪的图像分割*/

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/*轮廓跟踪法，白底黑物，寻找边缘轮廓
*/
void trackEdge()
{
	Mat srcImg, outImg;
	srcImg = imread("C:\\my\\截图\\QQ截图20220818132857.jpg", IMREAD_GRAYSCALE);

	bool edgeFlag = false;
	
	int x, y;	//当前的坐标位置
	//寻找物体边缘
	for (int i = 0; i < srcImg.rows; i++)
	{
		if (edgeFlag)
		{
			//检测到物体，跳出循环
			break;
		}
		for (int j = 0; j < srcImg.cols; j++)
		{
			uchar pix = srcImg.at<uchar>(i, j);
			if (pix <= 100)
			{
				//检测到黑色点
				edgeFlag = true;
				x = i;
				y = j;
			}
			if (edgeFlag)
			{
				//检测到物体，跳出循环
				break;
			}
		}
	}

	//轮廓的路径
	int routerX[10000],routerY[10000],index=0;
	//将第一个点存入路径列表
	routerX[0] = x;
	routerY[0] = y;
	//上一个走过的色块是否为白色
	bool lastWhite = false;
	while (true)
	{	
		int oldX = routerX[index];
		int oldY = routerY[index];
		if (lastWhite)
		{	
			//左转
			//当前方向左
			if (true)
			{

			}
		}
		else
		{
			//右转
		}
	}
}