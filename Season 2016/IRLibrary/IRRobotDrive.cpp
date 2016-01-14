/*
 * IRRobotDrive.cpp
 *
 *  Created on: 12 jan. 2016
 *      Author: Dylan Vos
 */

#include "IRRobotDrive.h"

#include "WPILIB.h"

#include "IRJoystick.h"

#undef max

IRRobotDrive::IRRobotDrive(uint32_t frontLeftMotorChannel, uint32_t rearLeftMotorChannel,
				uint32_t frontRightMotorChannel, uint32_t rearRightMotorChannel) :
				m_frontLeftMotor(frontLeftMotorChannel),
				m_frontRightMotor(frontRightMotorChannel),
				m_rearLeftMotor(rearLeftMotorChannel),
				m_rearRightMotor(rearRightMotorChannel)
{
	SetOutputMotors(0.0, 0.0);
}

void IRRobotDrive::ArcadeDrive(GenericHID *stick)
{
	ArcadeDrive(stick->GetY(), stick->GetX());
}

void IRRobotDrive::ArcadeDrive(GenericHID &stick)
{
	ArcadeDrive(stick.GetY(), stick.GetX());
}

void IRRobotDrive::ArcadeDrive(IRJoystick *stick)
{
	ArcadeDrive(stick->GetY(), stick->GetX());
}

void IRRobotDrive::ArcadeDrive(IRJoystick &stick)
{
	ArcadeDrive(stick.GetY(), stick.GetX());
}

void IRRobotDrive::ArcadeDrive(float moveValue, float rotateValue)
{
	ArcadeDrive(moveValue, rotateValue, 1.0);
}

void IRRobotDrive::ArcadeDrive(float moveValue, float rotateValue, float modifierValue)
{
	float leftMotorsOutput = -(modifierValue * (moveValue - rotateValue));
	float rightMotorsOutput = modifierValue * (moveValue + rotateValue);

	SetOutputMotors(leftMotorsOutput, rightMotorsOutput);
}




void IRRobotDrive::SetOutputMotors(float output)
{
	m_rearLeftMotor.Set(output, m_syncGroup);
	m_rearRightMotor.Set(output, m_syncGroup);
	m_frontLeftMotor.Set(output, m_syncGroup);
	m_frontRightMotor.Set(output, m_syncGroup);
}

void IRRobotDrive::SetOutputMotors(float leftOutput, float rightOutput)
{
	m_rearLeftMotor.Set(leftOutput, m_syncGroup);
	m_rearRightMotor.Set(rightOutput, m_syncGroup);
	m_frontLeftMotor.Set(leftOutput, m_syncGroup);
	m_frontRightMotor.Set(rightOutput, m_syncGroup);
}

