/*傅里叶相关算法*/
#include<opencv2/opencv.hpp>
#include<cmath>

using namespace cv;


void ricodft(Mat& srcImg, Mat& outImg, Mat& transImg);
void dft2(Mat input_image, Mat& output_image, Mat& transform_image);

/*最普通的dft算法 调用部分*/
void normal_dft()
{
	Mat srcImg, grayImg, outImg, transImg;
	srcImg = imread("C:\\my\\截图\\QQ截图20220715092337.jpg");
	cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);
	//调用部分
	dft2(grayImg, outImg, transImg);

	//显示
	imshow("灰色图", grayImg);
	imshow("傅里叶out", outImg);
	

	waitKey();

}

/*自定义傅里叶算法
* 其实第一次看我是懵逼的 <￣ω￣>
@param srcImg 源图像
@param outImg 输出图像
@param transImg 变换图像
*/
void ricodft(Mat& srcImg, Mat& outImg, Mat& transImg)
{	/*这种传参方式，可以保证修改到函数外的参数*/

	//1.扩展图像矩阵，为2，3，5的倍数时运算速度快
	//???为啥？？？

	//此函数返回给定向量尺寸经过DFT变换后结果的最优尺寸大小
	int m = getOptimalDFTSize(srcImg.rows);
	int n = getOptimalDFTSize(srcImg.cols);
	copyMakeBorder(srcImg, srcImg, 0, m - srcImg.rows, 0, n - srcImg.cols, BORDER_CONSTANT, Scalar::all(0));

	//2.双通道矩阵planes，用来储存复数的实部与虚部
	Mat planes[] = { Mat_<float>(srcImg), Mat::zeros(srcImg.size(), CV_32F) };

	//3.从多个单通道数组中创建一个多通道数组:transImg。
	//函数Merge将几个数组合并为一个多通道阵列，即输出数组的每个元素将是输入数组元素的级联
	merge(planes, 2, transImg);

	//4.进行傅立叶变换
	dft(transImg, transImg);

	//5.计算复数的幅值
	split(transImg, planes); // 将双通道分为两个单通道，一个表示实部，一个表示虚部
	magnitude(planes[0], planes[1], outImg); //计算复数的幅值，保存在outImg（频谱图）

	//6.前面得到的频谱图数级过大，不好显示，因此转换
	outImg += Scalar(1);   // 取对数前将所有的像素都加1，防止log0
	log(outImg, outImg);   // 取对数
	normalize(outImg, outImg, 0, 1, NORM_MINMAX); //归一化

	//7.剪切和重分布幅度图像限
	//这种写法真独特，从没见过
	outImg = outImg(Rect(0, 0, outImg.cols & -2, outImg.rows & -2));

	// 重新排列傅里叶图像中的象限，使原点位于图像中心
	int cx = outImg.cols / 2;
	int cy = outImg.rows / 2;
	Mat q0(outImg, Rect(0, 0, cx, cy));   // 左上区域
	Mat q1(outImg, Rect(cx, 0, cx, cy));  // 右上区域
	Mat q2(outImg, Rect(0, cy, cx, cy));  // 左下区域
	Mat q3(outImg, Rect(cx, cy, cx, cy)); // 右下区域

	//交换象限中心化
	Mat tmp;
	q0.copyTo(tmp); q3.copyTo(q0); tmp.copyTo(q3);//左上与右下进行交换
	q1.copyTo(tmp); q2.copyTo(q1); tmp.copyTo(q2);//右上与左下进行交换
}

/*高斯低通滤波器
直接调用自带的函数*/
void gaussDefaultFilter()
{
	Mat srcImg, outImg, transImg;
	srcImg = imread("D:\\图片\\xhs\\XHS_165564086086901024t016i8ot3zj1gq0112stla2qu005r.jpg");
	GaussianBlur(srcImg, transImg, Size(9, 9), 0);
	imshow("高斯", transImg);
	imshow("原图", srcImg);
	waitKey();

}

/*高斯低通滤波器
自己手撸代码（绝对不止是复制粘贴哦）
这玩意儿好像确实实现了高斯滤波，但我完全看不懂啊！不应该先傅里叶再应用H吗？*/
void myGauss(int filterSize, Mat& srcImg, Mat& transImg)
{
	//感觉多此一举？直接传进一个不带&的参数不就好了？
	transImg = srcImg.clone();
	int k = (filterSize - 1) / 2;
	//横向像素
	for (int i = k; i < (srcImg.rows - k); i++)
	{
		//纵向
		for (int j = k; j < (srcImg.cols - k); j++)
		{
			double sum = 0.0;
			double sum1 = 0.0;
			double sigma = 7; //可调参数
			double g;
			//里面这俩循环就给我整蒙圈了_(:з」∠)_
			for (int m = -k; m < k + 1; m++)
			{
				for (int n = -k; n < k + 1; n++)
				{
					//实现转移函数H(u,v)
					g = exp(-(m * m + n * n) / (2 * sigma * sigma));
					//这里就开始懵逼了
					sum = sum + g * srcImg.at<uchar>(i + m, j + n);
					sum1 = sum1 + g;
				}
			}
			transImg.at<uchar>(i, j) = (uchar)round(sum / sum1);

		}
	}
}

/*手写高斯滤波器*/
void gaussFilter()
{
	Mat srcImg, outImg;
	srcImg = imread("D:\\图片\\xhs\\XHS_165564086086901024t016i8ot3zj1gq0112stla2qu005r.jpg");
	cvtColor(srcImg, srcImg, COLOR_BGR2GRAY);
	myGauss(9, srcImg, outImg);
	imshow("原图", srcImg);
	imshow("手撕高斯", outImg);
	waitKey();

}

