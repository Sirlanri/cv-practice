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