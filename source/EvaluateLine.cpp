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
	Vec3b intensity;
	uchar blue, green, red;
	Mat img;
	//cv::split(data, channel); //the function returns RGB in reverse order (BGR)

	ostringstream tempString;

	img = *data;
	for (col=0; col<img.cols; col++) {
		tempLines.weight_blue = 0;
		tempLines.center_blue = 0;
		tempLines.weight_green = 0;
		tempLines.center_green = 0;
		tempLines.weight_red = 0;
		tempLines.center_red = 0;
		for (row=0; row<img.rows; row++) {
			intensity = img.at<Vec3b>(row, col);
			blue = intensity.val[0];
			green = intensity.val[1];
			red = intensity.val[2];
			
			tempLines.weight_blue += blue;
			tempLines.center_blue += blue * row;
			tempLines.weight_green += green;
			tempLines.center_green += green * row;
			tempLines.weight_red += red;
			tempLines.center_red += red * row;
		}
		tempLines.center_blue /= tempLines.weight_blue;
		tempLines.center_green /= tempLines.weight_green;
		tempLines.center_red /= tempLines.weight_red;
		
		rgbLines.push_back(tempLines);
		
		tempString << tempLines.weight_blue << " " << tempLines.center_blue << " " << tempLines.weight_green << " " << tempLines.center_green << " " << tempLines.weight_red << " " << tempLines.center_red << "\n";
	}
	
	std::ofstream myfile;
	myfile.open ("mesh.txt", std::fstream::out | std::fstream::trunc);
	myfile << tempString.str();
	myfile.close();

}

} //namespace ozo