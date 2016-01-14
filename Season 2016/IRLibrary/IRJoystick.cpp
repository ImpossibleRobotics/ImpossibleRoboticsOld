/*
 * IRJoystick.cpp
 *
 *  Created on: 14 jan. 2016
 *      Author: Dylan Vos
 */

#include "IRJoystick.h"

#include "WPILIB.h"

IRJoystick::IRJoystick(uint32_t port) :
	joystick(port)
{}

float IRJoystick::GetX()
{
	return joystick.GetX();
}

float IRJoystick::GetY()
{
	return joystick.GetY();
}

float IRJoystick::GetZ()
{
	return joystick.GetZ();
}


float IRJoystick::GetRawAxis(uint32_t axis)
{
	return joystick.GetRawAxis(axis);
}

float IRJoystick::GetTwist()
{
	return joystick.GetTwist();
}

float IRJoystick::GetThrottle()
{
	return joystick.GetThrottle();
}

float IRJoystick::GetLeveledThrottle()
{
	return (joystick.GetThrottle() - 1) / -2;
}

bool IRJoystick::GetRawButton(uint32_t button)
{
	return joystick.GetRawButton(button);
}

bool IRJoystick::GetTrigger()
{
	return joystick.GetTrigger();
}

bool IRJoystick::GetTop()
{
	return joystick.GetTop();
}

bool IRJoystick::GetBumper()
{
	return joystick.GetBumper();
}

int IRJoystick::GetPOV()
{
	return joystick.GetPOV();
}
