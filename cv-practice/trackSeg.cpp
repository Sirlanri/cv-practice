/*���ڸ��ٵ�ͼ��ָ�*/

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/*�������ٷ����׵׺��Ѱ�ұ�Ե����
*/
void trackEdge()
{
	Mat srcImg, outImg;
	srcImg = imread("C:\\my\\��ͼ\\QQ��ͼ20220818132857.jpg", IMREAD_GRAYSCALE);

	bool edgeFlag = false;
	
	int x, y;	//��ǰ������λ��
	//Ѱ�������Ե
	for (int i = 0; i < srcImg.rows; i++)
	{
		if (edgeFlag)
		{
			//��⵽���壬����ѭ��
			break;
		}
		for (int j = 0; j < srcImg.cols; j++)
		{
			uchar pix = srcImg.at<uchar>(i, j);
			if (pix <= 100)
			{
				//��⵽��ɫ��
				edgeFlag = true;
				x = i;
				y = j;
			}
			if (edgeFlag)
			{
				//��⵽���壬����ѭ��
				break;
			}
		}
	}

	//������·��
	int routerX[10000],routerY[10000],index=0;
	//����һ�������·���б�
	routerX[0] = x;
	routerY[0] = y;
	//��һ���߹���ɫ���Ƿ�Ϊ��ɫ
	bool lastWhite = false;
	while (true)
	{	
		int oldX = routerX[index];
		int oldY = routerY[index];
		if (lastWhite)
		{	
			//��ת
			//��ǰ������
			if (true)
			{

			}
		}
		else
		{
			//��ת
		}
	}
}

/*��դ�����㷨 
* �Կα�����Ϊ����Դ
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
	int out[8][10]{};

	//�����ֵ
	int d = 7;
	//������ֵ
	int t = 4;

	//��һ��ɨ�裬�����ڼ����ֵ�ĵ���������
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j < 10; j++)
		{	
			if (src[i][j]>=d)
			{	
				out[i][j] = 1;
			}
		}
	}

	//�ڶ���ɨ�裬���Ҹ�����ֵ��
	for (int i = 0; i <= 6; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (out[i][j] == 1)
			{
				//������һ�ж�Ӧ������λ��
				for (int k = -1; k <= 1; k++)
				{	
					//��ֹ���������
					if (j+k>=10)
					{
						break;
					}
					if (src[i+1][j+k]>=t)
					{
						out[i + 1][j+k] = 1;
					}
				}
			}
		}
	}

	//һ��һ��������
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (out[i][j]==1)
			{
				cout << src[i][j] << " ";
			}
		}
		cout << endl;
	}
	return;
}