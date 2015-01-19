#include <iostream>
#include <cv.h>
#include <highgui.h>
#include "EvaluateLine.hpp"
#include "OzoConfigure.hpp"

int main()
{
	using namespace ozo;
	using namespace cv;

	Mat img;
	EvaluateLine evaluateLine;

	//create components
	img = imread("sample.jpg")

	//connect components
	evaluateLine.data = &img;

	//main loop
	evaluateLine.process();
	
	return 0;
}