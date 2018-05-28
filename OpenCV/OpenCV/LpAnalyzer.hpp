#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class LpAnalyzer
{
private:
	VideoCapture orgVideo;
	Mat orgImg;

public:
	int rows;
	int cols;

	LpAnalyzer();
	LpAnalyzer(VideoCapture _vc);
	LpAnalyzer(Mat _img);
	~LpAnalyzer();
	void analyzeVideo();
	void analyzeImage(Mat &_img);
	void halfOfImage(Mat &_img);
};