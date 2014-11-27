/*
 * starttile.cpp
 *
 *  Created on: Oct 14, 2014
 *      Author: geoffrey
 */
#include "starttile.h"

StartTile::StartTile()
  : StartTile(0,0){}

StartTile::StartTile(int row,int column)
  : Tile(row,column,"images/starttile.png",'s'){}

StartTile::~StartTile() {

}

