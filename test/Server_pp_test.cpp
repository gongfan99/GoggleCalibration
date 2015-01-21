#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
/* #include <boost/thread.hpp>
#include <boost/thread/mutex.hpp> */
#include <boost/chrono.hpp>
#include "ParaGenerator.hpp"
#include "SourceCamera.hpp"
#include "Server_pp.hpp"
#include "EvaluateLine.hpp"
#include "OzoConfigure.hpp"

template < typename T >
std::string to_string( const T& n )	{
	std::ostringstream stm ;
	stm << n ;
	return stm.str() ;
}
	
int main()
{
	using namespace ozo;
	using namespace std;

	char key;
	bool startServer = true;
	int i, caseNum = 0;
	ostringstream tempString;

	tempString << "dK[0]" << " " << "dK[1]" << " " << "dK[2]" << " " << "dK[3]" << " " << "chr[0]" << " " << "chr[1]" << " " << "chr[2]" << " " << "chr[3]" << " " << "deviationStraight" << " " << "d_rg" << " " << "d_bg" << "\n";

	cv::namedWindow("Camera_Output", CV_WINDOW_AUTOSIZE);

	//create components
	ParaGenerator paraGenerator;
	Server_pp server;
	SourceCamera camera;
	EvaluateLine evaluateLine;

	//connect components
	server.distortionK = paraGenerator.distortionK;
	server.chromaAbParameter = paraGenerator.chromaAbParameter;
	server.inputReady = &startServer;
	evaluateLine.data = &(camera.data);

	//main loop
	while(1){
		server.process();
		boost::this_thread::sleep_for(boost::chrono::milliseconds(50)); //wait for the image to be stable before captured by camera
		if (server.outputReady) {
			camera.process();
			evaluateLine.process();
			
			/*******************************************************
			* save the result to file
			*********************************************************/
			cv::imshow("Camera_Output", camera.data);
			cv::waitKey(30);
			//cv::imwrite(to_string<int>(caseNum)+".png", camera.data);
			//boost::this_thread::sleep_for(boost::chrono::milliseconds(3000));
			for (i=0; i<4; i++) tempString << paraGenerator.distortionK[i] << " ";
			for (i=0; i<4; i++) tempString << paraGenerator.chromaAbParameter[i] << " ";
			tempString << evaluateLine.deviationStraight << " " << evaluateLine.d_rg << " " << evaluateLine.d_bg << "\n";
			/********************************************************/
			cout << "caswNum: " << caseNum << endl;
			startServer = true;
			caseNum++;
			if (caseNum == 50) {
				break;
			} else {
				paraGenerator.process(); //generate new distortionK and chromaAbParameter
			}
		}
	}

	/*******************************************************
	* save the result to file
	*********************************************************/
	ofstream myfile;
	myfile.open ("output.txt", fstream::out | fstream::trunc);
	myfile << tempString.str();
	myfile.close();
	
	return 0;
}