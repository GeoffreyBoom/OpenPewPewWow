#include "basicTower.h"
//#include "stdafx.h"
#include <iostream>
#include <math.h>
#include "../player/Player.h"
#include <string>
using namespace std;
double critDistance(Creep * target, Creep* nearby);


//Constructor
BasicTower::BasicTower(string imagefile, double newRange, int newSpeed,
    int newDamage, int posX, int posY, int buying, int upgrade, string name):
    Item( posX,  posY,TILE_WIDTH,TILE_HEIGHT,imagefile),
    Subject(),
    range(newRange),
    speed(newSpeed),
    damage(newDamage),
    upgradePrice(upgrade),
    buyingPrice(buying),
	strategy(new TargetingPatern())
{
  splashRadius = 0;
  damageTime = 0;
  lastingDamage = 0;
  slowTime = 0;
  slowAmmount = 1;
  level = 1;
  refundValue = buyingPrice / 2;
  numberOfTargets = 1;
  this->name = name;
};
BasicTower::BasicTower(string towername, double newRange, int newSpeed, int newDamage, int posX, int posY, int buying, int upgrade)
:BasicTower(towername,newRange,newSpeed,newDamage,posX,posY,buying,upgrade,"Tower"){}

BasicTower::BasicTower(int posX, int posY) : BasicTower("images/tower.png", 110, 20, 1, posX, posY, 50, 40){}

BasicTower::BasicTower( BasicTower& tower )
:BasicTower(tower.getName(), tower.getRange(), tower.getSpeed(),
    tower.getDamage(),tower.getPosX(),tower.getPosY(),
    tower.getBuyingPrice(),tower.getUpgradePrice())
{
	this->setStrategy(tower.strategy);
}

BasicTower::BasicTower() :BasicTower(0, 0){}

void BasicTower::tick(vector<Creep*>* creeps) {
  if(Player::getPlayer()->getTick()%speed == 0){
    //find target
    Creep* target = this->findTarget(creeps);

    //shoot creep
    if (target != NULL){

       this->attack(target);

       if (this->getSlowAmmount() != 0){
         target->indSlow(this->getSlowTime(),this->getSlowAmmount());
       }

       if (this->getLastingDamage() != 0){
         target->damageOverTime(this->getLastingDamage(), this->getDamageTime());
       }

       if (this->getSplashRadius() != 0){
          vector<Creep*>* splashCreeps = findSplashTargets(creeps, target);
          int numSplash = splashCreeps->size();

          if (numSplash > 0){
             for(int i = 0; i<numSplash; i++){
                this->attack((*splashCreeps)[i]);
             }

          }




       }



    }
  }
}

vector<Creep*>* BasicTower::findSplashTargets(vector<Creep*>* gCreeps, Creep* target){
    int numCreeps = gCreeps->size();
    int targetX = target->getCenterX();
    int targetY = target->getCenterY();
    vector<Creep*>* targetList = new vector<Creep*>;

    double minDist = this->getSplashRadius();

    int creepX = 0;
    int creepY = 0;

    double pyth = 0;

    for (int i = 0; i<numCreeps; i++){
        creepX = (*gCreeps)[i]->getCenterX();
        creepY = (*gCreeps)[i]->getCenterY();

        //pythagoras distance formula
        pyth  = ( pow((pow((creepX - targetX),2.0) + pow((creepY - targetY),2.0)),0.5));

        if (pyth < minDist){

             targetList->push_back((*gCreeps)[i]);

        }


    }

    return targetList;

}

// Attack the crit deal damage, display result
void BasicTower::attack(Creep* target){
	if (!target->attackCreep(getDamage()))
	{
		target->report();
	}

}
//This returns the selected targets, Can be an array of NULL pointers! //Check if there is nearby target if none, NULL pointer. Can<t target same crit twice.
Creep** BasicTower::selectTarget(Creep** targets,int totalTargets)
{
	Creep** myTargets = new Creep*[getNumberOfTargets()];
	int index = 0;
	for (int i = 0; i < getNumberOfTargets(); i++){
		myTargets[i] = NULL;
		for (int j = index; j < totalTargets; j++)
		{
			if (targets[j] == NULL)
				continue;
			if (distance(targets[j]) < getRange())
			{
				myTargets[i] = targets[j];
				index = j + 1;
				break;
			}
		}
	}
	return myTargets;
}

//creep targetting (eric's temp one)
Creep* BasicTower::findTarget2(vector<Creep*>* gCreeps){
    int numCreeps = gCreeps->size();
    int towerX = this->getCenterX();
    int towerY = this->getCenterY();
    Creep* target = NULL;

    double minDist = 9999;

    int creepX = 0;
    int creepY = 0;

    double pyth = 0;

    for (int i = 0; i<numCreeps; i++){
        creepX = (*gCreeps)[i]->getPosX();
        creepY = (*gCreeps)[i]->getPosY();

        //pythagoras distance formula
        pyth  = ( pow((pow((creepX - towerX),2.0) + pow((creepY - towerY),2.0)),0.5));

        if (pyth < minDist){
           if (pyth <= getRange()){
             if(debugPrint){
               printf("tcenterx:%i\n",getCenterX());
               printf("tcentery:%i\n",getCenterY());
               printf("cposx:%i\n",creepX);
               printf("cposy:%i\n",creepY);
               printf("pyth:%f\n",pyth);
               printf("range:%f\n", getRange());
             }
             minDist = pyth;
             target = (*gCreeps)[i];
           }
        }


    }

    return target;
}

