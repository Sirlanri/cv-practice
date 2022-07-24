/*����Ҷ����㷨*/
#include<opencv2/opencv.hpp>
#include<cmath>

using namespace cv;


void ricodft(Mat& srcImg, Mat& outImg, Mat& transImg);
void dft2(Mat input_image, Mat& output_image, Mat& transform_image);

/*����ͨ��dft�㷨 ���ò���*/
void normal_dft()
{
	Mat srcImg, grayImg, outImg, transImg;
	srcImg = imread("C:\\my\\��ͼ\\QQ��ͼ20220715092337.jpg");
	cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);
	//���ò���
	dft2(grayImg, outImg, transImg);

	//��ʾ
	imshow("��ɫͼ", grayImg);
	imshow("����Ҷout", outImg);
	

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

/*��˹��ͨ�˲���
�Լ���ߣ���루���Բ�ֹ�Ǹ���ճ��Ŷ��
�����������ȷʵʵ���˸�˹�˲���������ȫ������������Ӧ���ȸ���Ҷ��Ӧ��H��*/
void myGauss(int filterSize, Mat& srcImg, Mat& transImg)
{
	//�о����һ�٣�ֱ�Ӵ���һ������&�Ĳ������ͺ��ˣ�
	transImg = srcImg.clone();
	int k = (filterSize - 1) / 2;
	//��������
	for (int i = k; i < (srcImg.rows - k); i++)
	{
		//����
		for (int j = k; j < (srcImg.cols - k); j++)
		{
			double sum = 0.0;
			double sum1 = 0.0;
			double sigma = 7; //�ɵ�����
			double g;
			//��������ѭ���͸�������Ȧ��_(:�١���)_
			for (int m = -k; m < k + 1; m++)
			{
				for (int n = -k; n < k + 1; n++)
				{
					//ʵ��ת�ƺ���H(u,v)
					g = exp(-(m * m + n * n) / (2 * sigma * sigma));
					//����Ϳ�ʼ�±���
					sum = sum + g * srcImg.at<uchar>(i + m, j + n);
					sum1 = sum1 + g;
				}
			}
			transImg.at<uchar>(i, j) = (uchar)round(sum / sum1);

		}
	}
}

/*��д��˹�˲���*/
void gaussFilter()
{
	Mat srcImg, outImg;
	srcImg = imread("D:\\ͼƬ\\xhs\\XHS_165564086086901024t016i8ot3zj1gq0112stla2qu005r.jpg");
	cvtColor(srcImg, srcImg, COLOR_BGR2GRAY);
	myGauss(9, srcImg, outImg);
	imshow("ԭͼ", srcImg);
	imshow("��˺��˹", outImg);
	waitKey();

}

