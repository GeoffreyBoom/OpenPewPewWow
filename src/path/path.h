
/*
 * path.h
 *
 *  Created on: Nov 13, 2014
 *      Author: geoffrey
 */

#ifndef PATH_H_
#define PATH_H_
#include "../point/point.h"
#include <string>
#include <vector>
#include <cstdio>
#include "../display/sizeconstants.h"

using namespace std;

#ifndef NULL
#define NULL   ((void *) 0)
#endif

class Path {
public:
  Path();
  Path(Path* next);
  Path(Point* point);
  Path(Path* next, Point* point);
  Path(vector<Point*>);

  Path* getNext();
  bool hasNext();
  int getTargetX();
  int getTargetY();
  virtual ~Path();
  void print();
private:
  static const bool debugPrint = 0;
  void setNext(Path* next);
  void setTarget(Point* point);

  Path* next;
  int targetX;
  int targetY;
};


#endif /* PATH_H_ */

