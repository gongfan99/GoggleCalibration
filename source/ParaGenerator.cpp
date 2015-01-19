#include "ParaGenerator.hpp"
#include "OzoConfigure.hpp"

namespace ozo {

ParaGenerator::ParaGenerator() {
	distortionK[0] = 1.0;
	distortionK[1] = 0.0;
	distortionK[2] = 0.0;
	distortionK[3] = 0.0;
	
	chromaAbParameter[0] = 1.0;
	chromaAbParameter[1] = 0.0;
	chromaAbParameter[2] = 1.0;
	chromaAbParameter[3] = 0.0;

	// float distortionK[4] = {1.0, 0.22, 0.24, 0.0};
	// float chromaAbParameter[4] = {0.996, -0.004, 1.014, 0.0};
}

ParaGenerator::~ParaGenerator() {}

void ParaGenerator::process() {
	if (distortionK[3] < 0.1) {
		distortionK[3] += 0.01;
	} else if (distortionK[2] < 0.5) {
		distortionK[3] = 0.0;
		distortionK[2] += 0.1;
	} else if (distortionK[1] < 0.5) {
		distortionK[3] = 0.0;
		distortionK[2] = 0.0;
		distortionK[1] += 0.1;
	} else {
		distortionK[3] = 0.0;
		distortionK[2] = 0.0;
		distortionK[1] = 0.0;
	}

/* 	if (chromaAbParameter[1] > 0.02) {
		chromaAbParameter[1] -= 0.001;
	} else {
		chromaAbParameter[1] = 0.0;
	}

	if (chromaAbParameter[3] > 0.02) {
		chromaAbParameter[3] -= 0.001;
	} else {
		chromaAbParameter[3] = 0.0;
	} */

}

} //namespace ozo