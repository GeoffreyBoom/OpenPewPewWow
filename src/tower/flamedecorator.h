/*
 * flamedecorator.h
 * //increases damage, splash radius, lasting damage, and damage time
 *  Created on: Nov 20, 2014
 *      Author: geoffrey
 */

#ifndef FLAMEDECORATOR_H_
#define FLAMEDECORATOR_H_

#include "towerdecorator.h"

namespace std {

//increases damage, splash radius, lasting damage, and damage time
class FlameDecorator: public TowerDecorator {

public:
  FlameDecorator(BasicTower *decoratedTower);
  virtual int getDamage();
  virtual double getSplashRadius();
  virtual int getLastingDamage();
  virtual int getDamageTime();
  virtual string getName();
};

} /* namespace std */

#endif /* FLAMEDECORATOR_H_ */
