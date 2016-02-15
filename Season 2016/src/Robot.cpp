#include "WPILib.h"
#include "../IRLibrary/IRLib.h"
#include "Shooter.cpp"


/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public SampleRobot
{
	IRRobotDrive myDrive;
	IRJoystick joystick;
	Shooter shooter;

public:

	Robot() :
		myDrive(0, 1, 2, 3),
		joystick(0),
		shooter(4,5,6)
	{

	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
		myDrive.Drive(0.5, 0.2);
		myDrive.Drive(0.5, -0.2);
	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			myDrive.ArcadeDrive(joystick); // drive with arcade style (use right stick)
			Wait(0.005);				// wait for a motor update time
		}
	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
		shooter.intake();
		Wait(100);
		shooter.Shoot();
	}
};

START_ROBOT_CLASS(Robot);
