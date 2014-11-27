/*
 * Strongest.h
 *
 *  Created on: Nov 25, 2014
 *      Author: samuel
 */

#ifndef SRC_TOWER_STRONGEST_H_
#define SRC_TOWER_STRONGEST_H_

#include "TargetingPatern.h"

class Strongest: public TargetingPatern {
public:
	Strongest();
	virtual ~Strongest();
	Creep* execute(vector<Creep*>*, int,int,int );
	string getName();
};

#endif /* SRC_TOWER_STRONGEST_H_ */
