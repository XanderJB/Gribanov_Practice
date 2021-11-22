#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <stdio.h>
#include <ctime>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {

	VideoCapture cap(0);

	VideoCapture vidos("3.mp4");
	if (!cap.isOpened()) cout << "File is opened" << endl;

	auto fps = vidos.get(CAP_PROP_FPS); // frames per seconds
	auto delay = 1000 / fps;
	cout << "sobel " << delay << endl;

	Mat frame;

	while (1)
	{
		auto time = clock();
		cap>> frame; 
		if (frame.channels() != 1) cvtColor(frame, frame, COLOR_RGB2GRAY);
		Mat x, y;
		Sobel(frame, x, CV_16S, 1, 0);
		Sobel(frame, y, CV_16S, 0, 1);

		convertScaleAbs(x, x);
		convertScaleAbs(y, y);
		addWeighted(x, 0.5, y, 0.5, 0, frame); 
		imshow("sobel", frame);

		double time_work = (clock() - time) * 1000 / CLOCKS_PER_SEC;
		if (time_work > delay - 1) time_work = 1;
		else time_work = delay - time_work;

		int cap = waitKey(time_work);
		if (cap >= 0) break;
	}
	destroyAllWindows();
	return 0;
}
