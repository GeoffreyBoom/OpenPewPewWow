/*
 * CloseToTheEdge.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: samuel
 */

#include "CloseToTheEdge.h"

CloseToTheEdge::CloseToTheEdge() {
	// TODO Auto-generated constructor stub

}

CloseToTheEdge::~CloseToTheEdge() {
	// TODO Auto-generated destructor stub
}

Creep * CloseToTheEdge::execute(vector<Creep*>* creeps,int posX, int posY, int range){
	vector<Creep*>* targets = withinRange(creeps,posX,posY,range);
	if (targets->size() >0){
		Creep* target =(*targets)[0];
		for (int i = 0 ; i < targets->size();i++){
			if(target->getPathCount() < (*targets)[i]->getPathCount())
				target = (*targets)[i];
				}
	}

	else
		return NULL;
}

string CloseToTheEdge::getName(){return "Closest to the end";}

