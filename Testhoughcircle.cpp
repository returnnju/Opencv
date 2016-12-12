#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

const int kvalue = 15;//˫���˲������С

int main05()
{
	Mat src_color = imread("image/circle.png");//��ȡԭ��ɫͼ
	imshow("ԭͼ-��ɫ", src_color);

	//����һ����ͨ��ͼ������ֵȫΪ0������������任������Բ��������
	Mat dst(src_color.size(), src_color.type());
	dst = Scalar::all(0);

	Mat src_gray;//��ɫͼ��ת���ɻҶ�ͼ
	cvtColor(src_color, src_gray, COLOR_BGR2GRAY);
	imshow("ԭͼ-�Ҷ�", src_gray);
	imwrite("src_gray.png", src_gray);

	Mat bf;//�ԻҶ�ͼ�����˫���˲�
	bilateralFilter(src_gray, bf, kvalue, kvalue * 2, kvalue / 2);
	imshow("�Ҷ�˫���˲�����", bf);
	imwrite("src_bf.png", bf);

	vector<Vec3f> circles;//����һ�����������������Բ��Բ������Ͱ뾶
	HoughCircles(bf, circles, CV_HOUGH_GRADIENT, 1.5, 20, 130, 38, 10, 50);//����任���Բ

	cout << "x=\ty=\tr=" << endl;
	for (size_t i = 0; i < circles.size(); i++)//�ѻ���任������Բ������
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		circle(dst, center, 0, Scalar(0, 255, 0), -1, 8, 0);
		circle(dst, center, radius, Scalar(0, 0, 255), 1, 8, 0);
		circle(dst, center, radius-1, Scalar(0, 0, 255), 1, 8, 0);
		circle(dst, center, radius + 1, Scalar(0, 0, 255), 1, 8, 0);
		cout << cvRound(circles[i][0]) << "\t" << cvRound(circles[i][1]) << "\t"
			<< cvRound(circles[i][2]) << endl;//�ڿ���̨���Բ������Ͱ뾶				
	}

	imshow("Բ���ͼƬ", dst);
	imwrite("dst.png", dst);

	waitKey();

	return 0;
}
