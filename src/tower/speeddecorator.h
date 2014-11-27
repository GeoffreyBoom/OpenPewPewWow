/*
 * speeddecorator.h
 *
 *  Created on: Nov 26, 2014
 *      Author: geoffrey
 */

#ifndef SPEEDDECORATOR_H_
#define SPEEDDECORATOR_H_

#include "towerdecorator.h"

namespace std {

class SpeedDecorator: public TowerDecorator {
public:
  SpeedDecorator(BasicTower *decoratedTower);
  virtual string getName();
  virtual int getSpeed();
};

} /* namespace std */

#endif /* SPEEDDECORATOR_H_ */
