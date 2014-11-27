/*
 * weakest.h
 *
 *  Created on: Nov 25, 2014
 *      Author: samuel
 */

#ifndef SRC_TOWER_WEAKEST_H_
#define SRC_TOWER_WEAKEST_H_

#include "TargetingPatern.h"

class Weakest: public TargetingPatern {
public:
	Weakest();
	virtual ~Weakest();
	Creep* execute(vector<Creep*>*, int, int, int);
	string getName();
};

#endif /* SRC_TOWER_WEAKEST_H_ */
