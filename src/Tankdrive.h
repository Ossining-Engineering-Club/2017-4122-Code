#pragma once
#include "WPIlib.h"

class Tankdrive
{
public: // for functions
	Tankdrive(unsigned int Left1C,unsigned int Left2C, unsigned int Left3C,
			unsigned int Right1C, unsigned int Right2C, unsigned int Right3C);
	void drive(float left,float right);
	void Throttle(float Ithrottle);
	void DirectDrive (float, float);
private: // for variables
	VictorSP Left1;
	VictorSP Left2;
	Spark Left3;
	Spark Right1;
	VictorSP Right2;
	VictorSP Right3;
	float throttle;
};
