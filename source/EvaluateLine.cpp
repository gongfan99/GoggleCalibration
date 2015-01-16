#include "EvaluateLine.hpp"
#include "OzoConfigure.hpp"
#include <iostream>

namespace ozo {

EvaluateLine::EvaluateLine() {
}

EvaluateLine::~EvaluateLine() {}

void EvaluateLine::process() {
	cv::Mat channel[3];
	cv::split(data, channel); //the function returns RGB in reverse order (BGR)
	

}

} //namespace ozo