#include "path.h"
using namespace std;


Path::Path(){
  this->next = NULL;
  this->targetX = -1;
  this->targetY = -1;
}
Path::Path(Point* point){
  this->next = NULL;
  setTarget(point);
}

Path::Path(Path* next, Point* point){
  this->next = next;
  setTarget(point);
}

Path::Path(vector<Point*> points){
  Path * next = new Path(points[points.size()-1]);
  if(debugPrint)next->print();
  for(int i = points.size()-2;i > 0; i--){
    //cout << points[i]->getV() <<points[i]->getH() << endl;
    next = new Path(next, points[i]);
    if(debugPrint)next->print();
  }
  this->setTarget(points[0]);
  this->next = next;
  if(debugPrint) this->print();
  setTarget(points[0]);
}

void Path::setTarget(Point* point){
  int targetRow = point->getV();
  int targetCol = point->getH();
  targetX = targetCol*TILE_WIDTH+TILE_HEIGHT/2;
  targetY = targetRow*TILE_HEIGHT+TILE_HEIGHT/2;
}

Path::~Path() {
}

int Path::getTargetX(){
  return targetX;
}
int Path::getTargetY(){
  return targetY;
}
Path* Path::getNext(){
  return next;
}
bool Path::hasNext(){
  return next != NULL;
}

void Path::print(){
  printf("Path target:%i,%i\n", targetX,targetY);
  if(next != NULL){
    next->print();
  }
}

void Path::setNext(Path* next){
  this->next = next;
}
