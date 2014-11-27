/*
 * TowerTile.h
 *
 *  Created on: Oct 14, 2014
 *      Author: geoffrey
 */

#ifndef TOWERTILE_H_
#define TOWERTILE_H_

#include "tile.h"

class TowerTile: public Tile{
public:
  TowerTile();
  TowerTile(int row,int column);
  virtual ~TowerTile();
};

#endif /* TOWERTILE_H_ */
