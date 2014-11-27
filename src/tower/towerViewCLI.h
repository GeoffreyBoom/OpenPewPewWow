#pragma once
#include "../observer/observer.h" // Concrete observer in the observer pattern
#include "basicTower.h"
#include "../display/display.h"
class TowerViewCLI :
	public Observer
{
public:
	TowerViewCLI();
	~TowerViewCLI();
	TowerViewCLI(BasicTower* t); // The tower attach to the view
	TowerViewCLI(BasicTower* t, Display* display);
	void update();
private:
	bool initialized = 0;
	sf::Sprite* sprite;
	Display* display;
	BasicTower *_subjectTower;// Our observer is connected to the BasicTower model.
};

