/*
 * sniperdecorator.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: geoffrey
 */

#include "sniperdecorator.h"

SniperDecorator::SniperDecorator(BasicTower *decoratedTower)
: TowerDecorator(decoratedTower){}

double SniperDecorator::getRange(){
  return 20 + TowerDecorator::getRange();
}

string SniperDecorator::getName(){
  return "Sniping " + TowerDecorator::getName();
}




