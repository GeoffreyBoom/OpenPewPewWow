/*
 * observer.h
 *
 *  Created on: Oct 29, 2014
 *      Author: geoffrey
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

class Observer {
public:
  virtual void update() = 0;
  Observer();
  virtual ~Observer();
};

#endif /* OBSERVER_H_ */
