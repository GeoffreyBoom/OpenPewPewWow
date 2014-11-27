/*
 * mapobserver.cpp
 *
 *  Created on: Oct 29, 2014
 *      Author: geoffrey
 */

#include "mapobserver.h"


MapObserver::MapObserver(){}

MapObserver::MapObserver(Map* map) {
  gui = false;
  subject = map;
  subject->attach(this);
}

MapObserver::MapObserver(Map* map, Display* display) {
  gui = true;
  subject =  map;
  subject->attach(this);
  dis = display;
}

MapObserver::~MapObserver() {
  //subject->detach(this);
}

void MapObserver::update() {
  display();
}

void MapObserver::display() {
  vector<string> images = {
      "images/creeptile.png",
      "images/walltile.png",
      "images/towertile.png",
      "images/starttile.png",
      "images/endtile.png"
  };
  if(gui){
    if(initialized){
      for(int i = 0; i < sprites.size();i++){
        for(int j = 0; j < sprites[i].size(); j++){
          dis->removeSprite(sprites[i][j],0);
        }
      }
    }
    else{
      for(int row = 0; row < subject->getRows(); row++){
        sprites.push_back(vector<sf::Sprite*>());
        for(int column = 0; column < subject->getColumns(); column++){
          sprites[row].push_back(NULL);
        }
      }
      initialized = 1;
    }
  }
  if(gui){
    for(int row = 0; row < subject->getRows(); row++){
      for(int column = 0; column < subject->getColumns(); column++){
        Tile currTile = subject->getTile(row,column);
        if(debugPrint){
          printf("in MapObserver: currTile image: '%s', posX: %i, posY: %i\n",
              currTile.getImage().c_str(), currTile.getPosX(), currTile.getPosY());
        }
        if(sprites[row][column]!=NULL){
          delete sprites[row][column];
        }
        sprites[row][column] = dis->createSprite(currTile.getImage(), currTile.getPosX(), currTile.getPosY());
        dis->addSprite(sprites[row][column],0);
      }
    }
  }

  if(!gui || debugPrint){
    for(int row = 0; row < subject->getRows(); row++ ){
      for(int column = 0; column < subject->getColumns(); column++){
        printf("%c", subject->getTileType(row, column));
      }
      printf("\n");
    }
  }

}
