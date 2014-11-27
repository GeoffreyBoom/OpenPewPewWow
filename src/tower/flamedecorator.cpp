/*
 * flamedecorator.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: geoffrey
 */

#include "flamedecorator.h"

using namespace std;

FlameDecorator::FlameDecorator(BasicTower *decoratedTower)
: TowerDecorator(decoratedTower){}

int FlameDecorator::getDamage() {
  return 1 + TowerDecorator::getDamage();
}

double FlameDecorator::getSplashRadius() {
  return 10 + TowerDecorator::getSplashRadius();
}

int FlameDecorator::getLastingDamage() {
  return 1 + TowerDecorator::getLastingDamage();
}

int FlameDecorator::getDamageTime() {
  return 2 + TowerDecorator::getDamageTime();
}
string FlameDecorator::getName(){
  return "Flaming " + TowerDecorator::getName();
}
