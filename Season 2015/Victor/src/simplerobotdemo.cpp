#include "WPILib.h"
#include "ToteLifter.h"

class SimpleRobotDemo: public SimpleRobot
{
	Talon frontLeft, frontRight, rearLeft, rearRight;
	Joystick arcadeStick, gamePad;

	ToteLifter toteLift;

	Timer autoTimer;
	Timer coastTimer;


	double ExpirationTime = 0.1;
	double UpdatePeriod = 0.005;
	double SpeedModifier = 0;
	double SpeedModifierLeft = 0;
	double SpeedModifierRight = 0;
	double TempValueSave = 0;
	double CoastValue = 0.1;

	/*
	 * 1: Grijs	3: Blauw
	 * 2: Wit	4: Geel
	 *
	 *
	 *
	 */

public:
	SimpleRobotDemo() :
		frontLeft(1),
		frontRight(3),
		rearLeft(2),
		rearRight(4),
		arcadeStick(1),
		gamePad(2),
		toteLift(5, 0, 1, 2),
		autoTimer(),
		coastTimer()
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
//		toteLift.StackUp();
//		while(!toteLift.CheckLift())

		//vooruit zonder tote, komt 177 cm vooruit
		forward(2.5,0.3);

		{
			Wait(UpdatePeriod);
		}

		// tote on the ground start against allience wall
//		forward(5.5,0.3);
//
//		{
//			Wait(UpdatePeriod);
//		}
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
			if(gamePad.GetRawButton(7) == 1)
 			{
 				toteLift.manualStop();
 			}
 
 
 
 
			if(gamePad.GetRawButton(6) == 1)
 			{
 				toteLift.manualUp();
 			}
			else if(gamePad.GetRawButton(5) == 1)
 			{
 				toteLift.manualDown();
 			}
			/*else
			{
				toteLift.Stop();
			}*/

			TempValueSave = SpeedModifier;

			//Calculate SpeedModifier using given input from throttle
			SpeedModifier = (arcadeStick.GetThrottle() - 1)/-2;
			//Calculate SpeedModifiers for the left and right motors based on inputs
			SpeedModifierLeft = arcadeStick.GetY() - arcadeStick.GetX();
			SpeedModifierRight = arcadeStick.GetY() + arcadeStick.GetX();

			//Invert Left Motors
			SpeedModifierLeft *= -1;

//			if(arcadeStick.GetTrigger())
//			{
//				if(!coastTimer.m_running)
//				{
//					coastTimer.Start();
//				}
//				else
//				{
//					TempValueSave *= CoastValue * coastTimer.Get();
//				}
//				SpeedModifier = TempValueSave;
//				if(SpeedModifier < CoastValue)
//				{
//					SpeedModifier = 0;
//				}
//			}
//			else
//			{
//				coastTimer.Stop();
//				coastTimer.Reset();
//			}

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

	void forward(double time, float power)
	{
		autoTimer.Start();
		while(autoTimer.Get() < time)
		{
			frontLeft.Set(power);
		    rearLeft.Set(power);
			frontRight.Set(-0.77*power);
			rearRight.Set(-0.77*power);
		}
		autoTimer.Stop();
		autoTimer.Reset();
	}

	void backward(double time, float power)
		{
			autoTimer.Start();
			while(autoTimer.Get() < time)
			{
				frontLeft.Set(-1* power);
			    rearLeft.Set(-1* power);
				frontRight.Set(power);
				rearRight.Set(power);
			}
			autoTimer.Stop();
			autoTimer.Reset();
		}

	void right(double time, float power)
	{
		left(time, -1*(power));

	}

	void left(double time, float power)
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

START_ROBOT_CLASS(SimpleRobotDemo);
