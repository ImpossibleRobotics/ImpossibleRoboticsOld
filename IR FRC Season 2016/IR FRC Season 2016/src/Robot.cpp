#include "WPILib.h"
#include "../IRLibrary/IRLib.h"


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

	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";

public:

	Robot() :
		myDrive(0, 1, 2, 3),
		joystick(0),
		chooser()
	{
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
		/*
		std::string autoSelected = *((std::string*)chooser->GetSelected());
		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
			std::cout << "Running custom Autonomous" << std::endl;
		} else {
			//Default Auto goes here
			std::cout << "Running default Autonomous" << std::endl;
		}
		*/


		myDrive.Drive(0.5, 0.2);
		Wait(10);
		myDrive.Drive(0.5, -0.2);
		Wait(10);
		myDrive.Drive(0.0, 0.0);
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
	}
};

START_ROBOT_CLASS(Robot);
