#include "map.h"
#include <cstddef>
Map::Map()
	:Map(0, 0){}

Map::Map(int rows, int columns)
	: Subject(){
	this->rows = rows;
	this->columns = columns;
	this->grid = TileGrid(rows);
	this->startColumn = -1;
	this->startRow = -1;
	this->endRow = -1;
	this->endColumn = -1;
	this->editable = false;
	for (int row = 0; row < rows; row++){
		for (int column = 0; column < columns; column++){
			Tile* tmp = new Tile(row, column);
			grid.at(row).push_back(tmp);
		}
	}

	mDistance = NULL;
	path = NULL;
	pathlist = NULL;
}

Map::Map(int row, int columns, Point start, Point finish, vector<Tile*> *vTile){
	this->columns = columns;
	this->rows = row;
	this->startColumn = start.getH();
	this->startRow = start.getV();
	this->endColumn = finish.getH();
	this->endRow = finish.getV();
	this->grid = TileGrid(rows);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			grid.at(i).push_back(vTile->at(0));
			vTile->erase(vTile->begin());
		}
	}

	mDistance = new int*[row];
	for (int i = 0; i < row; i++)
	{
		mDistance[i] = new int[columns];
	}

	computeMdistance();



	this->path = aStarSearch(&start, &finish);
	//cout << "path size: " << path->size() << endl;
}

Map::~Map(){}

/*asks player for where to save, and prints a file of characters.*/
string Map::save(void){
	cout << "\nwhat should this map be saved as\n";
	printf(">");
	string filename;
	cin >> filename;
	filename = "mapfiles/" + filename;
	ofstream f;
	f.open(filename.c_str(), ios::out);
	//f << w << "," << h << "\n";
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			f << (getTileType(i,j));
		}
		f << '\n';
	}
	f.close();

	return filename;
}


//makes a map out of a text file
Map::Map(string oldMapFile) throw (int)
	:Subject(){
	if (debugprint){ printf("Loading Map: %s\n", oldMapFile.c_str()); }
	string line;
	fstream myfile;
	myfile.open(oldMapFile.c_str(), ios::in);
	this->grid = TileGrid(0);
	rows = 0;
	columns = 0;
	if (myfile.is_open()){
		if (debugprint){ printf("Map:\n  "); }
		for (int row = 0; getline(myfile, line); row++){
			rows++;
			columns = line.size();
			vector<Tile*> tmpvector;
			grid.push_back(tmpvector);
			for (int column = 0; column < line.size(); column++){
			  Tile* tmp;
			  if(line[column] == 't'){
			    TowerTile* tmpTower = new TowerTile(row,column);
			    towerTiles.push_back(tmpTower);
			    tmp = tmpTower;
			  }
			  else{
			    tmp = createTile(row, column, line[column]);
			  }
				grid.at(row).push_back(tmp);
				if (debugprint){ printf("%c", tmp->getType()); }
			}
			if (debugprint){ printf("\n  "); }
		}
		myfile.close();
	}
	if (!checkCorrectness()){
		throw 10;
	}
	else{
		if (debugprint){
			cout << "Map Loaded" << endl;
			printf("  statistics of loaded map:\n");
			printf("  h: %i, w: %i\n", rows, columns);
			printf("  start: row:%i, column:%i \n  end: row:%i, column:%i.\n", startRow, startColumn, endRow, endColumn);
		}
	}
	setPath();
	Player::getPlayer()->setEndPosX(getEndX());
	Player::getPlayer()->setEndPosY(getEndY());

}

string Map::mapeditor(Display* dis){
  //boolean to check if the mouse has been clicked but not lifted
  bool clicked = 0;
  //creating a close button
  Item* done = new Item(0,getRows()*TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT,"images/done.png");

  sf::Sprite* donesprite = dis->createSprite(done->getImage(),done->getPosX(),done->getPosY());
  //donesprite should be on layer 0
  dis->addSprite(donesprite,1);

  notify();
  dis->show();

  while(true){
    sf::Event event;
    while(dis->pollEvent(event)){
      //if the window close button has been pressed, and there is a path, close the window.
      if (event.type == sf::Event::Closed){
        dis->close();
        return "";
      }
      //if the mouse is released, set clicked false
      if(event.type == sf::Event::MouseButtonReleased){
        clicked = false;
      }
      //checks if the mouse is pressed and if it hasn't been released
      else if (event.type == sf::Event::MouseButtonPressed && !clicked){
        clicked = true;
        int x = dis->getMouseX();
        int y = dis->getMouseY();
        if(done->isClicked(x,y)){
          if(checkCorrectness()){
            printf("\n----Path Found!----\n\n");
            dis->close();
            string filename = save();
            return filename;
          }
          else{
            printf("\n----Path Not Found, Or you don't have a Tower Tile, Try Again!----\n");
          }
        }
        for(int i = 0; i < grid.size(); i++){
          for(int j = 0; j < grid[0].size();j++){
            if(getTile(i,j).isClicked(x,y)){
              modSetTile(i,j);
              break;
            }
          }
        }
      }
    }
    dis->show();
  }
  return "";
}

