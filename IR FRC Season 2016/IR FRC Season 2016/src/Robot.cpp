#include "WPILib.h"
#include "../IRLibrary/IRLib.h"
#include "IRShooter.h"


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
	IRJoystick joystick,gamePad;
	IRShooter irshooter;

	SendableChooser *chooser;
	const std::string autoTestShoot = "Test Shooter";
	const std::string autoTestDrive = "Test Driver";

public:

	Robot() :
		myDrive(0, 1, 2, 3),
		joystick(0),
		gamePad(1),
		irshooter(4,5,6),
		chooser()
	{
		chooser = new SendableChooser();
		chooser->AddDefault(autoTestShoot, (void*)&autoTestShoot);
		chooser->AddObject(autoTestDrive, (void*)&autoTestDrive);
		SmartDashboard::PutData("Auto Modes", chooser);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{

		std::string autoSelected = *((std::string*)chooser->GetSelected());
		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if(autoSelected == autoTestDrive){
			//Custom Auto goes here
			std::cout << "Running " + autoTestDrive << std::endl;

			myDrive.Drive(0.1, 0.0);
			Wait(10);
			myDrive.Drive(0.0, 0.0);
			Wait(10);
			myDrive.Drive(0.2, 1);
			Wait(10);
			myDrive.Drive(0.2, -1);
			Wait(10);
			myDrive.Drive(0.0, 0.0);
		}
		else {
			//Default Auto goes here
			//place in front of low bar, drive forward, turn right, shoot
			std::cout << "Running " + autoTestShoot << std::endl;
			irshooter.takeIn();
			Wait(10);
			myDrive.Drive(0.5, 0.0);
			Wait(10);
			myDrive.Drive(0.2, 0.2);
			Wait(10);
			irshooter.Shoot();
		}
	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			myDrive.ArcadeDrive(joystick); // drive with arcade style (use right stick)

			if(gamePad.GetRawButton(8)) irshooter.Shoot();
			if(gamePad.GetRawButton(7)) irshooter.takeIn();
			if(gamePad.GetRawButton(1)) irshooter.CurvedShoot(0.2);
			if(gamePad.GetRawButton(2)) irshooter.CurvedShoot(-0.2);
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
