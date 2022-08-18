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

/*光栅跟踪算法 
* 以课本例题为数据源
*/
void rasterTracking()
{
	int src[8][10] = {
		{9,2,5,0,0,8,4,5,0,3},
		{0,5,0,3,0,0,6,4,2,0},
		{3,0,9,1,1,0,5,0,5,0},
		{6,0,0,5,0,4,0,7,0,2},
		{0,3,0,6,2,0,0,9,3,7},
		{4,0,6,0,3,0,5,3,0,5},
		{2,0,5,0,2,0,6,2,6,0},
		{6,4,0,3,0,2,7,3,4,2}
	};
	int out[8][10];

	//检测阈值
	int d = 7;
	//跟踪阈值
	int t = 4;

	//高于检测阈值的点坐标
	int detectPoints[20][2];
	int index = 0;
	//第一次扫描，将大于检测阈值的点加入队列中
	cout << "检测点为：";
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 10; j++)
		{	
			if (src[i][j]>=d)
			{	
				cout<<"检测点" << src[i][j] << endl;
				detectPoints[index][0] = i;
				detectPoints[index][1] = j;

				bool flag = true;
				while (flag)
				{	
					//寻找跟踪阈值点
					for (int k = -1; k <= 1; k++)
					{
						if (src[i + 1][j + k] >= t)
						{
							cout
						}
					}
				}

				
			}
		}
	}

	//第二次扫描，查找跟踪阈值点
	int trackPoints[50][2];
	index = 0;

}