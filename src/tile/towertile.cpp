/*
 * TowerTile.cpp
 *
 *  Created on: Oct 14, 2014
 *      Author: geoffrey
 */
#include "towertile.h"

TowerTile::TowerTile()
  : TowerTile(0,0){}

TowerTile::TowerTile(int row, int column)
  : Tile(row,column,"images/towertile.png",'t'){}

TowerTile::~TowerTile() {

}

