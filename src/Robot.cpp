#include "WPIlib.h"
#include "Tankdrive.h"
#include "Constants.h"
#include "Pneumatics.h"
#include "Vision.h"

class Robot: public SampleRobot
{
private:
	Tankdrive tankdrive;
	SmartDashboard *dash;
	Joystick joystickleft;
	Joystick joystickright;
	Joystick joystickarm;
	Pneumatics pneumatics;
	Vision vision;
	cs::UsbCamera camera;
	Talon lights;
	float VisionX;
	float difference;
public:
	Robot():
		tankdrive(1,2,0,3,4,5), // 0 is left 1 is right
		dash (),
		joystickleft (1),
		joystickright (0),
		joystickarm (2),
		pneumatics(0,1),
		vision(),
		camera(),
		lights(6)
	{
		dash->init();
		VisionX = 0;
		difference = 0;
	}

	void RobotInit()
	{
		camera = CameraServer::GetInstance()->StartAutomaticCapture();
		camera.SetBrightness(45);
		camera.SetExposureManual(0);
		camera.SetResolution(320,240);
		camera.SetFPS(25);
	}
	void Autonomous()
	{
		// to refresh the camera
		Robot::RobotInit();
		lights.Set(0.33 * (1-joystickleft.GetZ()));
		Wait(1.0);
		do
		{
			vision.Update();
			VisionX = (vision.GetX(0) + vision.GetX(1)) /2;
			difference = (VisionX - 160) * PCONSTANT;
			if (vision.GetNumContours() == 0)
				tankdrive.DirectDrive(0,0);
			else
			tankdrive.DirectDrive(AUTODRIVE * (1 - difference), (AUTODRIVE * (1 + difference)));
		} while (IsAutonomous());

	}

	void OperatorControl()
	{
		// to refresh the camera
		Robot::RobotInit();
		pneumatics.compstop();
		pneumatics.gearchange(0);	// sets robot settings at start
		tankdrive.drive(0,0);

		while (IsOperatorControl() && IsEnabled())
		{
			camera.SetBrightness(((1 + joystickleft.GetZ()) / 2) * 100);
			//lights.Set(0.33 * (1-joystickleft.GetZ()));
			for(int i = 0; i < 10; ++i)
			{
				tankdrive.Throttle((joystickright.GetZ()-1)/2);
				tankdrive.drive(joystickright.GetY(), joystickleft.GetY());
				Wait(0.01);
			}
			if(joystickarm.GetRawButton(2))
				pneumatics.compstart();
			else if(joystickarm.GetRawButton(3))
				pneumatics.compstop();
			if(joystickarm.GetRawButton(6))
				pneumatics.gearchange(1); // high gear
			else if(joystickarm.GetRawButton(7))
				pneumatics.gearchange(0); //low gear ( BY TORIIIIII )
			dash->PutNumber("version number", VERSION);

			dash->PutNumber("Light intensity", 0.33 * (1-joystickleft.GetZ()));
		}
	}
};
START_ROBOT_CLASS(Robot);