/*���Ƶĸ���Ҷ�任
@param imput_image ����ͼ�񣬻�ɫͼ
@param output_image ����ʾ��Ƶ��ͼ
@param transform_image ����Ҷ�任�ĸ������

*/
void dft2(Mat input_image, Mat& output_image, Mat& transform_image)
{
	//1.��չͼ�����Ϊ2��3��5�ı���ʱ�����ٶȿ�
	int m = getOptimalDFTSize(input_image.rows);
	int n = getOptimalDFTSize(input_image.cols);
	copyMakeBorder(input_image, input_image, 0, m - input_image.rows, 0, n - input_image.cols, BORDER_CONSTANT, Scalar::all(0));

	//2.����һ��˫ͨ������planes���������渴����ʵ�����鲿
	Mat planes[] = { Mat_<float>(input_image), Mat::zeros(input_image.size(), CV_32F) };

	//3.�Ӷ����ͨ�������д���һ����ͨ������:transform_image������Merge����������ϲ�Ϊһ����ͨ�����У�����������ÿ��Ԫ�ؽ�����������Ԫ�صļ���
	merge(planes, 2, transform_image);

	//4.���и���Ҷ�任
	dft(transform_image, transform_image);

	//5.���㸴���ķ�ֵ��������output_image��Ƶ��ͼ��
	split(transform_image, planes); // ��˫ͨ����Ϊ������ͨ����һ����ʾʵ����һ����ʾ�鲿
	Mat transform_image_real = planes[0];
	Mat transform_image_imag = planes[1];

	magnitude(planes[0], planes[1], output_image); //���㸴���ķ�ֵ��������output_image��Ƶ��ͼ��

	//6.ǰ��õ���Ƶ��ͼ�������󣬲�����ʾ�����ת��
	output_image += Scalar(1);   // ȡ����ǰ�����е����ض���1����ֹlog0
	log(output_image, output_image);   // ȡ����
	normalize(output_image, output_image, 0, 1, NORM_MINMAX); //��һ��

	//7.���к��طֲ�����ͼ����
	output_image = output_image(Rect(0, 0, output_image.cols & -2, output_image.rows & -2));

	// �������и���Ҷͼ���е����ޣ�ʹԭ��λ��ͼ������
	int cx = output_image.cols / 2;
	int cy = output_image.rows / 2;
	Mat q0(output_image, Rect(0, 0, cx, cy));   // ��������
	Mat q1(output_image, Rect(cx, 0, cx, cy));  // ��������
	Mat q2(output_image, Rect(0, cy, cx, cy));  // ��������
	Mat q3(output_image, Rect(cx, cy, cx, cy)); // ��������

	//�����������Ļ�
	Mat tmp;
	q0.copyTo(tmp); q3.copyTo(q0); tmp.copyTo(q3);//���������½��н���
	q1.copyTo(tmp); q2.copyTo(q1); tmp.copyTo(q2);//���������½��н���


	Mat q00(transform_image_real, Rect(0, 0, cx, cy));   // ��������
	Mat q01(transform_image_real, Rect(cx, 0, cx, cy));  // ��������
	Mat q02(transform_image_real, Rect(0, cy, cx, cy));  // ��������
	Mat q03(transform_image_real, Rect(cx, cy, cx, cy)); // ��������
	q00.copyTo(tmp); q03.copyTo(q00); tmp.copyTo(q03);//���������½��н���
	q01.copyTo(tmp); q02.copyTo(q01); tmp.copyTo(q02);//���������½��н���

	Mat q10(transform_image_imag, Rect(0, 0, cx, cy));   // ��������
	Mat q11(transform_image_imag, Rect(cx, 0, cx, cy));  // ��������
	Mat q12(transform_image_imag, Rect(0, cy, cx, cy));  // ��������
	Mat q13(transform_image_imag, Rect(cx, cy, cx, cy)); // ��������
	q10.copyTo(tmp); q13.copyTo(q10); tmp.copyTo(q13);//���������½��н���
	q11.copyTo(tmp); q12.copyTo(q11); tmp.copyTo(q12);//���������½��н���

	planes[0] = transform_image_real;
	planes[1] = transform_image_imag;
	merge(planes, 2, transform_image);//������Ҷ�任������Ļ�
}

void dftFilter2()
{
	Mat srcImg, grayImg, outImg, transImg;
	srcImg = imread("D:\\ͼƬ\\xhs\\XHS_1605451276955f937121a-f4b5-3fa3-bb58-1e5738fdc5bd.jpg");
	cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);

	dft2(grayImg, outImg, transImg);

	Mat planes[] = { Mat_<float>(outImg), Mat::zeros(outImg.size(),CV_32F) };
	split(transImg, planes);//����ͨ������ȡʵ���鲿
	Mat image_transform_real = planes[0];
	Mat image_transform_imag = planes[1];

	int core_x = image_transform_real.rows / 2;//Ƶ��ͼ��������
	int core_y = image_transform_real.cols / 2;
	int r = 60;  //�˲��뾶
	float h;
	for (int i = 0; i < image_transform_real.rows; i++)
	{
		for (int j = 0; j < image_transform_real.cols; j++)
		{
			h = exp(-((i - core_x) * (i - core_x) + (j - core_y) * (j - core_y)) / (2 * r * r));
			image_transform_real.at<float>(i, j) = image_transform_real.at<float>(i, j) * h;
			image_transform_imag.at<float>(i, j) = image_transform_imag.at<float>(i, j) * h;

		}
	}
	planes[0] = image_transform_real;
	planes[1] = image_transform_imag;
	Mat image_transform_ilpf;//�����˹��ͨ�˲����
	merge(planes, 2, image_transform_ilpf);

	//3������Ҷ��任
	Mat iDft[] = { Mat_<float>(outImg), Mat::zeros(outImg.size(),CV_32F) };
	idft(image_transform_ilpf, image_transform_ilpf);//����Ҷ��任
	split(image_transform_ilpf, iDft);//����ͨ������Ҫ��ȡ0ͨ��
	magnitude(iDft[0], iDft[1], iDft[0]); //���㸴���ķ�ֵ��������iDft[0]
	normalize(iDft[0], iDft[0], 0, 1, NORM_MINMAX);//��һ������
	imshow("idft", iDft[0]);//��ʾ��任ͼ��

	waitKey();  //��ͣ������ͼ����ʾ���ȴ���������
	
}