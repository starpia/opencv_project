#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class VideoAnalyzer
{
private:
	VideoCapture orgVideo;

	void checkSize()
	{
		Mat frame;
		orgVideo >> frame;

		if (frame.empty())
			return;

		rows = frame.rows;
		cols = frame.cols;

		return;
	}

public:
	int rows;
	int cols;

	VideoAnalyzer() {}
	VideoAnalyzer(string _fname)
	{
		orgVideo = VideoCapture(_fname);
		if (!orgVideo.isOpened())
		{
			orgVideo = NULL;
			cout << "Error opening video stream or file." << endl;
		}
		else
		{
			checkSize();
		}
	}
	~VideoAnalyzer()
	{
		orgVideo.release();
	}


	void TopHatView()
	{
		Mat kernel(5, 5, CV_8U);
		Mat frame;

		while (true)
		{
			orgVideo >> frame;
			
			if (frame.empty())
			{
				break;
			}

			morphologyEx(frame, frame, MORPH_TOPHAT, kernel);
			imshow("Morphology Video", frame);
			
			char c = (char)waitKey(1);
			if (c == 27)
			{
				break;
			}
		}

		return;
	}


};