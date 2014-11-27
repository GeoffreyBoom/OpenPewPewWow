/*
 * subject.h
 *
 *  Created on: Oct 29, 2014
 *      Author: geoffrey
 */

#ifndef SUBJECT_H_
#define SUBJECT_H_
#include <list>

class Subject;

#include "../observer/observer.h"

using namespace std;

class Subject {
public:
  virtual void attach(Observer*);
  virtual void detach(Observer*);
  virtual void notify();
  Subject();
  virtual ~Subject();
private:
  list<Observer*>* observers;
};


#endif /* SUBJECT_H_ */

