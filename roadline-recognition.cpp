#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS   

using namespace cv;
using namespace std;

Mat grad, src;
Mat edges(600, 800, CV_8UC1);
char name[100];

void main()

{
	VideoCapture cap("C:\\Users\\82103\\source\\repos\\201821342\\201821342\\car_line.mp4");
	//int gg = 0;
	Mat scr;
	while (1) {
		cap >> scr;
		if (!src.data) break; // src 이미지 데이터가없으면 종료

		edges = Scalar(0);

		//소벨 필터
		Mat src_gray;
		Mat abs_grad_x, abs_grad_y;
		int scale = 1;
		int delta = 0;
		int ddepth = CV_16S;

		//이미지 로딩
		GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
		cvtColor(src, src_gray, IMREAD_COLOR);

		Mat grad_x, grad_y;

		/// Gradient X
		Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
		convertScaleAbs(grad_x, abs_grad_x);

		/// Gradient Y
		Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
		convertScaleAbs(grad_y, abs_grad_y);

		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

		//오른쪽 엣지 찾기
		vector<Point2i> rPoints;
		for (int y = 430; y < grad.rows; y = y + 5)
		{
			bool i = false;
			uchar* data = grad.ptr<uchar>(y);
			for (int x = 300; x < grad.cols; x++) {
				if (data[x] > 100 && i == false)
				{
					rectangle(edges, Point(x, y), Point(x - 2, y - 2), Scalar(255, 0, 0), 2);
					rPoints.push_back(Point(x, y));
					i = true;
				}
			}
		}
		//왼쪽 엣지 찾기
		vector<Point2i> lPoints;
		for (int y = 380; y < grad.rows; y = y + 5)
		{
			bool i = false;
			uchar* data = grad.ptr<uchar>(y);
			for (int x = 300; x > 0; x--) {
				if (data[x] > 100 && i == false)
				{
					rectangle(edges, Point(x, y), Point(x - 2, y - 2), Scalar(255, 0, 0), 2);
					lPoints.push_back(Point(x, y));
					i = true;
				}
			}
		}


		// 라인 찾기
		vector<Vec2f> lines;
		HoughLines(edges, lines, 1, CV_PI / 180, 150, 0, 0);
		int r, l;
		l = 0, r = 0;
		// 라인 그리기
		for (size_t i = 0; i < lines.size(); i++)
		{
			float rho = lines[i][0], theta = lines[i][1];
			Point pt1, pt2;
			double a = cos(theta), b = sin(theta);

			if ((a / b) < 0)
			{
				r = i;
			}
			else
			{
				l = i;
				cout << l << endl;
			}
		}


		float rho = lines[r][0], theta = lines[r][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));

		float rho2 = lines[l][0], theta2 = lines[l][1];
		Point pt3, pt4;
		double a2 = cos(theta2), b2 = sin(theta2);
		double x02 = a2 * rho2, y02 = b2 * rho2;
		pt3.x = cvRound(x02 + 1000 * (-b2));
		pt3.y = cvRound(y02 + 1000 * (a2));
		pt4.x = cvRound(x02 - 1000 * (-b2));
		pt4.y = cvRound(y02 - 1000 * (a2));

		double t;
		double s;

		double under = (pt4.y - pt3.y)*(pt2.x - pt1.x) - (pt4.x - pt3.x)*(pt2.y - pt1.y);

		double _t = (pt4.x - pt3.x)*(pt1.y - pt3.y) - (pt4.y - pt3.y)*(pt1.x - pt3.x);
		double _s = (pt2.x - pt1.x)*(pt1.y - pt3.y) - (pt4.y - pt1.y)*(pt1.x - pt3.x);



		t = _t / under;
		s = _s / under;


		double cx = pt1.x + t * (double)(pt2.x - pt1.x);
		double cy = pt1.y + t * (double)(pt2.y - pt1.y);
		Point cp;
		cp.x = cx, cp.y = cy;

		line(src, pt2, cp, Scalar(0, 0, 255), 3, 4);
		line(src, pt3, cp, Scalar(0, 0, 255), 3, 4);
		rectangle(src, Point(cx, cy), Point(cx - 4, cy - 4), Scalar(255, 0, 0), 4);



		cv::namedWindow("Detected Lines with Hough");
		cv::imshow("Detected Lines with Hough", src);

		waitKey(1);
	}

}
