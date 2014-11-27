/*
 * Closest.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: samuel
 */

#include "Closest.h"

Closest::Closest() {
	// TODO Auto-generated constructor stub

}

Closest::~Closest() {
	// TODO Auto-generated destructor stub
}

Creep* Closest::execute(vector<Creep*>* candidates,int posX, int posY, int range){
	vector<Creep*>* targets = withinRange(candidates,posX,posY,range); // Get targets within TowerRange
	Creep * target = NULL;
	if(targets->size() > 0){
		target = (*targets)[0];
		for (int i = 0 ; i < targets->size();i++){
			if(distance(posX,posY,(*targets)[i]) < distance(posX,posY,target) )// Find weakest
				target = (*targets)[i];
		}
	}
	return target;
}
string Closest::getName(){return "Closest";}
