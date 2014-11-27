#include <stdio.h>
#include "creepobserver.h"

using namespace std;

//Creep Observer -- Used to print information relating to the subject creep

CreepObserver::CreepObserver() {
}

CreepObserver::CreepObserver(Creep* subject, Display* display) {
	this->subject = subject;
	subject->attach(this);
	this->display = display;
	this->creepSprite = NULL;
	this->circle = new sf::CircleShape(subject->getHitPoints());

}

CreepObserver::~CreepObserver() {
  display->removeSprite(creepSprite,1);
  display->removeDrawable(circle);
}

void CreepObserver::update() {
	displayAll();
}

void CreepObserver::displayAll() {
	//observer has to store old sprite, because it is removed
	//if initialized remove old creepSprite
	if (initialized == true){
		//remove old
		//remove Sprite takes old sprite pointer, as well as layer -> 1
		display->removeSprite(creepSprite, 1);
		display->removeDrawable(circle);
	}
	else{
		initialized = true;
	}

  if(hurtBuffer > 0){
    hurtBuffer--;
  }

	if(subject->isWounded()){
	  hurtBuffer = hurtDisplayTime;
	  subject->setWounded(false);
	}


	//takes in filename and posx, posy
	if(hurtBuffer == 0){
	  creepSprite = display->createSprite(subject->getImage(), subject->getPosX()-25, subject->getPosY()-25);
	}
	else{
	  creepSprite = display->createSprite(subject->getWoundedImage(), subject->getPosX()-25, subject->getPosY()-25);
	}
	display->addSprite(creepSprite, 1);
	circle->setRadius(((double)subject->getHitPoints()/subject->getMaxHP()) * 5);
  circle->setPosition(subject->getPosX()-(circle->getRadius()),subject->getPosY()-(circle->getRadius()));
	display->addDrawable(circle);

	//Line Spacing
	//cout << this->subject->pList << endl;

}



void CreepObserver::displayHealth(){


	if (this->subject->getHitPoints() == 0){
		cout << "\nCreep Dead" << endl;
	}else{
		cout << "\nCurrent health: " << this->subject->getHitPoints();
	}

}

void CreepObserver::displayPosition(){

	//cout << "\nCreep Position: (" + to_string(this->subject->getPosX()) + "," + to_string(this->subject->getPosY()) + ")" << endl;
	printf("\nCreep Position: (%i,%i,)",this->subject->getPosX(),this->subject->getPosY());
}
