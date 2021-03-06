#include "SourceCamera.hpp"
#include "OzoConfigure.hpp"

namespace ozo {

SourceCamera::SourceCamera() {
	cap.open(1);
	if (!cap.isOpened()) {
		std::cout << "cannot open camera! \nuse " << OZO_PROJ_SRC"/MyMovie.wmv" << std::endl;
		cap.open("C:/Users/Sam/Documents/User/Embeded/ServerApp/webserver/source/MyMovie.wmv");
	}
 /* 	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320); 
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);  */
}

SourceCamera::~SourceCamera() {}

void SourceCamera::process() {
	//make sure the system can find "opencv_ffmpeg249.dll" !!!
	do {
		cap >> data;
	} while (data.empty()); //first frame from camera is often NULL
}

} //namespace ozo