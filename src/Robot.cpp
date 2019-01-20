#include "WPIlib.h"
#include "Tankdrive.h"
#include "Constants.h"
#include "Pneumatics.h"
#include "Vision.h"
#include "Ultrasonic.h"
#include <math.h>

class Robot: public SampleRobot
{
private:
	Tankdrive tankdrive;
	SmartDashboard *dash;
	Joystick joystickleft;
	Joystick joystickright;
	DigitalInput dio4;
	DigitalInput dio5;
	DigitalInput dio6;
	DigitalInput dio7;
	Joystick joystickarm;
	Pneumatics pneumatics;
	Timer autotime;
	Talon climber;
    Relay spike;
    AnalogPotentiometer potentiometer;
    Servo dropfront;
    Talon lights;
    cs::UsbCamera camera;
    Vision valuevision;


	float heightpercentage = 0;
	float VisionX = 0;
	float difference = 0;
	float X0, X1 = 0;
	float waittime;
	float lightvalue;
	bool init;

public:
	Robot():
		tankdrive(0,1), // 0 is left 1 is right
		dash (),
		joystickleft (1),
		joystickright (0),
		dio4(4),
		dio5(5),
		dio6(6),
		dio7(7),
		joystickarm (2),
		pneumatics (0,0,1), // compressor and solenoid both in port 0
		autotime(),
		climber(2),
		spike(0),
		potentiometer(2),
		dropfront(3),                //PWM 3
		lights(4),
		camera(),
		valuevision()
	{
		dash->init();
		X0 = 0;
		X1 = 0;
		init = false;
		waittime=0.0;
		lightvalue=0.0;
	}

	void RobotInit()
	{
		camera = CameraServer::GetInstance()->StartAutomaticCapture();
		camera.SetBrightness(BRIGHTNESS);
		camera.SetExposureManual(EXPOSURE);
		camera.SetWhiteBalanceManual(WBM);
		camera.SetResolution(320,240);
		camera.SetFPS(FPS);
	}

	void Autonomous()
	{
		dash->PutNumber("While loop exit", 0);
		lights.Set(LIGHTVALUE);
		tankdrive.DirectDrive(0.0,0.0);
		pneumatics.gearplacer(0);
		pneumatics.gearchange(0);
		dash->PutString("version id", VERSION);
		dash->PutBoolean("DIO4", dio4.Get());
		dash->PutBoolean("DIO5", dio5.Get());
		dash->PutBoolean("DIO6", dio6.Get());

		pneumatics.compstop();
		// this one without vision
		valuevision.Update();
		dash->PutNumber("#1", valuevision.GetY(0));
		dash->PutNumber("#2", valuevision.GetY(1));
		tankdrive.EncoderReset();
		dash->PutString("Autonomous","Waiting");
		waittime= 10.0 * potentiometer.Get();
		dash->PutNumber("Wait Time", waittime);
		if (IsAutonomous())Wait(waittime);
		dash->PutNumber("Gyro Angle", tankdrive.GetGyro());
		dash->PutString("Autonomous","After Wait");
		if (dio4.Get() && dio5.Get() && dio6.Get() && dio7.Get())	// just straigth
		{
			tankdrive.Throttle(1.0);
			tankdrive.drive(AUTOSPEEDSIDE*(2-LEFTMULT), AUTOSPEEDSIDE*LEFTMULT);
			Wait(3.0);
			tankdrive.drive(0.0,0.0);
		}
		else if (!dio4.Get() && dio5.Get() && dio6.Get())	// left
		{
			dash->PutString("Autonomous","Path left: Drive 1");
			tankdrive.AutoDriveGyro(AUTOD1A,AUTOSPEEDSIDE);
//			if (IsAutonomous())Wait(AUTOWAIT);
			dash->PutString("Autonomous","Path left: Turn");
			tankdrive.AutoTurnGyro(AUTOANGLE,AUTOTURNSPEED);
			if (IsAutonomous())Wait(AUTOWAIT);
			dash->PutString("Autonomous","Path left: Drive 2");
			if (dio7.Get())
			{
				tankdrive.AutoDriveGyroUS(USDISTANCE, AUTOSPEED2, AUTOD1B);
				dash->PutString("Autonomous","Path left: NO VISION");
			}
			else
			{
				dash->PutNumber("While loop exit", tankdrive.AutoDriveVision(USDISTANCE, AUTOSPEED2, AUTOD1B));
				dash->PutString("Autonomous","Path left: VISION");
			}
		}
		else if (!dio6.Get() && dio4.Get() && dio5.Get())	//	right
		{
			dash->PutString("Autonomous","Path right: Drive 1");
			tankdrive.AutoDriveGyro(AUTOD1A,AUTOSPEEDSIDE);
//			if (IsAutonomous())Wait(AUTOWAIT);
			dash->PutString("Autonomous","Path right: Turn");
			dash->PutNumber("Gyro Angle", tankdrive.GetGyro());
			tankdrive.AutoTurnGyro(-1*AUTOANGLE,AUTOTURNSPEED);
			if (IsAutonomous())Wait(AUTOWAIT);
			dash->PutString("Autonomous","Path right: Drive 2");
			if (dio7.Get())
			{
				tankdrive.AutoDriveGyroUS(USDISTANCE, AUTOSPEED2, AUTOD1B);
				dash->PutString("Autonomous","Path right: NO VISION");
			}
			else
			{
				dash->PutNumber("While loop exit",tankdrive.AutoDriveVision(USDISTANCE, AUTOSPEED2, AUTOD1B));
				dash->PutString("Autonomous","Path right: VISION");
			}
		}
		else	//center
		{
			Wait(CENTERWAIT);
			dash->PutString("Autonomous","Path center: Drive 1");
			if (dio7.Get())
			{
				tankdrive.AutoDriveGyroUS(USDISTANCE, AUTOSPEEDCENTER, AUTODISTANCECENTER);
				dash->PutString("Autonomous","Path center: NO VISION");
			}
			else
			{
				dash->PutNumber("Lencoder", tankdrive.GetLEncoder());
				dash->PutNumber("Rencoder", tankdrive.GetREncoder());
				dash->PutNumber("While loop exit", tankdrive.AutoDriveVision(USDISTANCE, AUTOSPEEDCENTER, AUTODISTANCECENTER));
				dash->PutString("Autonomous","Path center: VISION");
				dash->PutNumber("Lencoder", tankdrive.GetLEncoder());
				dash->PutNumber("Rencoder", tankdrive.GetREncoder());

			}
		}
		tankdrive.DirectDrive(0.0,0.0);
		lights.Set(0.0);
	}

