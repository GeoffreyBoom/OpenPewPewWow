/*
 * TargetingPatern.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: samuel
 */

#include "TargetingPatern.h"
//double distance(int x, int y, Creep* creep);
TargetingPatern::TargetingPatern() {
	// TODO Auto-generated constructor stub

}

TargetingPatern::~TargetingPatern() {
	// TODO Auto-generated destructor stub
}
Creep * TargetingPatern::execute(vector<Creep*>* creeps,int posX, int posY, int range){
	vector<Creep*>* targets = withinRange(creeps,posX,posY,range);
	if (targets->size() >0)
		return (*targets)[0];
	else
		return NULL;
}

vector<Creep*>* TargetingPatern::withinRange(vector<Creep*>* creeps,int posX, int posY, int range){
	vector<Creep*>* targets= new vector<Creep*>;
	for	(int i = 0 ; i< creeps->size();i++){
		if(distance(posX,posY,((*creeps)[i])) <= range)
			targets->push_back((*creeps)[i]);

	}
	return targets;
}

double TargetingPatern::distance(int x, int y , Creep* creep){
	return pow(pow(x-creep->getPosX(),2) + pow(y-creep->getPosY(),2),0.5);
}
string TargetingPatern::getName(){return "default";}
