#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, const char** argv) {
	if (argc < 2)
		return -1;

	cv::namedWindow("SnowFlakesRemoval", cv::WINDOW_AUTOSIZE);

	cv::VideoCapture video(argv[1]);
	cv::Mat prevFrame, frame, nextFrame;
	cv::Mat snow;
	cv::Mat clearedFrame;
	cv::Mat display;
	video >> frame;
	video >> nextFrame;
	while (true) {
		prevFrame = frame.clone();
		frame = nextFrame.clone();
		video >> nextFrame;
		if (nextFrame.empty() || !video.isOpened()) {
			break;
		}
		cv::bitwise_or(frame - prevFrame, frame - nextFrame, snow);
		clearedFrame = frame - snow;

		cv::vconcat(frame, clearedFrame, display);
		cv::resize(display, display, cv::Size(), 0.25, 0.25);
		cv::imshow("SnowFlakesRemoval", display);

		if (cv::waitKey(40) == 27)
			break;
	}
	video.release();
	return 0;
}