	void OperatorControl()
	{
		camera = CameraServer::GetInstance()->StartAutomaticCapture();
		dropfront.SetAngle(0.0);
		dash->PutString("DropFront: ", "DOWN");
		pneumatics.gearchange(0);	// sets robot settings at start
		pneumatics.gearplacer(0);
		pneumatics.compstart();		//Compressor on for Teleop added in version 1.8.11
		dash->PutString("Compressor: ", "ON");
		dash->PutString("Transmission", "HIGH");
		dash->PutString("Gear Place: ", "HIGH");
		dash->PutString("Climb Status: ", "NOT CLIMBING");
		tankdrive.drive(0,0);
		tankdrive.EncoderReset();
		while (IsOperatorControl() && IsEnabled())
		{
			lightvalue = 0.5 * (1-joystickleft.GetZ());
			lights.Set(lightvalue);
			for(int i = 0; i < 10; ++i)
			{
				tankdrive.Throttle((joystickright.GetZ()-1)/2);
				tankdrive.drive(joystickright.GetY(), joystickleft.GetY());
				tankdrive.GetUSSample();
				Wait(0.01);
			}
			if(joystickright.GetRawButton(6))
			{
				pneumatics.compstart();
				dash->PutString("Compressor: ", "ON");
			}
			else if(joystickright.GetRawButton(7))
			{
				dash->PutString("Compressor: ", "OFF");
				pneumatics.compstop();
			}
			if(joystickright.GetRawButton(5))
			{
				dash->PutString("Transmission", "HIGH");
				pneumatics.gearchange(0); // high gear
			}
			else if(joystickright.GetRawButton(4))
			{
				dash->PutString("Transmission", "LOW");
				pneumatics.gearchange(1); //low gear
			}
			if (joystickright.GetRawButton(1))
			{
				dash->PutString("Climb Status: ", "CLIMBING");
				climber.Set(1.0);
			}
			else if (joystickleft.GetRawButton(6))
			{
				dash->PutString("Climb Status: ", "DROPPING");
				climber.Set(-1.0);
			}
			else if (joystickright.GetRawButton(11))
			{
				dash->PutString("Climb Status: ", "HOLDING");
				climber.Set(CLIMBHOLD);
			}
			else
			{
				dash->PutString("Climb Status: ", "NOT CLIMBING");
				climber.Set(0.0);
			}
			if (joystickright.GetRawButton(3))
			{
				dash->PutString("Gear Place: ", "HIGH");
				pneumatics.gearplacer(0);
			}
			else if (joystickright.GetRawButton(2))
			{
				dash->PutString("Gear Place: ", "LOW");
				pneumatics.gearplacer(1);
			}
			if (joystickleft.GetRawButton(11))
			{
				dropfront.SetAngle(0.0);   //Raise the front up
				dash->PutString("DropFront: ", "DOWN");
			}
			else if (joystickleft.GetRawButton(10))
			{
				dropfront.SetAngle(150.0);   //Raise the front up
				dash->PutString("DropFront: ", "UP");
			}

			dash->PutString("version id", VERSION);

			dash->PutNumber("Vision 1st X val", valuevision.GetX(0));
			dash->PutNumber("Vision 2nd X val", valuevision.GetX(1));
			dash->PutNumber("Vision 1st Y val", valuevision.GetY(0));
			dash->PutNumber("Vision 2nd Y val", valuevision.GetY(1));
			dash->PutNumber("Lencoder", tankdrive.GetLEncoder());
			dash->PutNumber("Rencoder", tankdrive.GetREncoder());
			dash->PutNumber("Gyro Angle", tankdrive.GetGyro());
			dash->PutNumber("Ultrasonic", tankdrive.GetUSRange());
			dash->PutNumber("lightvalue", lightvalue);
		}
		climber.Set(0.0);
	}
};
START_ROBOT_CLASS(Robot);
