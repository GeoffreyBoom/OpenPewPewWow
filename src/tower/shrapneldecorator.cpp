/*
 * shrapneldecorator.cpp
 *
 *  Created on: Nov 21, 2014
 *      Author: geoffrey
 */

#include "shrapneldecorator.h"

using namespace std;
ShrapnelDecorator::ShrapnelDecorator(BasicTower* decoratedTower)
  : TowerDecorator(decoratedTower){}

double ShrapnelDecorator::getSplashRadius() {
  return 100 + TowerDecorator::getSplashRadius();
}

int ShrapnelDecorator::getDamage() {
  return 1 + TowerDecorator::getDamage();
}

string ShrapnelDecorator::getName() {
  return "Explosive " + TowerDecorator::getName() + " That Throws Shrapnel";
}
