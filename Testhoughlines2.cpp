#include<iostream>  
#include<opencv2/opencv.hpp>  
#include<vector>  

using namespace std;
using namespace cv;

int g_CannyThred = 150, g_CannyP = 0, g_CannySize = 0, g_HoughThred = 100, g_HoughThick = 0;
int g_Blue = 255, g_Green = 255, g_Red = 0;
int g_nWay = 0, g_nValue = 1000;

int main04(){
	Mat srcImage = imread("image/house.jpg");
	imshow("��ԭͼ��", srcImage);

	Mat grayImage;
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	Mat cannyImage;
	vector<Vec2f> lines;
	Point point1, point2;

	namedWindow("�����������ڡ�", 0);
	createTrackbar("CannyThred", "�����������ڡ�", &g_CannyThred, 255, 0);
	createTrackbar("P:", "�����������ڡ�", &g_CannyP, 100, 0);
	createTrackbar("Size", "�����������ڡ�", &g_CannySize, 20, 0);
	createTrackbar("HThred", "�����������ڡ�", &g_HoughThred, 255, 0);
	createTrackbar("Blue", "�����������ڡ�", &g_Blue, 255, 0);
	createTrackbar("Green", "�����������ڡ�", &g_Green, 255, 0);
	createTrackbar("Red", "�����������ڡ�", &g_Red, 255, 0);
	createTrackbar("Bgr/Gray", "�����������ڡ�", &g_nWay, 1, 0);
	createTrackbar("Thick", "�����������ڡ�", &g_HoughThick, 100, 0);
	createTrackbar("Value", "�����������ڡ�", &g_nValue, 2000, 0);

	char key;
	Mat CannyBgrImage;
	Mat dstImage;
	while (1)
	{
		Canny(srcImage, cannyImage, (double)g_CannyThred, (double)((g_CannyThred + 1) * (2 + g_CannyP / 100.0)), 3);
		HoughLines(cannyImage, lines, 1, CV_PI / 180, g_HoughThred + 1, 0, 0);

		cvtColor(cannyImage, CannyBgrImage, CV_GRAY2BGR);

		//��ʾ�߶�  
		for (size_t i = 0; i < lines.size(); i++)
		{
			//�������еõ� ����ֵ�ͽǶ�ֵ  
			//������仹����д�ɣ�  
			/*Vec2f vec = Vec2f(lines[i][0], lines[i][1]);
			float rho = vec[0], theta = vec[1];*/
			float rho = lines[i][0], theta = lines[i][1];
			//���ȵõ�ԭ��(0, 0)����ֱ�ߵĴ��� �� ��ֱ�ߵĽ��������  
			double x0 = rho * cos(theta), y0 = rho * sin(theta);
			//ȡ�ý������صĵ�  ������  
			point1.x = cvRound(x0 + g_nValue * (-sin(theta)));
			point1.y = cvRound(y0 + g_nValue * (cos(theta)));
			point2.x = cvRound(x0 - g_nValue * (-sin(theta)));
			point2.y = cvRound(y0 - g_nValue * (cos(theta)));

			if (g_nWay)
				dstImage = cannyImage;
			else
				dstImage = CannyBgrImage;

			line(dstImage, point1, point2, Scalar(g_Blue, g_Green, g_Red), g_HoughThick + 1, CV_AA);
		}

		imshow("�������", dstImage);

		key = waitKey(1);
		if (key == 27)
			break;
	}

	return 0;
}