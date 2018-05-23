#include "MyVideoCV.hpp"

MyVideoCV::MyVideoCV()
{

}

MyVideoCV::MyVideoCV(string _fname)
{
	orgVideo = VideoCapture(_fname);
	checkSize();
}

MyVideoCV::~MyVideoCV()
{
	orgVideo.release();
}

void MyVideoCV::checkSize()
{
	Mat frame;
	orgVideo >> frame;

	if (frame.empty())
		return;

	rows = frame.rows;
	cols = frame.cols;

	return;
}
