#ifndef __OZO_PARAGENERATOR_HPP__
#define __OZO_PARAGENERATOR_HPP__

#include <iostream>

namespace ozo {

class ParaGenerator {
public:
	//the external input interface

	//the external output interface
	float distortionK[4], chromaAbParameter[4];

	ParaGenerator();
	~ParaGenerator();
	void process();
private:

};

} //namespace ozo

#endif // __OZO_PARAGENERATOR_HPP__