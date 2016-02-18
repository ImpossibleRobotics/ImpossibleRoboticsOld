/*
 * IRShooter.cpp
 *
 *  Created on: 18 feb. 2016
 *      Author: Dylan Vos
 */

#include <IRShooter.h>

IRShooter::IRShooter(uint32_t shootingWheel1Channel, uint32_t shootingWheel2Channel, uint32_t intakeChannel) :
	shootingWheel1(shootingWheel1Channel),
	shootingWheel2(shootingWheel2Channel),
	intake(intakeChannel)
{

}

void IRShooter::Shoot()
{
	shootingWheel1.SetSpeed(1);
	shootingWheel2.SetSpeed(1);
	Wait(10);
	shootingWheel1.SetSpeed(0);
	shootingWheel2.SetSpeed(0);
}

void IRShooter::takeIn()
{
	intake.SetSpeed(1);
	Wait(10);
	intake.SetSpeed(0);
}
