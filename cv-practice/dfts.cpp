/*傅里叶相关算法*/
#include<opencv2/opencv.hpp>
#include<cmath>

using namespace cv;


void ricodft(Mat& srcImg, Mat& outImg, Mat& transImg);

/*最普通的dft算法 调用部分*/
void normal_dft()
{
	Mat srcImg, grayImg, outImg,transImg;
	srcImg = imread("C:\\my\\截图\\QQ截图20220715092337.jpg");
	cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);
	//调用部分
	ricodft(grayImg, outImg, transImg);

	//显示
	imshow("灰色图", grayImg);
	imshow("傅里叶", outImg);
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