Tile* Map::getTilePointer(int row, int column){
	return grid[row][column];
}

bool Map::inrange(int row, int column){
	if (row >= 0 && row < rows){
		if (column >= 0 && column < columns){
			return true;
		}
	}
	return false;
}



bool Map::checkCorrectness(){
  if(checkPath() && checkTower()){
    return true;
  }
  else
    return false;
}

/* Checks if there is a path from start to finish.*/
bool Map::checkPath(){
	if (findStartEnd()){
		vector<vector<int> > intmap = toInts();
		intmap = depthFirstMark(startRow, startColumn, intmap);
		if (intmap[endRow][endColumn] == 2){
			return true;
		}
	}
	return false;
}

bool Map::checkTower(){
  vector<vector<char> > charmap = toChars();
  int numTowers = 0;
  for (int row = 0; row < charmap.size(); row++){
      for (int column = 0; column < charmap[0].size(); column++){
        char currchar = charmap[row][column];
        if (currchar == 't'){
          numTowers++;
      }
    }
  }
  if (numTowers >= 1){
    if (debugprint){ printf("In isTower: found a tower\n"); }
    return true;
  }
  else{
    return false;
  }
}

/*goes through the int grid recursively and marks all the places it can go to with a 2.*/
vector<vector<int> > Map::depthFirstMark(int currRow, int currColumn,
	vector<vector<int> > intmap){
	if (currRow + 1 < intmap.size() && intmap[currRow + 1][currColumn] == 1){
		intmap[currRow + 1][currColumn] = 2;
		intmap = depthFirstMark(currRow + 1, currColumn, intmap);
	}
	if (currRow - 1 >= 0 && intmap[currRow - 1][currColumn] == 1){
		intmap[currRow - 1][currColumn] = 2;
		intmap = depthFirstMark(currRow - 1, currColumn, intmap);
	}
	if (currColumn + 1 < intmap[0].size() && intmap[currRow][currColumn + 1] == 1){
		intmap[currRow][currColumn + 1] = 2;
		intmap = depthFirstMark(currRow, currColumn + 1, intmap);
	}
	if (currColumn - 1 >= 0 && intmap[currRow][currColumn - 1] == 1){
		intmap[currRow][currColumn - 1] = 2;
		intmap = depthFirstMark(currRow, currColumn - 1, intmap);
	}
	return intmap;
}


//returns a 2D vector of chars representing the type of the tiles on the map
vector<vector<char> > Map::toChars(){
	vector<vector<char> > returnArray(rows);
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			returnArray[i].push_back(getTileType(i,j));
		}
	}
	return returnArray;
}

/*converts this map to a grid of integers (1 for walkable, 0 for not walkable)*/
vector<vector<int> > Map::toInts(){
	vector<vector<int> > intmap(grid.size());
	for (int row = 0; row < grid.size(); row++){
		for (int column = 0; column < grid[0].size(); column++){
			char currchar = getTileType(row,column);
			if (currchar == 'c' || currchar == 's' || currchar == 'e'){
				intmap[row].push_back(1);
			}
			else{
				intmap[row].push_back(0);
			}
		}
	}
	return intmap;
}

/*
 * goes through map and finds start and end.
 * returns true if one and only one start and one and only one end were found
 */
bool Map::findStartEnd(){
	vector<vector<char> > charmap = toChars();
	int numStart = 0;
	int numEnd = 0;
	for (int row = 0; row < charmap.size(); row++){
		for (int column = 0; column < charmap[0].size(); column++){
			char currchar = charmap[row][column];
			if (currchar == 's'){
				startRow = row;
				startColumn = column;
				numStart++;
			}
			else if (currchar == 'e'){
				endRow = row;
				endColumn = column;
				numEnd++;
			}
		}
	}
	if (numStart == 1 && numEnd == 1){
		if (debugprint){ printf("In findStartEnd: found find and start\n"); }
		return true;
	}
	return false;
}

void Map::print(){
	for (int row = 0; row < rows; row++){
		for (int column = 0; column < columns; column++){
			printf("%c ", (getTile(row, column).getType()));
		}
		cout << endl;
	}
}

