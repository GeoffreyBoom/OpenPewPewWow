/*
 * Closest.h
 *
 *  Created on: Nov 25, 2014
 *      Author: samuel
 */
#include "TargetingPatern.h"
#ifndef SRC_TOWER_CLOSEST_H_
#define SRC_TOWER_CLOSEST_H_

class Closest: public TargetingPatern {
public:
	Closest();
	virtual ~Closest();
	Creep* execute(vector<Creep*>*,int,int,int);
	string getName();
};

#endif /* SRC_TOWER_CLOSEST_H_ */
