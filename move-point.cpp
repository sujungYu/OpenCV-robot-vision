#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("C:/Users/82103/source/repos/2020/2020/lenna.bmp");
	moveWindow("lenna", 300, 400);
	imshow("lenna", img);
	waitKey(0);
	return 0;
}
