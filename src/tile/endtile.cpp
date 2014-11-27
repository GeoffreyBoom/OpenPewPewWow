/*
 * endtile.cpp
 *
 *  Created on: Oct 14, 2014
 *      Author: geoffrey
 */
#include "endtile.h"

EndTile::EndTile()
  : EndTile(0,0){}

EndTile::EndTile(int row,int column)
  : Tile(row,column,"images/endtile.png",'e'){}

EndTile::~EndTile() {}

