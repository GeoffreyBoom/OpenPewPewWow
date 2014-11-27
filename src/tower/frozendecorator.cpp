/*
 * frozendecorator.cpp
 *
 *  Created on: Nov 21, 2014
 *      Author: geoffrey
 */

#include "frozendecorator.h"

using namespace std;

FrozenDecorator::FrozenDecorator(BasicTower* decoratedTower)
:    TowerDecorator(decoratedTower){}

int FrozenDecorator::getSlowAmmount(){
  return 5 + TowerDecorator::getSlowAmmount();
}
int FrozenDecorator::getSlowTime(){
  return 100 + TowerDecorator::getSlowTime();
}
string FrozenDecorator::getName(){
  return "Freezing " + TowerDecorator::getName() + " That Lets it Go Like Elsa";
}

