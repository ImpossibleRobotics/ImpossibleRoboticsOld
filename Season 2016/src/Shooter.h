/*
 * Shooter.h
 *
 *  Created on: 15 feb. 2016
 *      Author: Dylan Vos
 */

#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

#include "WPILIB.h"

class Shooter {
public:
	Shooter(uint32_t shootingWheel1Channel, uint32_t shootingWheel2Channel, uint32_t intakeChannel);

	void Shoot();
	void takeIn();

protected:
	Spark shootingWheel1, shootingWheel2;
	Victor intake;
};

#endif /* SRC_SHOOTER_H_ */
