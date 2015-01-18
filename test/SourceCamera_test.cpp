#include <iostream>
#include <conio.h>
#include "SourceCamera.hpp"
#include "OzoConfigure.hpp"

int main()
{
	using namespace ozo;
	using namespace cv;

	Mat img;

	//create components
	SourceCamera camera;

	//connect components

	//main loop
	camera.process();
	
	img = camera.data;
	std::cout << "rows: " << img.rows << ", cols: " << img.cols << std::endl;

	namedWindow("image", CV_WINDOW_AUTOSIZE);
	imshow("image", img);
	waitKey();
	
	return 0;
}