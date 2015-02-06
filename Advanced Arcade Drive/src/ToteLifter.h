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
	int stackCounter;
	DigitalInput topMax, bottomMax, haltPoint;

public:

	ToteLifter(int portMotor = 4, int portTopMax = 0, int portBottomMax = 1, int portHaltPoint = 2):
		toteLift(portMotor),
		topMax(portTopMax),
		bottomMax(portBottomMax),
		haltPoint(portHaltPoint)
	{
		stackCounter = 0;
	}

	void StackUp()
	{
		if(!topMax.Get())
		{
			toteLift.Set(0.5);
			Wait(0.001);
			while(!haltPoint.Get() && !topMax.Get())
			{
				Wait(0.001);
			}
			toteLift.Set(0);
			stackCounter++;
		}
	}

	void StackDown()
	{
		if(!bottomMax.Get())
		{
			toteLift.Set(-0.5);
			Wait(0.001);
			while(!haltPoint.Get() && !bottomMax.Get())
			{
				Wait(0.001);
			}
			toteLift.Set(0);
			stackCounter--;
		}
	}

	void StackTotes()
	{
		for(int i = 0; i < stackCounter; i++)
		{
			StackDown();
		}
	}
};

#endif /* SRC_TOTELIFTER_H_ */
