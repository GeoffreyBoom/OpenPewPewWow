/*
 * sniperdecorator.h
 *
 *  Created on: Nov 24, 2014
 *      Author: geoffrey
 */

#ifndef SNIPERDECORATOR_H_
#define SNIPERDECORATOR_H_

#include "towerdecorator.h"

class SniperDecorator: public TowerDecorator {
public:
  SniperDecorator(BasicTower *decoratedTower);
  virtual double getRange();
  virtual string getName();
};

#endif /* SNIPERDECORATOR_H_ */
