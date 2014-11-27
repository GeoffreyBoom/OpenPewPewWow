/*
* CreepObserver.h
*/
#ifndef Creep_OBSERVER_H_
#define Creep_OBSERVER_H_

#include "observer.h"
#include "../creep/creep.h"
#include "../subject/subject.h"
#include <SFML/Graphics.hpp>
#include "../display/display.h"

using namespace std;

class CreepObserver : public Observer {

public:
	CreepObserver();
	CreepObserver(Creep*, Display*);
	virtual ~CreepObserver();
	void update();
	void displayAll();
	void displayHealth();
	void displayPosition();

private:
	int hurtBuffer = 0;
	int hurtDisplayTime = 10;
  bool initialized = false;
	Creep* subject;
	sf::Sprite* creepSprite;
	sf::CircleShape* circle;
	Display* display;
};
#endif
