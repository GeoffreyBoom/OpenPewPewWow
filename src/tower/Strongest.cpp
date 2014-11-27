/*
 * Strongest.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: samuel
 */

#include "Strongest.h"

Strongest::Strongest() {
	// TODO Auto-generated constructor stub

}

Strongest::~Strongest() {
	// TODO Auto-generated destructor stub
}

Creep* Strongest::execute(vector<Creep*>* candidates , int posX,int posY,int range){
	vector<Creep*>* targets = withinRange(candidates,posX,posY,range); // Get targets within TowerRange
		Creep * target = NULL;

		if(targets->size() > 0){
			target = (*targets)[0];
			for (int i = 0 ; i < targets->size();i++){
				if((*targets)[i]->getHitPoints() > target->getHitPoints())// Find weakest
					target = (*targets)[i];
			}

		}
		return target;
}

string Strongest::getName(){return "Strongest";}
