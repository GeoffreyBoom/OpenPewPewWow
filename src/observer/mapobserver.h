/*
 * mapobserver.h
 *
 *  Created on: Oct 29, 2014
 *      Author: geoffrey
 */

#ifndef MAPOBSERVER_H_
#define MAPOBSERVER_H_
#include "observer.h"
#include "../map/map.h"
#include "../display/display.h"
#include <map>

using namespace std;

class MapObserver: public Observer {
public:
    bool debugPrint = false;
	bool gui = false;
    MapObserver();
    MapObserver(Map*);
	MapObserver(Map*, Display*);
	Display* dis;
  virtual ~MapObserver();
  virtual void update();
  virtual void display();
private:
  vector<vector<sf::Sprite*> > sprites;
  bool initialized = 0;
  Map* subject;
};
#endif
