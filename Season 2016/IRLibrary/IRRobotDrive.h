/*
 * IRRobotDrive.h
 *
 *  Created on: 12 jan. 2016
 *      Author: Dylan Vos
 */

#ifndef IRLIBRARY_IRROBOTDRIVE_H_
#define IRLIBRARY_IRROBOTDRIVE_H_

#include "WPILIB.h"

#include "IRJoystick.h"

class IRRobotDrive{
public:
	IRRobotDrive(uint32_t frontLeftMotorChannel, uint32_t rearLeftMotorChannel,
	             uint32_t frontRightMotorChannel, uint32_t rearRightMotorChannel);

	  void SetOutputMotors(float output);
	  void SetOutputMotors(float leftOutput, float rightOutput);

	  void ArcadeDrive(GenericHID *stick);
	  void ArcadeDrive(IRJoystick *stick);
	  void ArcadeDrive(GenericHID &stick);
	  void ArcadeDrive(IRJoystick &stick);
	  void ArcadeDrive(float moveValue, float rotateValue);
	  void ArcadeDrive(float moveValue, float rotateValue, float modifierValue);

protected:

	  Talon m_frontLeftMotor;
	  Talon m_frontRightMotor;
	  Talon m_rearLeftMotor;
	  Talon m_rearRightMotor;

	  uint8_t m_syncGroup = 0;
};

#endif /* IRLIBRARY_IRROBOTDRIVE_H_ */
