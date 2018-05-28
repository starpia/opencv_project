#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class VideoAnalyzer
{
private:
	VideoCapture orgVideo;

	void checkSize();

public:
	int rows;
	int cols;

	VideoAnalyzer();
	VideoAnalyzer(string _fname);
	~VideoAnalyzer();
	void analyzeVideo();
	static void analyzeImage(Mat &_img);
	void halfOfImage(Mat &_img);
};