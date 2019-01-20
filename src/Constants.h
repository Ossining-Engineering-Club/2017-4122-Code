#pragma once
#define VERSION "3.3.1"

// drive constants
#define LEFTMULT	1.05		// multiplier for the left drive relative to the right

// CAMERA SETTINGS
#define BRIGHTNESS 20		// was 40
#define EXPOSURE 10			// was 20
#define WBM 0		// White Balance Manual
#define FPS	60
#define LIGHTVALUE 1.0		// brightness of lights on talon

// AUTONOMOUS
#define AUTOSPEED 0.35	// for driving WAS 0.35
#define AUTOSPEEDSIDE 0.38		// was 0.35
#define AUTOSPEEDCENTER 0.285 //speed on center gear chute
#define AUTOSPEED2 0.24		// for driving up and backing up -- was 0.2
#define AUTOWAIT 0.1
#define AUTOWAITBACK	1.0
#define AUTOWAITFORWARD	3.0 // was 2.0 and short by 2 inches
#define AUTOTURNWAIT 0.2
#define AUTOTURNSPEED		0.6
#define AUTODISTANCECENTER 69 // in inches for center - was 67.5
#define AUTOSTRAIGHT 95 //Drive straight only distance
#define AUTOGYROCONST 0.016
#define AUTOANGLE 			30
#define AUTOD1A 68.0	// was 70 // was 63.5 // worked once at 58
#define AUTOD1B	 120 //50 //Was 36 -- was 43
#define AUTOTIMEMAX 		10.0		// was
#define CENTERWAIT 0.35
#define ENCODERCONST 0.048
#define USDISTANCE 			13	// was 16.5 in
#define PLACEWAIT			1.0

//PID Constants
#define TIMEPERIOD 0.00001
#define PCONSTANT 0.006
#define ICONSTANT 0.025	// was 300
#define DCONSTANT 0		// was 0.000125


// VISION
#define MINVISION 168
#define MAXVISION 198
#define VISIONTARGET 178
#define VISIONMAXHEIGHT 70.0
#define XDIFFERENCEVAL 60
#define AUTODRIVEVISION 0.3


// CLIMBING SPEED
#define CLIMBINGSPEED 0.5
#define CLIMBHOLD		0.2
