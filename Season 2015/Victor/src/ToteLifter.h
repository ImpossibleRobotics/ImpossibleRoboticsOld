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
	double motorResistance;
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
		motorResistance(-0.2), //Set motorResistance
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
			toteLift.Set(0.500);
			stackCounter++;
		}
	}

	void StackDown()
	{
		if(bottomMax.Get() && inUse == false && stackCounter > 0)
		{
			liftTimer.Start();
			inUse = true;
			toteLift.Set(-0.850);
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
		if(stackCounter > 0)
		{
			toteLift.Set(motorResistance * stackCounter);
		}
		else
		{
			toteLift.Set(0);
		}
	}

	void manualUp()
	{
		toteLift.Set(0.500);
		if(!haltPoint.Get())
		{
			stackCounter++;
		}
	}

	void manualDown()
	{
		toteLift.Set(-0.850);
		if(!haltPoint.Get() && stackCounter > 0)
		{
			stackCounter--;
		}
	}

	void manualStop()
	{
		toteLift.Set(0);
		inUse = false;
	}
};

#endif /* SRC_TOTELIFTER_H_ */
