#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class MyVideoCV
{

private:
	VideoCapture orgVideo;

	void checkSize();

public:
	int rows;
	int cols;

	MyVideoCV(string _fname);
	MyVideoCV();
	~MyVideoCV();

};