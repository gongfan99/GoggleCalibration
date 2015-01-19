#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/chrono.hpp>
#include "ParaGenerator.hpp"
#include "SourceCamera.hpp"
#include "Server_pp.hpp"
#include "EvaluateLine.hpp"
#include "OzoConfigure.hpp"

int main()
{
	using namespace ozo;
	using namespace std;

	char key;
	bool startServer = true;
	int i, caseNum = 0;
	ostringstream tempString;

	tempString << "dK[0]" << " " << "dK[1]" << " " << "dK[2]" << " " << "dK[3]" << " " << "chr[0]" << " " << "chr[1]" << " " << "chr[2]" << " " << "chr[3]" << "deviationStraight" << " " << "d_rg" << " " << "d_bg" << "\n";

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
		boost::this_thread::sleep_for(boost::chrono::milliseconds(20)); //wait for the image to be stable before captured by camera
		if (server.outputReady) {
			camera.process();
			evaluateLine.process();
			
			/*******************************************************
			* save the result to file
			*********************************************************/
			for (i=0; i<4; i++) tempString << paraGenerator.distortionK[i] << " ";
			for (i=0; i<4; i++) tempString << paraGenerator.chromaAbParameter[i] << " ";
			tempString << evaluateLine.deviationStraight << " " << evaluateLine.d_rg << " " << evaluateLine.d_bg << "\n";
			
			startServer = true;
			caseNum++;
			if (caseNum == 1) {
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