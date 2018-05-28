#include "LpAnalyzer.hpp"

int main(int argc, char **argv)
{

	if (argc < 2)
	{
		cout << "Video name is missing." << endl;
		return -1;
	}

	VideoCapture inputVideo(argv[1]);

	if (!inputVideo.isOpened())
	{
		inputVideo = NULL;
		cout << "Error opening video stream or file." << endl;
		return -1;
	}

	LpAnalyzer la(inputVideo);

	la.analyzeVideo();

	return 0;

}