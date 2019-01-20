#pragma once
#include "WPIlib.h"
#include "Constants.h"
#include "Ultrasonic.h"
#include "Vision.h"

class Tankdrive
{
public: // for functions
	Tankdrive(unsigned int Leftchannel,unsigned int Rightchannel);
	void drive(float left,float right);
	void Throttle(float Ithrottle);
	void DirectDrive (float, float);
	void AutoDriveGyro(float, float); //Args are distance, speed
	void AutoTurnGyro(float, float);
	void AutoDriveGyroUS(float, float, float);
	int AutoDriveVision(float, float, float);

	void EncoderReset();
	void GetUSSample();
	double GetUSRange();
	double GetLEncoder();
	double GetREncoder();
	double GetGyro();
private: // for variables
	Talon Left;
	Talon Right;
	Encoder LWEncoder;
	Encoder RWEncoder;
	AnalogGyro Gyro;
	USSensor Usonic;
	Timer AutoTimer;
	Vision vision;
	float throttle;
	float VisionX;
	float VisionDifference;
};
