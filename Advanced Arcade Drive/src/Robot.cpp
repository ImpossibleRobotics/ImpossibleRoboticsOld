#include "WPILib.h"
#include "ToteLifter.h"

class Robot: public SampleRobot
{
	Talon frontLeft, frontRight, rearLeft, rearRight;
	Joystick arcadeStick, gamePad;

	ToteLifter toteLift;


	double ExpirationTime = 0.1;
	double UpdatePeriod = 0.005;
	double SpeedModifier = 0;
	double SpeedModifierLeft = 0;
	double SpeedModifierRight = 0;

public:
	Robot() :
		frontLeft(1),
		frontRight(3),
		rearLeft(0),
		rearRight(2),
		arcadeStick(0),
		gamePad(1),
		toteLift(4, 0, 1, 2)
	{
		//Enable safety for all motors
		frontLeft.SetSafetyEnabled(true);
		frontRight.SetSafetyEnabled(true);
		rearLeft.SetSafetyEnabled(true);
		rearRight.SetSafetyEnabled(true);

		//Set Expiration Time for all motors
		frontLeft.SetExpiration(ExpirationTime);
		frontRight.SetExpiration(ExpirationTime);
		rearLeft.SetExpiration(ExpirationTime);
		rearRight.SetExpiration(ExpirationTime);
	}
	// drive functions
	 void forward(int time, float power) {
	  Timer *autonTimer;
	  autonTimer = new Timer();
	  autonTimer->Start();

	  while(autonTimer->Get() > time){
	   frontLeft.Set(-1.2*power);
	   rearLeft.Set(-1.2*power);
	   frontRight.Set(power);
	   rearRight.Set(power);
	  }
	  autonTimer->Reset();
	 }

	 void left(int time, float power) {
	  Timer *autonTimer;
	  autonTimer = new Timer();
	  autonTimer->Start();

	  while(autonTimer->Get() > time){
	   frontLeft.Set(power);
	   rearLeft.Set(power);
	   frontRight.Set(power);
	   rearRight.Set(power);
	  }
	  autonTimer->Reset();
	 }

 void right(int time, int power){
	  left(time, -power);
	 }

	 void Autonomous(){
	  forward(1, 0.4);
	  toteLift.StackUp();
	  forward(1,0);
	  toteLift.StackTotes();
	  forward(1,-0.2);
	 }

	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			//Check totelift
			toteLift.CheckLift();


			if(gamePad.GetRawButton(1) == 1)
			{
				toteLift.StackUp();
			}
			if(gamePad.GetRawButton(2) == 1)
			{
				toteLift.StackDown();
			}
			if(gamePad.GetRawButton(3) == 1)
			{
				toteLift.StackTotes();
			}

			//Calculate SpeedModifier using given input from throttle
			SpeedModifier = (arcadeStick.GetThrottle() - 1)/-2;
			//Calculate SpeedModifiers for the left and right motors based on inputs
			SpeedModifierLeft = arcadeStick.GetY() - arcadeStick.GetX();
			SpeedModifierRight = arcadeStick.GetY() + arcadeStick.GetX();

			//Invert Left Motors
			SpeedModifierLeft *= -1;

			//Set speed of motors
			frontLeft.Set(SpeedModifier*SpeedModifierLeft);
			rearLeft.Set(SpeedModifier*SpeedModifierLeft);
			frontRight.Set(SpeedModifier*SpeedModifierRight);
			rearRight.Set(SpeedModifier*SpeedModifierRight);

			SmartDashboard:: PutNumber("SpeedModifier", SpeedModifier);
			SmartDashboard:: PutNumber("SpeedModifierLeft", SpeedModifierLeft);
			SmartDashboard:: PutNumber("SpeedModifierRight", SpeedModifierRight);
			SmartDashboard:: PutNumber("Total speed Left", SpeedModifier * SpeedModifierLeft);
			SmartDashboard:: PutNumber("Total speed Right", SpeedModifier * SpeedModifierRight);

			Wait(UpdatePeriod);
		}
	}

};

START_ROBOT_CLASS(Robot);
