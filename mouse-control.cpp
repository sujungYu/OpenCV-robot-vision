#include <opencv2/opencv.hpp>
#include<iostream>


using namespace cv;
using namespace std;

string title = "이벤트 그리기";
int thick = 1;
int radius = 1;

Mat image(600, 400, CV_8UC3, Scalar(255, 255, 255));
Scalar black(0, 0, 0);

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

	namedWindow(title, WINDOW_AUTOSIZE);
	moveWindow(title, 100, 200);

	imshow(title, image);
	setMouseCallback(title, onMouse, 0);

	waitKey(0);
	return 0;
}
