#pragma once
using namespace std;
#include <string>
#include "../item/item.h"
#include "../subject/subject.h"
#include "../creep/creep.h"
#include "../display/display.h"
#include "TargetingPatern.h"
#include "Strongest.h"
#include "Closest.h"
#include "weakest.h"
class BasicTower: public Subject, public Item
{
public:
	//Constructor
  BasicTower();
  BasicTower(int, int);
  BasicTower( BasicTower &tower );
  BasicTower(string imagefile,double newRange, int newSpeed, int newDamage, int posX, int posY, int buying, int upgrade);
  BasicTower(string imagefile,double newRange, int newSpeed, int newDamage, int posX, int posY, int buying, int upgrade, string name);

	//Destructor
  virtual ~BasicTower();
	//Accessor

	virtual double getRange();
	virtual int getLevel();
	virtual int getSpeed();
	virtual int getDamage();
    virtual int getLastingDamage();
    virtual int getSlowAmmount();
    virtual int getSlowTime();
    virtual int getDamageTime();
	virtual int getBuyingPrice();
	virtual int getRefundValue();
    virtual int getUpgradePrice();
	virtual int getNumberOfTargets();
	virtual TargetingPatern* getStrategy();
	virtual void setStrategy(TargetingPatern *);
    virtual double getSplashRadius();
	virtual string getName();



  void tick(vector<Creep*>* creeps);

	//Mutator Not
	inline void setRefundValue(int value)
	{
		if (value > 0)
			refundValue = value;
		else
			exit(0);
	}
	inline void setDamage(int value)
	{
		if (value > 0)
			damage = value;
		else
			exit(0);
	}
	virtual void splashTargets(Creep*, Creep **, int totalCrits);
	virtual int sell();
	//Find the crits to attact
	Creep** selectTarget(Creep** targets,int totalTargets);
	virtual void attack(Creep*); // Attack a crit
	virtual void action(Creep**, int length); // Find, then attack crits depend on number of targets
	virtual void displayInfo();
    Creep* findTarget(vector<Creep*>*);
    Creep* findTarget2(vector<Creep*>*);

    vector<Creep*>* findSplashTargets(vector<Creep*>*,Creep*);

private:

    bool debugPrint = false;
	double splashRadius;// Range of the splash
	int level; // Towers level
	//Money related stuff. The tower does not verify if the player has the money
	int buyingPrice;
	int refundValue;
	int upgradePrice;
	// Damage, projectile info.
	int damage;
	int lastingDamage;
	int slowAmmount;
	int slowTime;
	int damageTime;
	int numberOfTargets;// Can attack more than one at a time.
	int speed; // second between attacks
	double range;
	TargetingPatern* strategy;



	//Tower name i.e. The kind of tower.
	string name;

};

