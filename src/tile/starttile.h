/*
 * starttile.h
 *
 *  Created on: Oct 14, 2014
 *      Author: geoffrey
 */

#ifndef STARTTILE_H_
#define STARTTILE_H_

#include "tile.h"

class StartTile: public Tile{
public:
  StartTile();
  StartTile(int row,int column);
  virtual ~StartTile();
};

#endif /* STARTTILE_H_ */
