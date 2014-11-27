/*
 * speeddecorator.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: geoffrey
 */

#include "speeddecorator.h"

namespace std {

SpeedDecorator::SpeedDecorator(BasicTower *decoratedTower)
: TowerDecorator(decoratedTower){}

string SpeedDecorator::getName() {
  return "speedy" + TowerDecorator::getName();
}

int SpeedDecorator::getSpeed() {
  int speed = TowerDecorator::getSpeed()-1;
  if(speed > 0){
    return speed;
  }
  else{
    return 1;
  }
}

} /* namespace std */