void Map::setPath() {
  //computing mdistance
  mDistance = new int*[getRows()];
  for (int i = 0; i < getRows(); i++)
  {
    mDistance[i] = new int[getColumns()];
  }
  computeMdistance();

  Point* start = new Point(getStartRow(),getStartColumn());
  Point* finish = new Point(getEndRow(),getEndColumn());
  this->path = aStarSearch(start, finish);
  this->pathlist = new Path(*path);
}

bool Map::tileHasTower(int row, int column) {
  if(row < getRows() && column < getColumns()){
    Tile* tile = getTilePointer(row,column);
    if (tile->hasTower()){
      return true;
    }
    else return false;
  }
  else return false;
}

ostream& operator<<(ostream& st, Map& m) {
	string s = "";

	for (int row = 0; row < m.getRows(); row++){
		for (int column = 0; column < m.getColumns(); column++){
			char type = m.getTile(row, column).getType();
			Point *temp = new Point(row, column);
			if (type == 's')
			{
				s += " S";

			}
			else if (type == 'e')
			{
				s += " X";

			}
			else if (Map::isInVector(*temp, m.path)){
				s += " .";
			}
			else if (type == 'c')
			{
				s += "  ";

			}

			else
			{
				s += " #";

			}
		}
		s += "\n";
	}

	return st << s;
}
/*prints a grid of integers.*/
void Map::printIntGrid(vector<vector<int> > intgrid){
	for (int row = 0; row < intgrid.size(); row++){
		for (int column = 0; column < intgrid[row].size(); column++){
			printf("%i", intgrid[row][column]);
		}
		printf("\n");
	}
}

//returns a h x w vector<vector<tiles*> >
TileGrid Map::getGrid(){
	return grid;
}

//changes the tile to one of the new type
bool Map::setTile(int row, int column, char type){
	if (editable){
	  delete grid[row][column];
		grid[row][column] = createTile(row, column, type);
		notify();
		return true;
	}
	return false;
}

bool Map::modSetTile(int row, int column){
  char type = getTileType(row, column);
	const int numTypes = 5;
	char types[numTypes] = {'c','w','t','s','e'};
	for(int i = 0; i < numTypes; i++){
	  if(types[i] == type){
      if(setTile(row,column,types[(i+1)%numTypes])){
        return true;
      }
      break;
    }
  }
	return false;
}

int Map::getRows(){
	return rows;
}
int Map::getColumns(){
	return columns;
}
int Map::getStartRow(){
	return startRow;
}
int Map::getStartColumn(){
	return startColumn;
}
int Map::getEndRow(){
	return endRow;
}
int Map::getEndColumn(){
	return endColumn;
}

bool Map::isTowerTile(int row, int column) {
	if (!inrange(row, column)){ return false; }
	return getTile(row, column).getType() == 't';
}

bool Map::isCritterTile(int row, int column) {
	if (debugprint){ printf("Testing if tile is critter tile"); }
	if (!inrange(row, column)){ return false; }
	if (getTile(row, column).getType() == 'c') return true;
	if (getTile(row, column).getType() == 'e') return true;
	if (getTile(row, column).getType() == 's') return true;
	else return false;
}

void Map::setEditable(bool editable) {
	this->editable = editable;
}

Tile Map::getTile(int row, int column) {
	return *grid[row][column];
}

char Map::getTileType(int row, int column) {
	return getTile(row, column).getType();
}



//-------------------------------------------------------
//Path fiding methods


// if a value is in vector
bool Map::isInVector(Point p, vector<Point*> * v){
	if (v == NULL)
	{
		return false;
	}
	else{
		for (int i = 0; i < v->size(); i++)
		{
			if (p.getH() == v->at(i)->getH() && p.getV() == v->at(i)->getV())
			{
				return true;
			}
		}
		return false;
	}

}
// if a node is in vector
bool Map::isInVector(Node n, vector<Node*> * v){
	if (v == NULL)
	{
		return false;
	}
	else{

		for (int i = 0; i < v->size(); i++)
		{
			if (n.getPoint()->getH() == v->at(i)->getPoint()->getH() && n.getPoint()->getV() == v->at(i)->getPoint()->getV())
			{
				return true;
			}
		}
		return false;
	}
}


bool Map::sortNode(Node *a, Node *b){
	return (a->getFcost() < b->getFcost());
}


