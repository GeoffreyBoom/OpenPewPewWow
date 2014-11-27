/*
 * shrapneldecorator.h
 *
 *  Created on: Nov 21, 2014
 *      Author: geoffrey
 */

#ifndef SHRAPNELDECORATOR_H_
#define SHRAPNELDECORATOR_H_

#include "towerdecorator.h"

using namespace std;

class ShrapnelDecorator: public TowerDecorator {
public:
  ShrapnelDecorator(BasicTower *decoratedTower);
  virtual double getSplashRadius();
  virtual int getDamage();
  virtual string getName();
};

#endif /* SHRAPNELDECORATOR_H_ */
