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


/**
 * Constructor for RobotDrive with 4 motors specified with channel numbers.
 * Set up parameters for a four wheel drive system where all four motor
 * pwm channels are specified in the call.
 * This call assumes Talons for controlling the motors.
 * @param frontLeftMotor Front left motor channel number. 0-9 are on-board,
 * 10-19 are on the MXP port
 * @param rearLeftMotor Rear Left motor channel number. 0-9 are on-board, 10-19
 * are on the MXP port
 * @param frontRightMotor Front right motor channel number. 0-9 are on-board,
 * 10-19 are on the MXP port
 * @param rearRightMotor Rear Right motor channel number. 0-9 are on-board,
 * 10-19 are on the MXP port
 */
IRRobotDrive::IRRobotDrive(uint32_t frontLeftMotorChannel, uint32_t rearLeftMotorChannel,
				uint32_t frontRightMotorChannel, uint32_t rearRightMotorChannel) :
				m_frontLeftMotor(frontLeftMotorChannel),
				m_frontRightMotor(frontRightMotorChannel),
				m_rearLeftMotor(rearLeftMotorChannel),
				m_rearRightMotor(rearRightMotorChannel)
{
	SetOutputMotors(0.0, 0.0);
}

/**
 * Arcade drive implements single stick driving.
 * Given a single Joystick, the class assumes the Y axis for the move value and
 * the X axis
 * for the rotate value.
 * (Should add more information here regarding the way that arcade drive works.)
 * @param stick The joystick to use for Arcade single-stick driving. The Y-axis
 * will be selected
 * for forwards/backwards and the X-axis will be selected for rotation rate.
 */
void IRRobotDrive::ArcadeDrive(GenericHID *stick)
{
	ArcadeDrive(stick->GetY(), stick->GetX());
}

/**
 * Arcade drive implements single stick driving.
 * Given a single Joystick, the class assumes the Y axis for the move value and
 * the X axis
 * for the rotate value.
 * (Should add more information here regarding the way that arcade drive works.)
 * @param stick The joystick to use for Arcade single-stick driving. The Y-axis
 * will be selected
 * for forwards/backwards and the X-axis will be selected for rotation rate.
 */
void IRRobotDrive::ArcadeDrive(GenericHID &stick)
{
	ArcadeDrive(stick.GetY(), stick.GetX());
}

/**
 * Arcade drive implements single stick driving.
 * Given a single IRJoystick, the class assumes the Y axis for the move value and
 * the X axis
 * for the rotate value.
 * (Should add more information here regarding the way that arcade drive works.)
 * @param stick The IRjoystick to use for Arcade single-stick driving. The Y-axis
 * will be selected
 * for forwards/backwards and the X-axis will be selected for rotation rate.
 */
void IRRobotDrive::ArcadeDrive(IRJoystick *stick)
{
	ArcadeDrive(stick->GetY(), stick->GetX());
}

/**
 * Arcade drive implements single stick driving.
 * Given a single IRJoystick, the class assumes the Y axis for the move value and
 * the X axis
 * for the rotate value.
 * (Should add more information here regarding the way that arcade drive works.)
 * @param stick The IRjoystick to use for Arcade single-stick driving. The Y-axis
 * will be selected
 * for forwards/backwards and the X-axis will be selected for rotation rate.
 */
void IRRobotDrive::ArcadeDrive(IRJoystick &stick)
{
	ArcadeDrive(stick.GetY(), stick.GetX());
}

/**
 * Arcade drive implements single stick driving.
 * This function lets you directly provide joystick values from any source.
 * @param moveValue The value to use for fowards/backwards
 * @param rotateValue The value to use for the rotate right/left
 */
void IRRobotDrive::ArcadeDrive(float moveValue, float rotateValue)
{
	ArcadeDrive(moveValue, rotateValue, 1.0);
}

/**
 * Arcade drive implements single stick driving.
 * This function lets you directly provide joystick values from any source.
 * @param moveValue The value to use for fowards/backwards
 * @param rotateValue The value to use for the rotate right/left
 * @param modifierValue The value to use for the speedmodifier
 */
void IRRobotDrive::ArcadeDrive(float moveValue, float rotateValue, float modifierValue)
{
	float leftMotorsOutput = -(modifierValue * (moveValue - rotateValue));
	float rightMotorsOutput = modifierValue * (moveValue + rotateValue);

	SetOutputMotors(leftMotorsOutput, rightMotorsOutput);
}

/** Set the speed of the right and left motors.
 * This is used once an appropriate drive setup function is called such as
 * TwoWheelDrive(). The motors are set to "leftOutput" and "rightOutput"
 * and includes flipping the direction of one side for opposing motors.
 * @param output The speed to send to the motors.
 */
void IRRobotDrive::SetOutputMotors(float output)
{
	m_rearLeftMotor.Set(output, m_syncGroup);
	m_rearRightMotor.Set(output, m_syncGroup);
	m_frontLeftMotor.Set(output, m_syncGroup);
	m_frontRightMotor.Set(output, m_syncGroup);
}

/** Set the speed of the right and left motors.
 * This is used once an appropriate drive setup function is called such as
 * TwoWheelDrive(). The motors are set to "leftOutput" and "rightOutput"
 * and includes flipping the direction of one side for opposing motors.
 * @param leftOutput The speed to send to the left side of the robot.
 * @param rightOutput The speed to send to the right side of the robot.
 */
void IRRobotDrive::SetOutputMotors(float leftOutput, float rightOutput)
{
	m_rearLeftMotor.Set(leftOutput, m_syncGroup);
	m_rearRightMotor.Set(rightOutput, m_syncGroup);
	m_frontLeftMotor.Set(leftOutput, m_syncGroup);
	m_frontRightMotor.Set(rightOutput, m_syncGroup);
}

