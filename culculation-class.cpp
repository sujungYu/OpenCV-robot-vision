#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


int main()
{
	Size2i sz(200, 300);
	Size2i sz1(20, 30);
	Point2i pt1(50, 50);
	Rect_<int> rect1(100, 100, 200, 300);

	Rect rect2 = rect1 + (Point)pt1;
	rect2 = rect2 + (Size2i)sz1;


	cout << "평행이동한 좌표는" << rect2.x << "," << rect2.y << "입니다" << endl;
	cout << "평행이동하고 크기를 증가시킨 사각형의 크기는" << rect2 << "입니다." << endl;

	return 0;
}
