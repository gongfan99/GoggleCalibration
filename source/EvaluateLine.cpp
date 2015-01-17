#include "EvaluateLine.hpp"
#include "OzoConfigure.hpp"
#include <iostream>

namespace ozo {

EvaluateLine::EvaluateLine() {
}

EvaluateLine::~EvaluateLine() {}

void EvaluateLine::process() {
	using namespace std;
	using namespace cv;

	int col, row;
	vector<lines> rgbLines;
	lines tempLines = {0, 0, 0, 0, 0, 0};
	uchar blue, green, red;
	Mat img = data;
	//cv::split(data, channel); //the function returns RGB in reverse order (BGR)

	for (col=0; col<img.cols; col++) {
		tempLines.weight_blue = 0;
		tempLines.center_blue = 0;
		tempLines.weight_green = 0;
		tempLines.center_green = 0;
		tempLines.weight_red = 0;
		tempLines.center_red = 0;
		for (row=0; row<img.rows; row++) {
		}
	}
	Vec3b intensity = img.at<Vec3b>(y, x);
	blue = intensity.val[0];
	green = intensity.val[1];
	red = intensity.val[2];
}

} //namespace ozo