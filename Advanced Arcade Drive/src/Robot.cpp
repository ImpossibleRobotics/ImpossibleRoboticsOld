#include "WPILib.h"
#include "ToteLifter.h"

class Robot: public SampleRobot
{
	Talon frontLeft, frontRight, rearLeft, rearRight;
	Joystick arcadeStick, gamePad;

	ToteLifter toteLift;

	Timer autoTimer;


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
		toteLift(4, 0, 1, 2),
		autoTimer()
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

	void Autonomous()
	{
		//Totelift control
		toteLift.StackUp();
		while(!toteLift.CheckLift())
		{
			Wait(UpdatePeriod);
		}
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

	void DriveForward(double time, float power)
	{
		autoTimer.Start();
		while(autoTimer.Get() < time)
		{
			frontLeft.Set(power);
		    rearLeft.Set(power);
			frontRight.Set(-1*power);
			rearRight.Set(-1*power);
		}
		autoTimer.Stop();
		autoTimer.Reset();
	}

	void DriveBackward(double time, float power)
		{
			autoTimer.Start();
			while(autoTimer.Get() < time)
			{
				frontLeft.Set(-1 * power);
			    rearLeft.Set(-1 * power);
				frontRight.Set(power);
				rearRight.Set(power);
			}
			autoTimer.Stop();
			autoTimer.Reset();
		}

	void TurnRight(double time, float power)
	{
		TurnLeft(time, -1*(power));

	}

	void TurnLeft(double time, float power)
	{
		autoTimer.Start();
		while(autoTimer.Get() < time)
		{
			frontLeft.Set(-power);
			rearLeft.Set(-power);
			frontRight.Set(-power);
			rearRight.Set(-power);
		}
		autoTimer.Stop();
		autoTimer.Reset();
	}

};

START_ROBOT_CLASS(Robot);
