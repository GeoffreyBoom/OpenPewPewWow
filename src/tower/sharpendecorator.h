/*
 * sharpendecorator.h
 *
 *  decorates the tower with extra power
 *
 *  Created on: Nov 21, 2014
 *      Author: geoffrey
 */

#ifndef SHARPENDECORATOR_H_
#define SHARPENDECORATOR_H_

#include "towerdecorator.h"

//decorates the tower with extra power
class SharpenDecorator : public TowerDecorator{
public:
  SharpenDecorator(BasicTower *decoratedTower);
  virtual int getDamage();
  virtual string getName();
};


#endif /* SHARPENDECORATOR_H_ */
