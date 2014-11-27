#include <stdio.h>
#include "boss.h"

//boss constructor implements the creep constructor, and inherits all creep methods
Boss::Boss(int waveNum, int startHP, int posX, int posY, int width, int height, string image, Path* path):Creep(waveNum, posX, posY, width, height, image, path)
{
	//Passing values to creep constructor

	this->setHitPoints(startHP);
	this->setDefense(10*(waveNum + BASEVAL));
	this->setReward(10*(waveNum / 2 + BASEVAL));
	this->setSpeed(waveNum / 2 + (2*BASEVAL));

	//slow = 1 -> not slowed // slowed = 2 -> slowed
	this->setSlowed(BASEVAL);

	this->setMaxHP(startHP);
	this->setDamageTime(0);
    this->setDPS(0);
    this->setSlowTime(0);
    this->setPathCount(0);






};


Boss::Boss():Creep(){}
