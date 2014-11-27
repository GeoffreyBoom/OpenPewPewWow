/*
 * notfrozentargeting.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: geoffrey
 */

#include "notfrozentargeting.h"


NotFrozenTargeting::NotFrozenTargeting() {
  // TODO Auto-generated constructor stub

}

NotFrozenTargeting::~NotFrozenTargeting() {
  // TODO Auto-generated destructor stub
}
Creep* NotFrozenTargeting::execute(vector<Creep*>* candidates , int posX,int posY,int range){
  vector<Creep*>* targets = withinRange(candidates,posX,posY,range); // Get targets within TowerRange
  Creep * target = NULL;
  if(targets->size() > 0){
    target = (*targets)[0];
    for (int i = 0 ; i < targets->size();i++){
      if(!(*targets)[i]->isSlowed())// Find weakest
        target = (*targets)[i];
    }
    if(target == NULL){
      target = (*targets)[0];
    }
  }

  return target;

}

string NotFrozenTargeting::getName() {
  return "Not Frozen";
}
