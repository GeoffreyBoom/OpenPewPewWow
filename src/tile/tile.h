#ifndef TILE_H
#define TILE_H
#include "../item/item.h"
#include "../creep/creep.h"
#include "../tower/basicTower.h"
#include "../display/display.h"
#include <vector>
#include <string>


using namespace std;

class Tile: public Item{
  friend class Map;
  public:
    void update();
    //makes a tile
    Tile();
    //makes a tile with posx,posy as i and j. default image
    Tile(int i, int j);
    //makes a tile with posx and posy, with a specific image
    Tile(int i, int j, string image);
    //sets everything, including type
    Tile(int i, int j, string image, char type);
    //destructor
    virtual ~Tile();
    char getType();
  protected:
    BasicTower* getTower();
    bool hasTower();
    //a tile can only have one tower
    BasicTower* tower;
    //gets the type of the tile
    char type;
    int row;
    int column;

};

Tile* createTile(int row, int column, char type);
#endif
