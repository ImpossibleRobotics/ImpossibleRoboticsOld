/*
 * ToteLifter.h
 *
 *  Created on: 30 jan. 2015
 *      Author: Dylan
 */

#ifndef SRC_TOTELIFTER_H_
#define SRC_TOTELIFTER_H_

class ToteLifter {

	Victor toteLift;
	DigitalInput topMax, bottomMax, haltPoint;
	int stackCounter;
	double switchDelay;
	bool stackingDown;
	bool inUse;
	Timer liftTimer;

public:

	ToteLifter(int portMotor = 4, int portTopMax = 0, int portBottomMax = 1, int portHaltPoint = 2):
		toteLift(portMotor),
		topMax(portTopMax),
		bottomMax(portBottomMax),
		haltPoint(portHaltPoint),
		stackCounter(0),
		switchDelay(0.5),
		stackingDown(false),
		inUse(false),
		liftTimer()
	{
	}

	bool CheckLift()
	{
		SmartDashboard:: PutBoolean("Top of the lift", topMax.Get());
		SmartDashboard:: PutBoolean("Bottom of the lift", bottomMax.Get());
		SmartDashboard:: PutBoolean("Halt point of the lift", haltPoint.Get());
		SmartDashboard:: PutBoolean("Is the elevator in use", inUse);
		SmartDashboard:: PutNumber("Stack Counter", stackCounter);
		SmartDashboard:: PutNumber("Motor Lift", toteLift.Get());
		SmartDashboard:: PutNumber("Lift Timer", liftTimer.Get());
		if(liftTimer.Get() > switchDelay)
		{
			if(stackingDown)
			{
				if((!topMax.Get() || !bottomMax.Get()) && inUse)
				{
					Stop();
					stackingDown = false;
					inUse = false;
					liftTimer.Reset();
					return true;
				}
			}
			else
			{
				if((!haltPoint.Get() || !topMax.Get() || !bottomMax.Get()) && inUse)
				{
					Stop();
					inUse = false;
					liftTimer.Reset();
					return true;
				}
			}
			liftTimer.Stop();
			return false;
		}
		return false;
	}

	void StackUp()
	{
		if(topMax.Get() && inUse == false)
		{
			liftTimer.Start();
			inUse = true;
			toteLift.Set(-0.750);
			stackCounter++;
		}
	}

	void StackDown()
	{
		if(bottomMax.Get() && inUse == false && stackCounter > 0)
		{
			liftTimer.Start();
			inUse = true;
			toteLift.Set(0.500);
			stackCounter--;
		}
	}

	void StackTotes()
	{
		StackDown();
		stackingDown = true;
		stackCounter = 0;
	}

	void Stop()
	{
		toteLift.Set(0);
	}
};

#endif /* SRC_TOTELIFTER_H_ */
