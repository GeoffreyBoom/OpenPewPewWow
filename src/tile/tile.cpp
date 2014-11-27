#include "tile.h"
#include "creeptile.h"
#include "walltile.h"
#include "towertile.h"
#include "starttile.h"
#include "endtile.h"

string creepimage = "images/creeptile.png";
string wallimage  = "images/walltile.png";
string towerimage = "images/towertile.png";
string startimage = "images/starttile.png";
string endimage   = "images/endtile.png";
const int numTypes = 5;
char types[numTypes] = {'c','w','t','s','e'};

Tile::Tile()
  : Tile(0, 0){};

Tile::Tile(int row, int column)
  : Tile(row,column,creepimage){};

Tile::Tile(int row, int column, string image)
  : Tile(row, column, image, 'c'){
};

Tile::Tile(int row, int column, string image, char type)
: Item(column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, image){
  this->row = row;
  this->column = column;
  this->tower = NULL;
  this->type = type;
}

Tile::~Tile(){}

void Tile::update(){}

Tile* createTile(int row, int column, char c){
  if(c == 'c'){
    return new CreepTile(row, column);
  }
  if(c == 'w'){
    return new WallTile(row,column);
  }
  if(c == 't'){
    return new TowerTile(row, column);
  }
  if(c == 's'){
    return new StartTile(row, column);
  }
  if(c == 'e'){
    return new EndTile(row, column);
  }
  return new Tile(row, column);
}

char Tile::getType(){
  return type;
}

BasicTower* Tile::getTower() {
  return tower;
}

bool Tile::hasTower() {
  if (tower == NULL){
    return false;
  }
  else
    return true;
}
