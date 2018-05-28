#include "VideoAnalyzer.hpp"

int main(int argc, char **argv)
{

	if (argc < 2)
	{
		cout << "Video name is missing." << endl;
		return -1;
	}

	VideoAnalyzer va(argv[1]);

	va.analyzeVideo();

	return 0;

}