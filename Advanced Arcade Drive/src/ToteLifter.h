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
	bool stackingDown;
	bool inUse;

public:

	ToteLifter(int portMotor = 4, int portTopMax = 0, int portBottomMax = 1, int portHaltPoint = 2):
		toteLift(portMotor),
		topMax(portTopMax),
		bottomMax(portBottomMax),
		haltPoint(portHaltPoint),
		stackCounter(0),
		stackingDown(false),
		inUse(false)
	{
	}

	void CheckLift()
	{
		SmartDashboard:: PutBoolean("Top of the lift", topMax.Get());
		SmartDashboard:: PutBoolean("Bottom of the lift", bottomMax.Get());
		SmartDashboard:: PutBoolean("Halt point of the lift", haltPoint.Get());
		SmartDashboard:: PutBoolean("Is the elevator in use", inUse);
		SmartDashboard:: PutNumber("Stack Counter", stackCounter);
		SmartDashboard:: PutNumber("Motor Lift", toteLift.Get());
		if(stackingDown)
		{
			if((!topMax.Get() || !bottomMax.Get()) && inUse)
			{
				Stop();
				stackingDown = false;
				inUse = false;
			}
		}
		else
		{
			if((!haltPoint.Get() || !topMax.Get() || !bottomMax.Get()) && inUse)
			{
				Stop();
				inUse = false;
			}
		}
	}

	void StackUp()
	{
		if(topMax.Get() && inUse == false)
		{
			inUse = true;
			toteLift.Set(0.5);
			stackCounter++;
		}
	}

	void StackDown()
	{
		if(bottomMax.Get() && inUse == false && stackCounter > 0)
		{
			inUse = true;
			toteLift.Set(-0.5);
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
