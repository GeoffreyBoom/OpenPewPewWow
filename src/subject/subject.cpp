/*
 * subject.cpp
 *
 *  Created on: Oct 29, 2014
 *      Author: geoffrey
 */

#include "subject.h"
#include "stdio.h"


Subject::Subject() {
  observers = new list<Observer*>;
}

Subject::~Subject() {
  while(observers->size() > 0){
    delete observers->front();
    observers->erase(observers->begin());
  }
  delete observers;
}

void Subject::attach(Observer* o) {
  observers->push_back(o);
}

void Subject::detach(Observer* o) {
  observers->remove(o);
}

void Subject::notify() {
  list<Observer *>::iterator i = observers->begin();
  for(;i != observers->end(); ++i){
    (*i)->update();
  }
}
