#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include "../tile/creeptile.h"
#include "../tile/towertile.h"
#include "../tile/walltile.h"
#include "../tile/starttile.h"
#include "../tile/endtile.h"
#include "../subject/subject.h"
#include "../node/node.h"
#include "../point/point.h"
#include "../path/path.h"
#include "../display/display.h"
#include "../player/Player.h"

#include "../display/sizeconstants.h"
#include "../tower/CloseToTheEdge.h"
#include "../tower/towerdecorator.h"
#include "../tower/flamedecorator.h"
#include "../tower/sharpendecorator.h"
#include "../tower/shrapneldecorator.h"
#include "../tower/frozendecorator.h"
#include "../tower/sniperdecorator.h"
#include "../tower/speeddecorator.h"
#include "../tower/towerViewCLI.h"
#include "../tower/weakest.h"
#include "../tower/Closest.h"
#include "../tower/Strongest.h"
#include "../tower/notfrozentargeting.h"
#include <algorithm>
#include <ctime>

using namespace std;

class Map;

//rename 2 dimensional vector of tiles to a tile-grid
typedef vector<vector<Tile*> > TileGrid;
typedef vector<vector<int> > IntGrid;

class Map: public Subject{
  private:
    static const bool debugprint = 0;

    bool editable;
    int rows;
    int columns;
    int startRow;
    int startColumn;
    int endRow;
    int endColumn;


    vector<TowerTile*> towerTiles;

    int **mDistance; // Manhattan distance
    vector<Point*> *path;
    Path* pathlist;

  protected:
    /*sets start and end returns true if found start and end*/
    bool findStartEnd();

    TileGrid grid;

    TileGrid getGrid();

    /*creates a grid of chars based on the types of the map*/
    vector<vector<char> > toChars();

    /* creates a grid of integers 0 for can't walk, 1 for can walk.*/
    IntGrid toInts();

    /*marks a n by m matrix of integers with 2's everywhere it can step*/
    IntGrid depthFirstMark(int currI, int currJ, IntGrid intgrid);

    /*prints a grid of integers*/
    void printIntGrid(IntGrid intgrid);

    //buys a tower
    void buyTower(int row, int column, Display* dis);
    //decides whether to upgrade or sell tower
    void changeTower(int row, int column, Display* dis);
    //upgrades a tower
    void upgradeTower(int row, int column, Display* dis);
    //sells a tower
    void sellTower(int row, int column);

  public:
    //makes a new map of 0x0 size
    Map();
    //makes a new map with all creep tiles
    Map(int rows, int column);
    //makes a new map from a save file
    Map(string oldMapFile) throw (int);

    string mapeditor(Display* dis);

    //makes a map from predefined tiles
    Map(int width, int height, Point start, Point finish, vector<Tile*> *v);

    virtual ~Map();

    bool inrange(int, int);

    //getters
    Path* getPath();
    int getRows();
    int getColumns();
    int getStartRow();
    int getStartColumn();
    int getStartX();
    int getStartY();
    int getEndRow();
    int getEndColumn();
    int getEndX();
    int getEndY();

    Tile getTile(int row, int column);
    Tile* getTilePointer(int row, int column);
    char getTileType(int row, int column);


    /*Determines if there is a path from the start to the end*/
    bool checkPath();
    //Determines if there's a tower tile
    bool checkTower();
    //Determines if the map is correct.
    bool checkCorrectness();

    //saves the map
    string save();

    //sets the map to be editable
    void setEditable(bool editable);
    //sets tile at row x column. returns true if changed
    bool setTile(int row, int column, char type);
    //sets the tile to the next type
    bool modSetTile(int row, int column);



    //tells whether the tile is a tower tile
    bool isTowerTile(int row, int column);
    //tells whether the tile is a tile that a critter can walk on
    bool isCritterTile(int row, int column);

    //returns whether the tile has a tower on it
    bool tileHasTower(int row, int column);

    //sets the tower on the given tile to the passed tower.
    //returns false if the tile was not a towertile
    BasicTower* getTower(int row, int column);
    bool setTower(int row, int column, BasicTower* tower);

    void print();

    //path finding methods
    void setPath();
    void computeMdistance();  //Manhattan algorithm
    vector<Point*>* computeParentNodes(Point *current); // get parent nodes
    vector<Point*>* aStarSearch(Point *start, Point* end); // A* algorithm
    static bool isInVector(Point p, vector<Point*> * v);
    static bool isInVector(Node n, vector<Node*> * v);
    static bool sortNode(Node *a, Node *b);
    Point* convertIdtoPoint(int id); //convert 1D to 2D coordinate
    int convertPointToId(Point a); // convert 2D to 1D coordinate
    Map* generateMap(int rows, int columns, Point start, Point finish);
    friend ostream& operator<<(ostream&, Map&);



    //methods for interacting with towers!
    void tick(vector<Creep*>* creeps);
    void editTower(int row, int column, Display* display);
    void changeStrategy(int row, int column);
};
#endif
