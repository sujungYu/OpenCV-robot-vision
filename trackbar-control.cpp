#include <opencv2/opencv.hpp>
#include<iostream>


using namespace cv;
using namespace std;

string title = "이벤트 그리기", bar_name1 = "선의굵기", bar_name2 = "반지름";
int thick = 1;
int radius = 1;

Mat image(600, 400, CV_8UC3, Scalar(255, 255, 255));
Scalar black(0, 0, 0);

void onMouse(int, int, int, int, void*);
void onChange1(int, void*);
void onChange2(int, void*);


void onChange(int value, void* userdata)
{
	int line = value - 130;
	Mat tmp = image + line;
	imshow(title, tmp);

}

void onMouse(int event, int x, int y, int flags, void*param)
{
	switch (event) {
	case  EVENT_LBUTTONDOWN:

			rectangle(image, Point2d(x, y), Point2d(x + 30, y + 30), black, thick);
			imshow(title, image);
			break;

	case EVENT_RBUTTONDOWN:
	
			circle(image, Point2d(x, y), radius, black, thick);
			imshow(title, image);
			break;

	}
}
int main()
{

	int value1 = 128;
	int value2 = 50;

	namedWindow(title, WINDOW_AUTOSIZE);
	moveWindow(title, 100, 200);

	imshow(title, image);
	createTrackbar(bar_name1, title, &value1, 10, onChange1);
	createTrackbar(bar_name2, title, &value1, 50, onChange2);
	imshow(title, image);
	setMouseCallback(title, onMouse, 0);

	waitKey(0);
	return 0;
}

void onChange1(int value, void*userdata) {
	thick = value;
}

void onChange2(int value, void*userdata) {
	radius = value;
}
