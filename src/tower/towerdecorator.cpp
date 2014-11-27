/*
 * towerdecorator.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: geoffrey
 */

#include "towerdecorator.h"

using namespace std;
TowerDecorator::TowerDecorator(BasicTower *decoratedTower)
: BasicTower(*decoratedTower){
  this->decoratedTower = decoratedTower;
}

TowerDecorator::~TowerDecorator() {
  delete this->decoratedTower;
}

double TowerDecorator::getRange(){
  return this->decoratedTower->getRange();
}
int TowerDecorator::getLevel(){
  return 1 + this->decoratedTower->getLevel();
}
int TowerDecorator::getSpeed(){
  return this->decoratedTower->getSpeed();
}
int TowerDecorator::getDamage(){
  return this->decoratedTower->getDamage();
}
int TowerDecorator::getBuyingPrice(){
  return this->decoratedTower->getBuyingPrice();
}
int TowerDecorator::getRefundValue(){
  return 10 + this->decoratedTower->getRefundValue();
}
int TowerDecorator::getUpgradePrice(){
  return 20 + this->decoratedTower->getUpgradePrice();
}
int TowerDecorator::getNumberOfTargets(){
  return this->decoratedTower->getNumberOfTargets();
}
double TowerDecorator::getSplashRadius(){
  return this->decoratedTower->getSplashRadius();
}
int TowerDecorator::getLastingDamage() {
  return this->decoratedTower->getLastingDamage();
}
int TowerDecorator::getSlowAmmount() {
  return this->decoratedTower->getSlowAmmount();
}
int TowerDecorator::getSlowTime() {
  return this->decoratedTower->getSlowTime();
}
int TowerDecorator::getDamageTime() {
  return this->decoratedTower->getDamageTime();
}
string TowerDecorator::getName(){
  return this->decoratedTower->getName();
}
int TowerDecorator::sell(){
  int buffer = this->getRefundValue();
  Player::getPlayer()->deposit(buffer);
  delete this;
  return buffer;
}