Creep* BasicTower::findTarget(vector<Creep*>* gCreeps){
   Creep* target = getStrategy()->execute(gCreeps, this->getCenterX(), this->getCenterY(), this->getRange());
   return target;
}

//Deal spash dmg to targets.
void BasicTower::splashTargets(Creep* targets, Creep** arrCrits, int totalCrits)
{
  if(getSplashRadius() > 1){
    if (targets == NULL)
      return;

        //splash all other nearby creeps
        for (int j = 0; j < totalCrits; j++)
        {
          if (arrCrits[j] == NULL)
            continue;
          if (!arrCrits[j]->attackCreep(0))
          {
            cout << "\nDistance between creep : " << critDistance(targets, arrCrits[j]) << "\n";
            if (critDistance(targets, arrCrits[j]) > 0 && critDistance(targets, arrCrits[j]) < getSplashRadius())
            {
              if (arrCrits[j]->attackCreep(2))
              {

                cout << " Splash\n";
                arrCrits[j]->report();
                if (arrCrits[j]->attackCreep(0))
                  delete arrCrits[j];
                  arrCrits[j] = NULL;
              }
              else
              {
                arrCrits[j] = NULL;
              }
            }
          }
          else
            arrCrits[j] = NULL;

        }
      }
}



//Method action that find, select, then attack crits. Also deal splash if any.
void BasicTower::action(Creep** listOfCrits, int length){
	Creep** targets;
	targets = selectTarget(listOfCrits, length);
	for (int i = 0; i < getNumberOfTargets(); i++)
	{
		if (targets[i] == NULL)
			continue;
		else
		{
			attack(targets[i]);

			splashTargets(targets[i], listOfCrits, length);
		}
	}
}



void BasicTower::displayInfo() //Display Basic information dfor the driver.
{
  cout << "Name: " << getName()  << endl;
  cout << "\tRange: " << getRange() <<endl;
  cout << "\tLevel: " << getLevel() <<endl;
  cout << "\tSpeed: " << getSpeed() << endl;
  cout << "\tDamage: " << getDamage() << endl;
  cout << "\tLasting Damage:" << getLastingDamage() << endl;
  cout << "\tLasting Damage Time: " <<  getDamageTime() << endl;
  cout << "\tSlow Amount: " << getSlowAmmount() << endl;
  cout << "\tSlow Time: " <<  getSlowTime() << endl;
  cout << "\tRefund Value: " <<  getRefundValue() << endl;
  cout << "\tUpgrade Price: " <<  getUpgradePrice() << endl;
  cout << "\tSplash Radius: " <<  getSplashRadius() << endl;
  cout << "\tStrategy: " << getStrategy()->getName() << endl;
}

BasicTower::~BasicTower()
{
}
//Distance between crits, if one of the crits are NULL, it returns -1.
double critDistance(Creep * target, Creep* nearby){
	if (target == NULL || nearby == NULL)
		return -1.0;
	else
		return sqrt((target->getPosX() - nearby->getPosX())*(target->getPosX() - nearby->getPosX()) + (target->getPosY() - nearby->getPosY())*(target->getPosY() - nearby->getPosY()));
}

int BasicTower::sell(){
	int buffer = this->getRefundValue();
	Player::getPlayer()->deposit(buffer);
	delete this;
	return buffer;
}

double BasicTower::getRange()         		{ return range; }
int BasicTower::getLevel()            		{ return level; }
int BasicTower::getSpeed()            		{ return speed; }
int BasicTower::getDamage()           		{ return damage; }
int BasicTower::getLastingDamage()    		{ return lastingDamage; }
int BasicTower::getSlowAmmount()      		{ return slowAmmount; }
int BasicTower::getSlowTime()         		{ return slowTime; }
int BasicTower::getDamageTime()       		{ return damageTime; }
int BasicTower::getBuyingPrice()      		{ return buyingPrice; }
int BasicTower::getRefundValue()      		{ return refundValue; }
int BasicTower::getNumberOfTargets()  		{ return numberOfTargets; }
double BasicTower::getSplashRadius()  		{ return splashRadius; }
int BasicTower::getUpgradePrice()     		{ return upgradePrice;}
TargetingPatern* BasicTower::getStrategy()	{return strategy ;}
string BasicTower::getName() {
  return name;
}

void BasicTower::setStrategy(TargetingPatern * newStrategy){
  delete strategy;
	this->strategy = newStrategy;
}


