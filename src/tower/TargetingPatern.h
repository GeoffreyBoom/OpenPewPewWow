/*
 * TargetingPatern.h
 *
 *  Created on: Nov 25, 2014
 *      Author: samuel
 */

#include "../creep/creep.h"
#include <vector>
#ifndef SRC_TOWER_TARGETINGPATERN_H_
#define SRC_TOWER_TARGETINGPATERN_H_

class TargetingPatern {
public:
	TargetingPatern();
	virtual ~TargetingPatern();
	virtual Creep* execute(vector<Creep*>* ,int posX,int posY, int);
	virtual vector<Creep*>* withinRange(vector<Creep*>*,int , int ,int);
	virtual double distance(int x, int y, Creep* creep);
	virtual string getName();

};

#endif /* SRC_TOWER_TARGETINGPATERN_H_ */
