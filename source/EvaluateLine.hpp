#ifndef __OZO_EVALUATELINE_HPP__
#define __OZO_EVALUATELINE_HPP__

#include <cv.h>
#include <highgui.h>

namespace ozo {

class EvaluateLine {
public:
	cv::Mat data; //the external input interface
	EvaluateLine();
	~EvaluateLine();
	void process();
private:

};

} //namespace ozo

#endif // __OZO_EVALUATELINE_HPP__