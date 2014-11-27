/*
 * towerdecorator.h
 *
 *  Created on: Nov 20, 2014
 *      Author: geoffrey
 */

#ifndef TOWERDECORATOR_H_
#define TOWERDECORATOR_H_

#include "basicTower.h"
#include "../player/Player.h"

using namespace std;
class TowerDecorator: public BasicTower {
protected:
  BasicTower *decoratedTower;
public:
  //wraps the tower in a tower-decorator
  TowerDecorator(BasicTower *decoratedTower);
  virtual ~TowerDecorator();
  virtual double getRange();
  virtual int getLevel();
  virtual int getSpeed();
  virtual int getDamage();
  virtual int getLastingDamage();
  virtual int getSlowAmmount();
  virtual int getSlowTime();
  virtual int getDamageTime();
  virtual int getBuyingPrice();
  virtual int getRefundValue();
  virtual int getUpgradePrice();
  virtual int getNumberOfTargets();
  virtual double getSplashRadius();
  virtual string getName();
  virtual int sell();
};

#endif /* TOWERDECORATOR_H_ */
