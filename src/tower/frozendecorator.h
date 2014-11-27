/*
 * frozendecorator.h
 *
 *  Created on: Nov 21, 2014
 *      Author: geoffrey
 */

#ifndef FROZENDECORATOR_H_
#define FROZENDECORATOR_H_

#include "towerdecorator.h"


class FrozenDecorator: public TowerDecorator {
public:
  FrozenDecorator(BasicTower *decoratedTower);
  virtual int getSlowAmmount();
  virtual int getSlowTime();
  virtual string getName();
};

#endif /* FROZENDECORATOR_H_ */
