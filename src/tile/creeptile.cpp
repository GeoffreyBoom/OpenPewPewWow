/*
 * CreepTile.cpp
 *
 *  Created on: Oct 14, 2014
 *      Author: geoffrey
 */
#include "creeptile.h"

CreepTile::CreepTile()
  : CreepTile(0,0){}

CreepTile::CreepTile(int row,int column)
  : Tile(row,column,"images/creeptile.png",'c'){}

CreepTile::~CreepTile() {}

