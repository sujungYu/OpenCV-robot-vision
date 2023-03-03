#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture capture(0);
	Mat frame;
	Rect rect(200, 100, 200, 100);

	if (!capture.isOpened())
	{
		cout << "카메라가 연결되지 않았습니다" << endl;
		exit(1);
	}

	for (;;) {
		capture.read(frame);
		rectangle(frame, rect, Scalar(0, 0, 255), 1);
		imshow("카메라 영상보기", frame);
		if (waitKey(1) == 27)
		{
			break;
		}
	}
	Mat image = frame(rect);
	destroyAllWindows();
	cout << "문제1-2:" << mean(image) << endl;

	Mat rgb_image[3], r, g, b;
	split(image, rgb_image);

	r = rgb_image[0];
	float sum_r = 0;
	for (int i = 0; i < r.rows; i++) {
		for (int j = 0; j < r.cols; j++) {
			sum_r += r.at<uchar>(i, j);
		}
	}
	float x_r;
	x_r = sum_r / 20000;
	cout << "문제1-3_r" << x_r << endl;

	g = rgb_image[1];
	float sum_g = 0;
	for (int i = 0; i < g.rows; i++) {
		for (int j = 0; j < g.cols; j++) {
			sum_g += g.at<uchar>(i, j);
		}
	}
	float x_g;
	x_g = sum_g / 20000;
	cout << "문제1-3_g " << x_g << endl;

	b = rgb_image[2];
	float sum_b = 0;
	for (int i = 0; i < b.rows; i++) {
		for (int j = 0; j < b.cols; j++) {
			sum_b += b.at<uchar>(i, j);
		}
	}
	float x_b;
	x_b = sum_b / 20000;
	cout << "문제1-3_b " << x_b << endl;


	return 0;
}
