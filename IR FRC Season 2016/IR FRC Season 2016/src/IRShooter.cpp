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
	shootingWheel2.SetInverted(true);
}

void IRShooter::Shoot()
{
	shootingWheel1.SetSpeed(1);
	shootingWheel2.SetSpeed(1);
}

void IRShooter::ShootingSequence()
{
	Shoot();
	intake.SetSpeed(-0.7);
	Wait(1);
	StopInTake();
	TakeIn();
	Wait(4);
	StopInTake();
	Wait(1);
	StopShoot();
}

void IRShooter::StopShoot()
{
	shootingWheel1.SetSpeed(0);
	shootingWheel2.SetSpeed(0);
}

void IRShooter::CurvedShoot(float curve)
{
	if(curve<0 )
	{
		shootingWheel1.SetSpeed(1+curve);
		shootingWheel2.SetSpeed(1);
	}

	else if(curve>0)
	{
		shootingWheel1.SetSpeed(1);
		shootingWheel2.SetSpeed(1-curve);
	}
}

void IRShooter::TakeIn()
{
	intake.SetSpeed(1);
}

void IRShooter::TakeOut()
{
	intake.SetSpeed(-1);
}

void IRShooter::StopInTake()
{
	intake.SetSpeed(0);
}
