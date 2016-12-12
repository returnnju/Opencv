#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

const int kvalue = 15;//双边滤波邻域大小

int main05()
{
	Mat src_color = imread("image/circle.png");//读取原彩色图
	imshow("原图-彩色", src_color);

	//声明一个三通道图像，像素值全为0，用来将霍夫变换检测出的圆画在上面
	Mat dst(src_color.size(), src_color.type());
	dst = Scalar::all(0);

	Mat src_gray;//彩色图像转化成灰度图
	cvtColor(src_color, src_gray, COLOR_BGR2GRAY);
	imshow("原图-灰度", src_gray);
	imwrite("src_gray.png", src_gray);

	Mat bf;//对灰度图像进行双边滤波
	bilateralFilter(src_gray, bf, kvalue, kvalue * 2, kvalue / 2);
	imshow("灰度双边滤波处理", bf);
	imwrite("src_bf.png", bf);

	vector<Vec3f> circles;//声明一个向量，保存检测出的圆的圆心坐标和半径
	HoughCircles(bf, circles, CV_HOUGH_GRADIENT, 1.5, 20, 130, 38, 10, 50);//霍夫变换检测圆

	cout << "x=\ty=\tr=" << endl;
	for (size_t i = 0; i < circles.size(); i++)//把霍夫变换检测出的圆画出来
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		circle(dst, center, 0, Scalar(0, 255, 0), -1, 8, 0);
		circle(dst, center, radius, Scalar(0, 0, 255), 1, 8, 0);
		circle(dst, center, radius-1, Scalar(0, 0, 255), 1, 8, 0);
		circle(dst, center, radius + 1, Scalar(0, 0, 255), 1, 8, 0);
		cout << cvRound(circles[i][0]) << "\t" << cvRound(circles[i][1]) << "\t"
			<< cvRound(circles[i][2]) << endl;//在控制台输出圆心坐标和半径				
	}

	imshow("圆检测图片", dst);
	imwrite("dst.png", dst);

	waitKey();

	return 0;
}
