/*
 * Player.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: Samuel
 */
#include "../creep/creep.h"
#include "Player.h"

void Player::setTick(int tick) {
  this->tick = tick;
}

Player::Player() {
	currency = initialMoney;
	life = initialLife;

}

Player::~Player() {
}

bool Player::damagePlayer(Creep * creep){
	return this->setLife( this->getLife() - creep->getPenalty() );
}
bool Player::withdraw(int amount)
{
	if( currency  <amount)
		return false;
	else
	{
		this->setMoney(currency-= amount);
		return true;
	}
}

void Player::muchCheat(){
  setMoney(getMoney() + 10000);
}

int Player::incTick(){
  if(tick == INT_MAX-10){
    tick = 0;
  }
  return ++tick;
}

int Player::getTick(){
  return tick;
}

void Player::reset() {
  getPlayer()->life = (initialLife);
  getPlayer()->currency = (initialMoney);
  getPlayer()->tick = (initialTick);
}


void Player::setEndPosX(int x){ this->endPosX = x;}
void Player::setEndPosY(int y){ this->endPosY = y;}
int Player::getEndPosX(){return endPosX;}
int Player::getEndPosY(){return endPosY;}
