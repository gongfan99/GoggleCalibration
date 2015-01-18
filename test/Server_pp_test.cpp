#include <iostream>
#include <conio.h>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/chrono.hpp>
#include "SourceCamera.hpp"
#include "Server_pp.hpp"
#include "EvaluateLine.hpp"
#include "OzoConfigure.hpp"

using namespace ozo;

int main()
{
	char key;
	bool startServer = true;
	int caseNum = 0;
	float distortionK[4] = {1.0, 0.22, 0.24, 0.0};
	float chromaAbParameter[4] = {0.996, -0.004, 1.014, 0.0};

	//create components
	Server_pp server;
	SourceCamera camera;
	EvaluateLine evaluateLine;

	//connect components
	server.distortionK = distortionK;
	server.chromaAbParameter = chromaAbParameter;
	evaluateLine.data = &(camera.data);

	//main loop
	while(1){
		server.process();
		if (server.outputReady) {
			camera.process();
			evaluateLine.process();
			caseNum++;
			if (caseNum == 1) {
				break;
			} else {
				distortionK[1] += 0.1;
				distortionK[2] += 0.1;
			}
		}
	}
	
	return 0;
}