/*复制的傅里叶变换
@param imput_image 输入图像，灰色图
@param output_image 可显示的频谱图
@param transform_image 傅里叶变换的复数结果

*/
void dft2(Mat input_image, Mat& output_image, Mat& transform_image)
{
	//1.扩展图像矩阵，为2，3，5的倍数时运算速度快
	int m = getOptimalDFTSize(input_image.rows);
	int n = getOptimalDFTSize(input_image.cols);
	copyMakeBorder(input_image, input_image, 0, m - input_image.rows, 0, n - input_image.cols, BORDER_CONSTANT, Scalar::all(0));

	//2.创建一个双通道矩阵planes，用来储存复数的实部与虚部
	Mat planes[] = { Mat_<float>(input_image), Mat::zeros(input_image.size(), CV_32F) };

	//3.从多个单通道数组中创建一个多通道数组:transform_image。函数Merge将几个数组合并为一个多通道阵列，即输出数组的每个元素将是输入数组元素的级联
	merge(planes, 2, transform_image);

	//4.进行傅立叶变换
	dft(transform_image, transform_image);

	//5.计算复数的幅值，保存在output_image（频谱图）
	split(transform_image, planes); // 将双通道分为两个单通道，一个表示实部，一个表示虚部
	Mat transform_image_real = planes[0];
	Mat transform_image_imag = planes[1];

	magnitude(planes[0], planes[1], output_image); //计算复数的幅值，保存在output_image（频谱图）

	//6.前面得到的频谱图数级过大，不好显示，因此转换
	output_image += Scalar(1);   // 取对数前将所有的像素都加1，防止log0
	log(output_image, output_image);   // 取对数
	normalize(output_image, output_image, 0, 1, NORM_MINMAX); //归一化

	//7.剪切和重分布幅度图像限
	output_image = output_image(Rect(0, 0, output_image.cols & -2, output_image.rows & -2));

	// 重新排列傅里叶图像中的象限，使原点位于图像中心
	int cx = output_image.cols / 2;
	int cy = output_image.rows / 2;
	Mat q0(output_image, Rect(0, 0, cx, cy));   // 左上区域
	Mat q1(output_image, Rect(cx, 0, cx, cy));  // 右上区域
	Mat q2(output_image, Rect(0, cy, cx, cy));  // 左下区域
	Mat q3(output_image, Rect(cx, cy, cx, cy)); // 右下区域

	//交换象限中心化
	Mat tmp;
	q0.copyTo(tmp); q3.copyTo(q0); tmp.copyTo(q3);//左上与右下进行交换
	q1.copyTo(tmp); q2.copyTo(q1); tmp.copyTo(q2);//右上与左下进行交换


	Mat q00(transform_image_real, Rect(0, 0, cx, cy));   // 左上区域
	Mat q01(transform_image_real, Rect(cx, 0, cx, cy));  // 右上区域
	Mat q02(transform_image_real, Rect(0, cy, cx, cy));  // 左下区域
	Mat q03(transform_image_real, Rect(cx, cy, cx, cy)); // 右下区域
	q00.copyTo(tmp); q03.copyTo(q00); tmp.copyTo(q03);//左上与右下进行交换
	q01.copyTo(tmp); q02.copyTo(q01); tmp.copyTo(q02);//右上与左下进行交换

	Mat q10(transform_image_imag, Rect(0, 0, cx, cy));   // 左上区域
	Mat q11(transform_image_imag, Rect(cx, 0, cx, cy));  // 右上区域
	Mat q12(transform_image_imag, Rect(0, cy, cx, cy));  // 左下区域
	Mat q13(transform_image_imag, Rect(cx, cy, cx, cy)); // 右下区域
	q10.copyTo(tmp); q13.copyTo(q10); tmp.copyTo(q13);//左上与右下进行交换
	q11.copyTo(tmp); q12.copyTo(q11); tmp.copyTo(q12);//右上与左下进行交换

	planes[0] = transform_image_real;
	planes[1] = transform_image_imag;
	merge(planes, 2, transform_image);//将傅里叶变换结果中心化
}

void dftFilter2()
{
	Mat srcImg, grayImg, outImg, transImg;
	srcImg = imread("D:\\图片\\xhs\\XHS_1605451276955f937121a-f4b5-3fa3-bb58-1e5738fdc5bd.jpg");
	cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);

	dft2(grayImg, outImg, transImg);

	Mat planes[] = { Mat_<float>(outImg), Mat::zeros(outImg.size(),CV_32F) };
	split(transImg, planes);//分离通道，获取实部虚部
	Mat image_transform_real = planes[0];
	Mat image_transform_imag = planes[1];

	int core_x = image_transform_real.rows / 2;//频谱图中心坐标
	int core_y = image_transform_real.cols / 2;
	int r = 60;  //滤波半径
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
	Mat image_transform_ilpf;//定义高斯低通滤波结果
	merge(planes, 2, image_transform_ilpf);

	//3、傅里叶逆变换
	Mat iDft[] = { Mat_<float>(outImg), Mat::zeros(outImg.size(),CV_32F) };
	idft(image_transform_ilpf, image_transform_ilpf);//傅立叶逆变换
	split(image_transform_ilpf, iDft);//分离通道，主要获取0通道
	magnitude(iDft[0], iDft[1], iDft[0]); //计算复数的幅值，保存在iDft[0]
	normalize(iDft[0], iDft[0], 0, 1, NORM_MINMAX);//归一化处理
	imshow("idft", iDft[0]);//显示逆变换图像

	waitKey();  //暂停，保持图像显示，等待按键结束
	
}