/*
 * weakest.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: samuel
 */

#include "weakest.h"

Weakest::Weakest() {
	// TODO Auto-generated constructor stub

}

Weakest::~Weakest() {
	// TODO Auto-generated destructor stub
}


Creep *  Weakest::execute(vector<Creep*>* candidates, int posX, int posY, int range)
{
	vector<Creep*>* targets = withinRange(candidates,posX,posY,range); // Get targets within TowerRange
	Creep * target = NULL;

	if(targets->size() > 0){
		target = (*targets)[0];
		for (int i = 0 ; i < targets->size();i++){
			if((*targets)[i]->getHitPoints() < target->getHitPoints())// Find weakest
				target = (*targets)[i];
		}

	}
	return target;
}
string Weakest::getName(){
	return "weakest";
}
