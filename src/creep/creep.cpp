#include "creep.h"
#include "../player/Player.h"

using namespace std;


//default Creep constructor
Creep::Creep() :Item(), Subject(){

  this->setPosX(0);
	this->setPosY(0);
	this->setWidth(50);
	this->setHeight(50);
	this->setImage("");
	this->setPenalty(BASEVAL);
	this->setWaveNum(BASEVAL);
	this->setDefense(BASEVAL);
	this->pList = "";
    dps = 0;
    damageTime = 0;
    slowTime = 0;
    pathCount = 0;

	//initializing base Creep stats
	this->setHitPoints((this->getWaveNum())*5);
	this->setReward((this->getWaveNum()) / (2 + this->BASEVAL) + BASEVAL);
	this->setSpeed((this->getWaveNum()) / (2 + this->BASEVAL) + BASEVAL);

	//slow = 1 -> not slowed // slowed = 2 -> slowed
	this->setSlowed(this->BASEVAL);


    //MAY BREAK CODE
    this->setPath(new Path());
    this->maxHP = 99;


};


//Creep constructor implements the Item constructor
Creep::Creep(int waveNum, int posX, int posY, int width, int height, string image, Path* path):Item(posX, posY, width, height, image)
{
	//Passing values to Item constructor
	this->setPosX(posX);
	this->setPosY(posY);
	this->setWidth(width);
	this->setHeight(height);
	this->setImage(image);
	this->setPenalty(BASEVAL);
	this->setWaveNum(waveNum);
	this->setDefense(BASEVAL);
	this->pList = "";
    dps = 0;
    damageTime = 0;
    slowTime = 0;
    pathCount = 0;

	//initializing base Creep stats
	this->setHitPoints((this->getWaveNum())*5);
	this->setReward((this->getWaveNum()) / (2 + this->BASEVAL)+ BASEVAL);
	this->setSpeed((this->getWaveNum()) / (2 + this->BASEVAL)+ BASEVAL);


	//slow = 1 -> not slowed // slowed = 2 -> slowed
	this->setSlowed(this->BASEVAL);

    this->setPath(path);

    this->maxHP = 99;

};

//Creep initializer that accounts for difficulty changes
Creep::Creep(int waveNum, int startHP, int posX, int posY, int width, int height, string image, Path* path):Item(posX, posY, width, height, image)
{
	//Passing values to Item constructor
	this->setPosX(posX);
	this->setPosY(posY);
	this->setWidth(width);
	this->setHeight(height);
	this->setImage(image);
	this->setPenalty(BASEVAL);
	this->setWaveNum(waveNum);
	this->setDefense(BASEVAL);
	this->pList = "";
    dps = 0;
    damageTime = 0;
    slowTime = 0;
    pathCount = 0;


	//initializing base Creep stats
	this->setHitPoints(startHP);
	this->setReward((this->getWaveNum()) / (2 + this->BASEVAL)+ BASEVAL);
	this->setSpeed((this->getWaveNum()) / (2 + this->BASEVAL)+ BASEVAL);

    this->maxHP = startHP;

	//slow = 1 -> not slowed // slowed = 2 -> slowed
	this->setSlowed(this->BASEVAL);

    this->setPath(path);


};

bool Creep::isKilled(){
    return (hitPoints == 0);
}


//Induce damage
bool Creep::attackCreep(int atkPwr){
  if(debugPrint) printf("creep attacked: beforehealth:%i\n", hitPoints);
	//Check if this hit will destroy the Creep
	if (hitPoints > (atkPwr / defense)){
		hitPoints -= atkPwr / defense;
		wounded = true;
		if (debugPrint) printf("creep attacked: nowhealth:%i\n", hitPoints);
		return false;

	}else{
		hitPoints = 0;
    if(debugPrint) printf("creep attacked: nowhealth:%i\n", hitPoints);
		return true;

	}

};


//Used to determine if Creep is slowed
bool Creep::isSlowed(){
	switch (slowed){

		case 1:
			return false;
			break;
		default :
			return true;
			break;


	}

};

//Induces slowness modifer
void Creep::indSlow(int time, int amount){
    slowTime = time;
	slowed = amount;
};


