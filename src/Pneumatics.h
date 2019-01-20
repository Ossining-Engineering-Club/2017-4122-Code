#pragma once
#include "WPIlib.h"

class Pneumatics
{
public: // for functions
	Pneumatics(unsigned int, unsigned int, unsigned int);
	void compstart();
	void compstop();
	void gearchange(bool);
	void gearplacer(bool);


private: // for variables
	Compressor compressor;
	Solenoid gear;			// for changing from high gear to low gear
	Solenoid gearplace;

};
