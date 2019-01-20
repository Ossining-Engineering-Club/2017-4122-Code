/***************************************************************************************
 *
 * Declare the Interface for the Ossining High School Robot
 * 
 */
#ifndef USSENSOR_H_		//Checks if subsys.h has already been included
#define USSENSOR_H_		//Set USSENSOR_H when ussensor.h is included to prevent it from being included multiple times
#include "WPILib.h"		//Include the FRC Library


/*
 * Ultrasonic Sensor Class
 */
class USSensor
{
	public:
		USSensor(uint32_t channel);	//Constructor to intialize - default is off
		float GetRawRange(void);  //Gives unaveraged range value
		void GetSample(void);	//This is used for taking a sample
		float GetRange(void);	//Find the range using the sensor
	private:
		AnalogInput uschannel;
		float averagerange;		//Variable accumulates average range
};
#endif
