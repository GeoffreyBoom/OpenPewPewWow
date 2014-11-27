/*
 * WallTile.cpp
 *
 *  Created on: Oct 14, 2014
 *      Author: geoffrey
 */
#include "walltile.h"

WallTile::WallTile()
  :WallTile(0,0){}

WallTile::WallTile(int row, int column)
  : Tile(row,column,"images/walltile.png",'w'){}

WallTile::~WallTile() {}

