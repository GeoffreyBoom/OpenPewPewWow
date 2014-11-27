#include "towerViewCLI.h"
//#include "stdafx.h"

// Concrete Observer.
TowerViewCLI::TowerViewCLI()
{
	_subjectTower = NULL;
}

TowerViewCLI::TowerViewCLI(BasicTower* t) // Attach detach tower to the view with the constructor/ destructor
{
	_subjectTower = t;
	_subjectTower->Subject::attach(this);
	display = NULL;
	this->update();

}

TowerViewCLI::TowerViewCLI(BasicTower* t, Display* display) // Attach detach tower to the view with the constructor/ destructor
{
  _subjectTower = t;
  _subjectTower->Subject::attach(this);
  this->display = display;
  this->update();

}

TowerViewCLI::~TowerViewCLI()
{
  display->removeSprite(sprite,1);
	//_subjectTower->Subject::detach(this);
}

void TowerViewCLI::update() //Use the builtin displayInfo on update/ It will display all the changes.
{
  if(display == NULL){
    _subjectTower->displayInfo();
  }
  else{
    sprite = display->createSprite(this->_subjectTower->getImage(), _subjectTower->getPosX(), _subjectTower->getPosY());
    if(initialized){
      display->removeSprite(sprite,1);
    }
    display->addSprite(sprite,1);
  }
}
