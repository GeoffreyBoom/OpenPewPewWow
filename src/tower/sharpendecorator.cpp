/*
 * sharpendecorator.cpp
 *
 *  Created on: Nov 21, 2014
 *      Author: geoffrey
 */

#include "sharpendecorator.h"

SharpenDecorator::SharpenDecorator(BasicTower* decoratedTower)
: TowerDecorator(decoratedTower){}

int SharpenDecorator::getDamage() {
  return 2 + TowerDecorator::getDamage();
}
string SharpenDecorator::getName(){
  return "Sharpened " + TowerDecorator::getName();
}
