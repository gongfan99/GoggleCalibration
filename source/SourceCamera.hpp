#ifndef __OZO_SOURCECAMERA_HPP__
#define __OZO_SOURCECAMERA_HPP__

#include <cv.h>
#include <highgui.h>

namespace ozo {

class SourceCamera {
public:
	//the external input interface
	
	//the external output interface
	cv::Mat data;

	SourceCamera();
	~SourceCamera();
	void process();
private:
	cv::Mat frame;
	cv::VideoCapture cap;
};

} //namespace ozo

#endif // __OZO_SOURCECAMERA_HPP__