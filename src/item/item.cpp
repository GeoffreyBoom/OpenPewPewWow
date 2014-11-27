#include "item.h"

Item::Item(int posX, int posY, int width, int height, string imageFile){
  setImage(imageFile);
  this->posX = posX;
  this->posY = posY;
  this->width = width;
  this->height = height;
}

Item::Item()
  : Item(0,0,0,0,""){};

Item::~Item(){};

int Item::getPosX(){
  return posX;
}

int Item::getPosY(){
  return posY;
}

void Item::setPosX(int posX){
	this->posX = posX;
}

void Item::setPosY(int posY){
	this->posY = posY;
}

int Item::getCenterX(){
  return getPosX() + (getWidth()/2);
}

int Item::getCenterY(){
  return getPosY() + (getHeight()/2);
}

int Item::getWidth(){
  return width;
}

int Item::getHeight(){
  return height;
}

void Item::setWidth(int w){
    this->width = w;
}

void Item::setHeight(int h){
    this->height = h;
}

string Item::getImage(){
  return image;
}



bool Item::isClicked(int x, int y){
  if(x > this->getPosX() && x < (this->getPosX() + this-> getWidth()))
    if(y > this->getPosY() && y < (this->getPosY() + this-> getHeight()))
      return true;
  return false;
};

void Item::setImage(string imageFile){
  this->image = imageFile;
}

double Item::distance(Item * it){
	if (it == NULL)
	  return -1.0;
	else
	  return sqrt((this->getPosX() - it->getPosX())*(this->getPosX() - it->getPosX()) + (this->getPosY() - it->getPosY())*(this->getPosY() - it->getPosY()));

}
