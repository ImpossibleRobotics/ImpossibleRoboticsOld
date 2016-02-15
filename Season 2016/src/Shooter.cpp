/*
 * Shooter.cpp
 *
 *  Created on: 15 feb. 2016
 *      Author: Dylan Vos
 */

#include <Shooter.h>

#include "WPILIB.h"

Shooter::Shooter(uint32_t shootingWheel1Channel, uint32_t shootingWheel2Channel, uint32_t intakeChannel) :
	shootingWheel1(shootingWheel1Channel),
	shootingWheel2(shootingWheel2Channel),
	intake(intakeChannel)
{

}

void Shooter::Shoot()
{
	shootingWheel1.SetSpeed(1);
	shootingWheel2.SetSpeed(1);
	Wait(10);
	shootingWheel1.SetSpeed(0);
	shootingWheel2.SetSpeed(0);
}

void Shooter::takeIn()
{
	intake.SetSpeed(1);
	Wait(10);
	intake.SetSpeed(0);
}

