#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{

	Mat orgImg = imread(argv[1], IMREAD_UNCHANGED);

	imshow("Test Image",orgImg);

	waitKey(0);

	return 0;

}