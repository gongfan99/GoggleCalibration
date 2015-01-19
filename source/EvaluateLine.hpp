#ifndef __OZO_EVALUATELINE_HPP__
#define __OZO_EVALUATELINE_HPP__

#include <iostream>
#include <fstream>
#include <sstream>
#include <cv.h>
#include <highgui.h>

namespace ozo {

// weight and weight center of RGB lines.
typedef struct lines_
{
    int weight_blue, center_blue, weight_green, center_green, weight_red, center_red;  
} lines;

class EvaluateLine {
public:
	//the external input interface
	cv::Mat *data;
	
	//the external output interface
	float deviationStraight, d_rg, d_bg;

	EvaluateLine();
	~EvaluateLine();
	void process();
private:

};

} //namespace ozo

#endif // __OZO_EVALUATELINE_HPP__