void Creep::tick(){

if (Player::getPlayer()->getTick()%slowed == 0){

  if(reachedTarget()){
    this->setPath(this->path->getNext());
    this->pathCount++;
  }

    if(debugPrint) printf("current: %i,%i\n",posX,posY);
    if(debugPrint) printf("target: %i,%i\n",targetX,targetY);
    if (this-> getPosX() < this->getTargetX()){
      this->setPosX(this->getPosX() + 1);
    }else if (this->getPosX() > this->getTargetX()){
      this->setPosX(this->getPosX() - 1);
    }

    if (this-> getPosY() < this->getTargetY()){
      this->setPosY(this->getPosY() + 1);

    }else if (this->getPosY() > this->getTargetY()){
      this->setPosY(this->getPosY() - 1);
    }
    this->notify();


 }

     if (slowTime > 0){
        slowTime--;
     }else{
        slowed = 1;
     }

     if (damageTime > 0){
        this->attackCreep(dps);
        damageTime--;
     }
}


void Creep::setPath(Path* path){
    this->path = path;
    this->setTarget();

}

//Set movement target
void Creep::setTarget(){
    this->targetX = this->path->getTargetX();
    this->targetY = this->path->getTargetY();

}



//Setters
void Creep::setHitPoints(int hitPoints){
	this->hitPoints = hitPoints;
};


void Creep::setDefense(int defense){
	this->defense = defense;
};


void Creep::setReward(int reward){
	this->reward = reward;
};

void Creep::setSpeed(int speed){
	this->speed = speed;
};


void Creep::setSlowed(int slowed){
	this->slowed = slowed;
};

void Creep::setWaveNum(int waveNum){
    this->waveNum = waveNum;
}

void Creep::setPathCount(int num){
    this->pathCount = num;
}


void Creep::setDamageTime(int dmg){
    this->damageTime = dmg;
}

void Creep::setDPS(int inDPS){
    this->dps = inDPS;
}

void Creep::setMaxHP(int mHP){
    this->maxHP = mHP;
}

void Creep::setSlowTime(int timez){
    this->slowTime = timez;
}

//end Setters


//Getters
int Creep::getPathCount(){
    return this->pathCount;
}


int Creep::getHitPoints(){
	return this->hitPoints;
}


int Creep::getDefense(){
	return this->defense;
}


int Creep::getReward(){
	return this->reward;
}

int Creep::getSpeed(){
	return this->speed;
}



int Creep::getSlowed(){
	return this->slowed;
}

int Creep::getWaveNum(){
    return this->waveNum;
}
int Creep::getMaxHP(){
  return maxHP;
}

//end getters





//Report

string Creep::report(){

	//Clear old list

	//Stores the header of the report at the top of the stack for later reference

	ostringstream os;
  	os << "\nMinion stats:" << "\n"
  	   << "Hitpoints = "    << this->getHitPoints() << "\n"
  	   << "Defense = "      << this->getDefense() << "\n"
  	   << "Reward = "	    << this->getReward() << "\n"
  	   << "Speed = "	    << this->getSpeed() << "\n"
  	   << "Creep slowed = " << this->isSlowed() << "\n"
  	   << "Current coords: "<< "(" << this->getPosX() << "," << this->getPosY() << ")" << "\n"
  	   << endl;


 	pList = os.str();


	return pList;


};

Creep::~Creep() {
}

int Creep::getTargetX() {
  return targetX;
}

int Creep::getTargetY() {
  return targetY;
}

Path* Creep::getPath() {
  return path;
}

bool Creep::reachedTarget() {
  return (this-> getPosX() == this->getTargetX())&&((this->getPosY() == this->getTargetY()));
}

void Creep::damageOverTime(int atk, int time){
    this->dps = atk;
    this->damageTime = time;
}


bool Creep::isWounded(){
    return this->wounded;
}
bool Creep::setWounded(bool wounded){
  this->wounded = wounded;
}



//Creep deleter -- DO NOT USE
void Creep::destroyCreep(){
	//Player::getPlayer()->deposit(this->getReward());
	delete this;
}
;

bool Creep::setWoundedImage(string woundedImage) {
  this->woundedImage = woundedImage;
}

string Creep::getWoundedImage() {
  return woundedImage;
}
