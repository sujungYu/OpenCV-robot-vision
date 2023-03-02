#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{

	VideoCapture cap("C:/Users/82103/source/repos/201821342/201821342/car.mp4");

	if (!cap.isOpened()) {
		cerr << "Video open failed!" << endl;
		return -1;
	}
	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	Mat frame;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		vector<Rect> detected;
		hog.detectMultiScale(frame, detected);

		for (Rect r : detected) {
			Scalar c = Scalar(0, 0, 255);
			rectangle(frame, r, c, 3);
		}
		imshow("frame", frame);

		if (waitKey(10) == 27)
			break;
	}
	destroyAllWindows();
	return 0;
}