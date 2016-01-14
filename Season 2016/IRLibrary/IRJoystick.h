/*
 * IRJoystick.h
 *
 *  Created on: 14 jan. 2016
 *      Author: Dylan Vos
 */

#ifndef IRLIBRARY_IRJOYSTICK_H_
#define IRLIBRARY_IRJOYSTICK_H_

#include "WPILIB.h"

class IRJoystick
{
public:
	static const uint32_t kDefaultThrottleAxis = 3;

	IRJoystick(uint32_t port);

	float GetY();
	float GetX();
	float GetZ();

	float GetTwist();
	float GetRawAxis(uint32_t axis);

	float GetThrottle();
	float GetLeveledThrottle();

	bool GetTrigger();
	bool GetTop();
	bool GetBumper();

	bool GetRawButton(uint32_t button);

	int GetPOV();

protected:
	Joystick joystick;

};

#endif /* IRLIBRARY_IRJOYSTICK_H_ */
