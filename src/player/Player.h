/*
 * Player.h

 *
 *  Created on: Nov 4, 2014
 *      Author: Samuel
 */
#pragma once
#ifndef SOURCE_PLAYER_PLAYER_H_
#define SOURCE_PLAYER_PLAYER_H_
#include "../subject/subject.h"
#include "../creep/creep.h"
#include "stdio.h"
#include <climits>

class Player:Subject {

public:
	bool damagePlayer(Creep* );
	void muchCheat();


	void deposit(int amount){
		if(amount > 0)
			this->setMoney(currency+=amount);
	}
	bool withdraw(int amount);

	static Player * getPlayer(){
	  static Player* gamer = NULL;
		if(gamer == NULL)
		  {
				gamer = new Player();
			}
		return gamer;
	}

    	void subLife(){

	if ( this->life >0)
		{
			this->life -= 1;
		}

	}

	bool isAlive(){
        return (this->life != 0);
	}



	bool setMoney(int m)
	{
		if(m >= 0)
		{
			this->currency = m;
      cout << "\n----money is now:"<< getMoney() << "----"<< endl;
			return true;
		}
		else
		{
			return false;
		}

	};

	int getLife()
	{
		return this->life;
	}

	bool setLife(int l){
		if ( l >0)
		{
			this->life= l;
			return true;
		}
		else
		{
			this->life = 0;
			return false;
		}
	}
	int incTick();
	int getTick();
	void setEndPosX(int);
	void setEndPosY(int);
	int getEndPosX();
	int getEndPosY();
	int getMoney(){return this->currency;}
	void reset();

	virtual ~Player();
private:
	int initialMoney = 500;
	int initialLife = 20;
	int initialTick = 0;
	int tick = 0;
	int endPosX=0;
	int endPosY=0;
	int currency;
	int life;
	Player();

  void setTick(int);





};


#endif /* SOURCE_PLAYER_PLAYER_H_ */
