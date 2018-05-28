#include "LpAnalyzer.hpp"

LpAnalyzer::LpAnalyzer()
{

}

LpAnalyzer::LpAnalyzer(VideoCapture _vc)
{
	orgVideo = _vc;

	Mat frame;
	orgVideo >> frame;

	if (frame.empty()) 
	{
		rows = NULL;
		cols = NULL;
	}
		return;

	rows = frame.rows;
	cols = frame.cols;
}

LpAnalyzer::LpAnalyzer(Mat _img)
{
	orgImg = _img;

	rows = _img.rows;
	cols = _img.cols;
}

LpAnalyzer::~LpAnalyzer()
{
	orgVideo.release();
}

void LpAnalyzer::analyzeVideo()
{

	Mat frame;

	if (!orgVideo.isOpened())
	{
		cout << "video open error!" << endl;
		return;
	}

	while (true)
	{
		orgVideo >> frame;

		if (frame.empty())
		{
			break;
		}

		analyzeImage(frame);
		imshow("Analyze result of Video", frame);

		char c = (char)waitKey(1);
		if (c == 27)
		{
			break;
		}
	}

	return;
}

void LpAnalyzer::analyzeImage(Mat &_img)
{
	Mat analyzeImg;
	Mat kernel(5, 5, CV_8U);
	Mat kernel2(9, 9, CV_8U);

	// init of image
	cvtColor(_img, analyzeImg, COLOR_BGR2GRAY);
	halfOfImage(analyzeImg);

	// change of image shape for analysis
	morphologyEx(analyzeImg, analyzeImg, MORPH_TOPHAT, kernel);
	Canny(analyzeImg, analyzeImg, 200, 230);
	morphologyEx(analyzeImg, analyzeImg, MORPH_CLOSE, kernel);
	medianBlur(analyzeImg, analyzeImg, 13);
	dilate(analyzeImg, analyzeImg, kernel2);
	Canny(analyzeImg, analyzeImg, 1, 200);

	// find of contours
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(analyzeImg, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	for (int i = 0; i < contours.size(); i++)
	{
		Rect r = boundingRect(contours[i]);
		rectangle(_img, r, Scalar(0, 0, 255), 3, LINE_8);
	}

}

void LpAnalyzer::halfOfImage(Mat &_img)
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