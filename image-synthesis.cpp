#include <opencv2/opencv.hpp>
#include<iostream>


using namespace cv;
using namespace std;

void onMouse(int, int, int, int, void*);
void onChange1(int, void*);
void onChange2(int, void*);

void onChange(int value, void* userdata)
{
	int line = value - 1;
	Mat tmp = image + line;
	imshow(title, tmp);

}

int main()
{
	int value1 = 5;
	int value2 = 5
	string bar_name1 = "img1 rate", bar_name2 = "img2 rate";;

	namedWindow(title, WINDOW_AUTOSIZE);
	moveWindow(title, 100, 200);

	imshow(title, image);
	createTrackbar(bar_name1, title, &value1, 10, onChange1);
	createTrackbar(bar_name2, title, &value1, 10, onChange2);
	imshow(title, image);
	setMouseCallback(title, onMouse, 0);
	Mat image1 = imread("C:\\Users\\82103\\source\\repos\\2020\\2020\\add1.jpg", IMREAD_COLOR);
	Mat image2 = imread("C:\\Users\\82103\\source\\repos\\2020\\2020\\add2.jpg", IMREAD_COLOR);
	CV_Assert(!(image1.empty() || image2.empty()));

	double alpha = 0.6, beta = 0.7;
	Mat add_img1;
	addWeighted(image1, alpha, image2, beta, 0, add_img1);

	imshow("add_img1", add_img1);
	waitKey(0);
	return 0;
}
void onChange1(int value, void*userdata) {
	img1_rate = value;
}

void onChange2(int value, void*userdata) {
	img2_rate= value;
}
