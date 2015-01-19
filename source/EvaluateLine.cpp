#include "EvaluateLine.hpp"
#include "OzoConfigure.hpp"

namespace ozo {

EvaluateLine::EvaluateLine() {}

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
	tempString << "weight_blue" << " " << "center_blue" << " " << "weight_green" << " " << "center_green" << " " << "weight_red" << " " << "center_red" << "\n";

	/*******************************************************
	* calculate the lines for red/green/blue
	* input: data
	* output: rgbLines
	*********************************************************/
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
		tempLines.center_blue = (tempLines.weight_blue < 1e-3)? 0 : tempLines.center_blue/tempLines.weight_blue;
		tempLines.center_green = (tempLines.weight_green < 1e-3)? 0 : tempLines.center_green/tempLines.weight_green;
		tempLines.center_red = (tempLines.weight_red < 1e-3)? 0 : tempLines.center_red/tempLines.weight_red;
		
		rgbLines.push_back(tempLines);
		
		tempString << tempLines.weight_blue << " " << tempLines.center_blue << " " << tempLines.weight_green << " " << tempLines.center_green << " " << tempLines.weight_red << " " << tempLines.center_red << "\n";
	}
	
/* 	ofstream myfile;
	myfile.open ("result.txt", fstream::out | fstream::trunc);
	myfile << tempString.str();
	myfile.close(); */

	/*******************************************************
	* calculate the deviation from straight line for (x, y)
	* input: (x, y) where x = col, y = rgbLines[col].center_green
	* output: deviationStraight
	* note: equations are from
	* http://archive.bio.ed.ac.uk/jdeacon/statistics/tress11.html
	*********************************************************/
	float startRatio, dx2, dy2, dxy, slope, intercept, coefficientOfDetermination;
	float s_x, s_y, s_xy, s_x2, s_y2;
	int NN;
	startRatio = 0.20; // we only use the middle portion of rgbLines
	s_x = s_y = s_xy = s_x2 = s_y2 = 0.0;
	NN = (int)((1 - startRatio) * rgbLines.size()) - (int)(startRatio * rgbLines.size());
	for (col=(int)(startRatio*rgbLines.size()); col<(int)((1-startRatio)*rgbLines.size()); col++) {
		s_x += col;
		s_y += rgbLines[col].center_green;
		s_xy += col * rgbLines[col].center_green;
		s_x2 += col * col;
		s_y2 += rgbLines[col].center_green * rgbLines[col].center_green;
	}
	dx2 = s_x2 - s_x * s_x / NN;
	dy2 = s_y2 - s_y * s_y / NN;
	dxy = s_xy - s_x * s_y / NN;

	// result of linear regression: y = intercept + slope * x
	slope = dxy / dx2;
	intercept = (s_y - slope * s_x) / NN;
	coefficientOfDetermination = (dx2 < 1e-3 || dy2 < 1e-3)? -1 : dxy * dxy / (dx2 * dy2);

	deviationStraight = dy2; // i.e. Sigma [ yi - avg(y) ]^2

	/*******************************************************
	* calculate the difference between blue/red and green
	* input: rgbLines, startRatio
	* output: 
	* 		d_rg: difference between red and green
	* 		d_bg: difference between blue and green
	*********************************************************/
	d_rg = d_bg = 0.0;
	for (col=(int)(startRatio*rgbLines.size()); col<(int)((1-startRatio)*rgbLines.size()); col++) {
		d_rg += (rgbLines[col].center_red - rgbLines[col].center_green) * (rgbLines[col].center_red - rgbLines[col].center_green);
		d_bg += (rgbLines[col].center_blue - rgbLines[col].center_green) * (rgbLines[col].center_blue - rgbLines[col].center_green);
	}

/* 	cout << startRatio * rgbLines.size() << "  " << (1 - startRatio) * rgbLines.size() << endl;
	cout << s_x << "  " << s_y << "  " << s_xy << "  " << s_x2 << "  " << s_y2 << endl;
	cout << dx2 << "  " << dy2 << "  " << dxy << endl;
	cout << slope << "  " << intercept << endl;
	cout << "deviationStraight: " << deviationStraight << endl;
	cout << "d_rg: " << d_rg << endl;
	cout << "d_bg: " << d_bg << endl; */
}

} //namespace ozo