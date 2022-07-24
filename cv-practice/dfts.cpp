/*����Ҷ����㷨*/
#include<opencv2/opencv.hpp>
#include<cmath>

using namespace cv;


void ricodft(Mat& srcImg, Mat& outImg, Mat& transImg);

/*����ͨ��dft�㷨 ���ò���*/
void normal_dft()
{
	Mat srcImg, grayImg, outImg,transImg;
	srcImg = imread("C:\\my\\��ͼ\\QQ��ͼ20220715092337.jpg");
	cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);
	//���ò���
	ricodft(grayImg, outImg, transImg);

	//��ʾ
	imshow("��ɫͼ", grayImg);
	imshow("����Ҷ", outImg);
	waitKey();

}

/*�Զ��帵��Ҷ�㷨
* ��ʵ��һ�ο������±Ƶ� <���أ�>
@param srcImg Դͼ��
@param outImg ���ͼ��
@param transImg �任ͼ��
*/
void ricodft(Mat& srcImg, Mat& outImg, Mat& transImg)
{	/*���ִ��η�ʽ�����Ա�֤�޸ĵ�������Ĳ���*/

	//1.��չͼ�����Ϊ2��3��5�ı���ʱ�����ٶȿ�
	//???Ϊɶ������
	
	//�˺������ظ��������ߴ羭��DFT�任���������ųߴ��С
	int m = getOptimalDFTSize(srcImg.rows);
	int n = getOptimalDFTSize(srcImg.cols);
	copyMakeBorder(srcImg, srcImg, 0, m - srcImg.rows, 0, n - srcImg.cols, BORDER_CONSTANT, Scalar::all(0));

	//2.˫ͨ������planes���������渴����ʵ�����鲿
	Mat planes[] = { Mat_<float>(srcImg), Mat::zeros(srcImg.size(), CV_32F) };

	//3.�Ӷ����ͨ�������д���һ����ͨ������:transImg��
	//����Merge����������ϲ�Ϊһ����ͨ�����У�����������ÿ��Ԫ�ؽ�����������Ԫ�صļ���
	merge(planes, 2, transImg);

	//4.���и���Ҷ�任
	dft(transImg, transImg);

	//5.���㸴���ķ�ֵ
	split(transImg, planes); // ��˫ͨ����Ϊ������ͨ����һ����ʾʵ����һ����ʾ�鲿
	magnitude(planes[0], planes[1], outImg); //���㸴���ķ�ֵ��������outImg��Ƶ��ͼ��

	//6.ǰ��õ���Ƶ��ͼ�������󣬲�����ʾ�����ת��
	outImg += Scalar(1);   // ȡ����ǰ�����е����ض���1����ֹlog0
	log(outImg, outImg);   // ȡ����
	normalize(outImg, outImg, 0, 1, NORM_MINMAX); //��һ��

	//7.���к��طֲ�����ͼ����
	//����д������أ���û����
	outImg = outImg(Rect(0, 0, outImg.cols & -2, outImg.rows & -2));

	// �������и���Ҷͼ���е����ޣ�ʹԭ��λ��ͼ������
	int cx = outImg.cols / 2;
	int cy = outImg.rows / 2;
	Mat q0(outImg, Rect(0, 0, cx, cy));   // ��������
	Mat q1(outImg, Rect(cx, 0, cx, cy));  // ��������
	Mat q2(outImg, Rect(0, cy, cx, cy));  // ��������
	Mat q3(outImg, Rect(cx, cy, cx, cy)); // ��������

	//�����������Ļ�
	Mat tmp;
	q0.copyTo(tmp); q3.copyTo(q0); tmp.copyTo(q3);//���������½��н���
	q1.copyTo(tmp); q2.copyTo(q1); tmp.copyTo(q2);//���������½��н���
}

/*��˹��ͨ�˲���
ֱ�ӵ����Դ��ĺ���*/
void gaussDefaultFilter()
{
	Mat srcImg, outImg, transImg;
	srcImg = imread("D:\\ͼƬ\\xhs\\XHS_165564086086901024t016i8ot3zj1gq0112stla2qu005r.jpg");
	GaussianBlur(srcImg, transImg, Size(9, 9), 0);
	imshow("��˹", transImg);
	imshow("ԭͼ", srcImg);
	waitKey();

}