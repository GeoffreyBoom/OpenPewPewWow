/*
 * WallTile.h
 *
 *  Created on: Oct 14, 2014
 *      Author: geoffrey
 */


#ifndef WALLTILE_H_
#define WALLTILE_H_

#include "tile.h"

class WallTile: public Tile {
public:
  WallTile();
  WallTile(int row, int column);

  virtual ~WallTile();
};

#endif /* WALLTILE_H_ */
