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

	void analyzeVideo()
	{
		
		Mat frame;

		while (true)
		{
			orgVideo >> frame;
			Mat analyzeFrame;

			if (frame.empty())
			{
				break;
			}

			//cvtColor(frame, analyzeFrame, COLOR_BGR2GRAY);
			//halfOfImage(analyzeFrame);
			//analyzeImage(analyzeFrame);
			//showOverayImage(frame, analyzeFrame);
			Mat kernel(3, 3, CV_8U);
			morphologyEx(frame, frame, MORPH_TOPHAT, kernel);
			imshow("test of morphology kernel", frame);

			char c = (char)waitKey(1);
			if (c == 27)
			{
				break;
			}
		}

		return;
	}

	void showOverayImage(Mat &_oriImg, Mat &_analyzeImg)
	{
		static int horizon = (_oriImg.rows / 2) - 30;

		for (int i = horizon; i < _oriImg.rows; i++)
		{
			for (int j = 0; j < _oriImg.cols; j++)
			{
				if (_analyzeImg.at<uchar>(i, j) > 0)
				{
					_oriImg.at<Vec3b>(i, j)[0] = 0;
					_oriImg.at<Vec3b>(i, j)[1] = 0;
					_oriImg.at<Vec3b>(i, j)[2] = 255;
				}
			}
		}

		imshow("Analyzed Image", _oriImg);
	}

	void analyzeImage(Mat &_img)
	{
		Mat kernel(5, 5, CV_8U);
		Mat kernel2(13, 13, CV_8U);
		//cvtColor(_img, _img, COLOR_BGR2GRAY);
		morphologyEx(_img, _img, MORPH_TOPHAT, kernel);
		Canny(_img, _img, 200, 230);
		//dilate(_img, _img, kernel);
		//medianBlur(_img, _img, 11);
		morphologyEx(_img, _img, MORPH_CLOSE, kernel);
		medianBlur(_img, _img, 13);
		dilate(_img, _img, kernel2);
		Canny(_img, _img, 1, 200);
	}

	void halfOfImage(Mat &_img)
	{
		static int horizon = (_img.rows / 2) - 20;

		for (int i = 0; i < (horizon); i++)
		{
			for (int j = 0; j < _img.cols; j++)
			{
				_img.at<uchar>(i, j) = 0;
			}
		}
	}

};

int main(int argc, char **argv)
{

	VideoAnalyzer va(argv[1]);

	va.analyzeVideo();

	return 0;

}