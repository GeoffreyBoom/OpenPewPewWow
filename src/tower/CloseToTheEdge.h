/*
 * CloseToTheEdge.h

 *
 *  Created on: Nov 26, 2014
 *      Author: samuel
 */


#ifndef SRC_TOWER_CLOSETOTHEEDGE_H_
#define SRC_TOWER_CLOSETOTHEEDGE_H_
#include "../player/Player.h"
#include "TargetingPatern.h"

class CloseToTheEdge: public TargetingPatern {
public:
	CloseToTheEdge();
	virtual ~CloseToTheEdge();
	virtual string getName();
	virtual Creep* execute(vector<Creep*>* ,int , int, int);


};

#endif /* SRC_TOWER_CLOSETOTHEEDGE_H_ */
