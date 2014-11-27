/*
 * endtile.h
 *
 *  Created on: Oct 14, 2014
 *      Author: geoffrey
 */


#ifndef ENDTILE_H_
#define ENDTILE_H_
#include "../player/Player.h"
#include "../creep/creep.h"
#include "tile.h"

class EndTile: public Tile{
public:
  EndTile();
  inline bool damagePlayer(Creep* cr){
	  return Player::getPlayer()->damagePlayer(cr);
  }
  EndTile(int row,int column);
  virtual ~EndTile();
};

#endif /* ENDTILE_H_ */
