/*
 * CreepTile.h
 *
 *  Created on: Oct 14, 2014
 *      Author: geoffrey
 */

#ifndef CREEPTILE_H_
#define CREEPTILE_H_
#include "tile.h"

class CreepTile: public Tile{
public:
  CreepTile();
  CreepTile(int x, int y);
  virtual ~CreepTile();
};

#endif /* CREEPTILE_H_ */
