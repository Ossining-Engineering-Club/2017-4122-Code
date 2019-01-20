#pragma once
#include "WPIlib.h"

class Pneumatics
{
public: // for functions
	Pneumatics(unsigned int, unsigned int);
	void compstart();
	void compstop();
	void gearchange(bool);


private: // for variables
	Compressor compressor;
	Solenoid gear;

};
