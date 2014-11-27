#ifndef Creep_H
#define Creep_H
#include "../item/item.h"
#include "../subject/subject.h"
#include "../path/path.h"
#include <stdio.h>
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>


using namespace std;

//renaming "pointer to an int" as pint
typedef int * pint;
//renaming "pointer to a char" as pchar
typedef char * pchar;
//rename "pointer to a Creep" as pMap
//typedef Creep * pCreep;

class Creep :public Item, public Subject{
public:


    const int BASEVAL = 1;

	string pList;

	Creep();
	Creep(int, int, int, int, int, string, Path*);
	Creep(int, int, int, int, int, int, string, Path*);
	virtual ~Creep();

	//Setters
	void setWaveNum(int);
	void setHitPoints(int);
	void setDefense(int);
	void setReward(int);
	void setSpeed(int);
	void setSlowed(int);
	void setPath(Path*);
	void setTarget();
	void setPathCount(int);

	void setDamageTime(int);
	void setDPS(int);
	void setMaxHP(int);
	void setSlowTime(int);

	inline void setPenalty(int p){ this->penalty = p; };


	//Getters
	int getWaveNum();
	int getHitPoints();
	int getDefense();
	int getReward();
	int getSpeed();
	int getSlowed();
	Path* getPath();
	int getTargetX();
	int getTargetY();
	int getMaxHP();
	int getPathCount();
	string getWoundedImage();
	inline int getPenalty() { return this->penalty;}

	//updates creep parameters
	void tick();

	bool reachedTarget();

	//Destroy Creep
	void destroyCreep();

	//isAttacked handler
	//Takes in attack power and current value savings
	bool attackCreep(int);

	bool isKilled();

	//isSlowed handler
	bool isSlowed();

	//induce slow modifier
	void indSlow(int, int);

	bool isWounded();
	bool setWounded(bool wounded);
	bool setWoundedImage(string woundedImage);


	//Creep Report - Returns a pointer to a vector with creep information
	string report();

	//Damage over time
	void damageOverTime(int, int);


private:
	const bool debugPrint = false;
    int waveNum;
	int hitPoints;
	int defense;
	int reward;
	int speed;
	int slowed;
	int penalty;
	int targetX;
	int targetY;
	int slowTime;
	int damageTime;
	int dps;
	int maxHP;
	int pathCount;
	bool wounded = false;
	string woundedImage;

	Path* path;
};
#endif
