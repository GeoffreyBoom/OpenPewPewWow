/*
 * notfrozentargeting.h
 *
 *  Created on: Nov 26, 2014
 *      Author: geoffrey
 */

#ifndef NOTFROZENTARGETING_H_
#define NOTFROZENTARGETING_H_

#include "TargetingPatern.h"


class NotFrozenTargeting: public TargetingPatern {
public:
  NotFrozenTargeting();
  virtual ~NotFrozenTargeting();
  Creep* execute(vector<Creep*>*, int,int,int );
  string getName();
};


#endif /* NOTFROZENTARGETING_H_ */