vector<Point*> *Map::aStarSearch(Point *start, Point *end){
	vector<Node *> *openList = new vector < Node * > ;
	vector<Node *> *closedList = new vector < Node * > ;
  Node *currentN = new Node(start, NULL, 0, mDistance[start->getV()][start->getH()]);
  openList->push_back(currentN);

	while (openList->size() > 0)
	{
		sort(openList->begin(), openList->end(), sortNode);
		currentN = openList->at(0);
		if (currentN->getPoint()->getH() == end->getH() && currentN->getPoint()->getV() == end->getV())
		{
			vector<Point*> * path = new vector < Point * > ;
			while (currentN->getParent() != NULL)
			{
				path->insert(path->begin(), currentN->getPoint());
				currentN = currentN->getParent();
			}
			return path;
		}
		closedList->push_back(currentN);
		openList->erase(openList->begin());
		vector<Point*> * parents = computeParentNodes(currentN->getPoint());

		for (int i = 0; i < parents->size(); i++)
		{
			Point *t = parents->at(i);
			int gCost = currentN->getGcost() + 1;
			int hCost = mDistance[t->getV()][t->getH()];
			Node *n = new Node(t, currentN, gCost, hCost);
			if (isInVector(*n, closedList) && (gCost+hCost) >= currentN->getFcost())
			{
				continue;
			}
			if (!isInVector(*n, openList) || (gCost+hCost) < currentN->getFcost())
			{

				openList->push_back(n);
			}
		}

	}
	//cout << "failed. No path found.\n";
	return NULL;
}
// compute Manhattan distance
void Map::computeMdistance() {
	Point* s;
	Point* e = new Point(endRow, endColumn);

	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < columns; j++)
		{
			s = new Point(i, j);
			mDistance[i][j] = abs(e->getH() - s->getH()) + abs(e->getV() - s->getV());
		}
	}
}

vector<Point*>* Map::computeParentNodes(Point *current) {
	IntGrid walkableGrid = toInts();
	vector<Point*> *parents = new vector < Point* > ;
	Point* north = current->north();
	Point* south = current->south();
	Point* west = current->west();
	Point* east = current->east();
	if (west == nullptr) {
		//no west node
	}
	else {
		if (walkableGrid.at(west->getV()).at(west->getH()) == 1)
		{
			parents->push_back(west);
		}

	}
	if (north == nullptr) {
		//no north node
	}
	else {
		if (walkableGrid.at(north->getV()).at(north->getH()) == 1)
		{
			parents->push_back(north);
		}
	}
	if (east == nullptr || east->getH() >= columns) {
		// no east node
	}
	else {
		if (walkableGrid.at(east->getV()).at(east->getH()) == 1) {
			// there is a east node
			parents->push_back(east);
		}
	}
	if (south == nullptr || south->getV() >= rows) {
		//no south node
	}
	else {
		if (walkableGrid.at(south->getV()).at(south->getH()) == 1)
		{
			parents->push_back(south);
		}
	}
	//sort(parents->begin(), parents->end());
	//cout << "number of parents :  " << parents->size() << endl;
	return parents;

}

//MAKES A RANDOM MAP
Map* Map::generateMap(int rows, int columns, Point start, Point finish){
	this->rows = rows;
	this->columns = columns;
	vector<Tile*> *vTiles = new vector <Tile*> ;
	srand(time(NULL));
	int randomNumber = 0;
	for (int i = 0; i < rows*columns; i++)
	{
		randomNumber = rand() % 10 + 1;

		Point *point = convertIdtoPoint(i);
		if (randomNumber <= 2)
		{
			vTiles->push_back(new WallTile(point->getV(), point->getH()));
		}
		else
		{
			vTiles->push_back(new CreepTile(point->getV(), point->getH()));
		}
	}
	//create a map using random tiles
	int startId = convertPointToId(start);
	int endId = convertPointToId(finish);
	vTiles->at(startId) = new StartTile(start.getV(), start.getH());
	vTiles->at(endId) = new EndTile(finish.getV(), finish.getH());

	Map *m = new Map(rows, columns, start, finish, vTiles);

	return m;

}

// Convert id to point format
Point* Map::convertIdtoPoint(int id) {
	return new Point((id / columns), id % columns);
}

//convert point to id format
int Map::convertPointToId(Point a) {
	if (a.getV() == 0) {
		return a.getH();
	}
	else {
		return columns * (a.getV()) + a.getH();
	}
}

Path* Map::getPath() {
  return pathlist;
}

bool Map::setTower(int row, int column, BasicTower* tower) {
  if(isTowerTile(row,column)){
    getTilePointer(row,column)->tower = tower;

    return true;
  }
  else{
    return false;
  }
}

BasicTower* Map::getTower(int row, int column) {
  return getTilePointer(row,column)->getTower();
}

int Map::getStartX() {
  return getStartColumn() * TILE_WIDTH + TILE_WIDTH/2;
}

int Map::getStartY() {
  return getStartRow() * TILE_HEIGHT + TILE_HEIGHT/2;
}

int Map::getEndX() {
  return getEndColumn() * TILE_WIDTH + TILE_WIDTH/2;
}

int Map::getEndY() {
  return getEndRow() * TILE_HEIGHT + TILE_HEIGHT/2;
}
