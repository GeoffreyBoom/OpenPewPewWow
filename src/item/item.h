//item class is at the top of the chain, as everything derrives from it

//generic libs to include in program
#ifndef ITEM_H
#define ITEM_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
using namespace std;

class Item{
  public:
    int posX;
    int posY;
    int width;
    int height;
    string image;


    virtual int getPosX();
    virtual int getPosY();
    virtual int getWidth();
    virtual int getHeight();
    virtual void setHeight(int);
    virtual void setWidth(int);
    virtual void setPosX(int);
    virtual void setPosY(int);
    virtual int getCenterX();
    virtual int getCenterY();

    void setImage(string newimage);
    double distance(Item * it);
    string getImage();
    Item();
    Item(int x, int y, int width, int height, string image);
    virtual ~Item();
    //accepts x,y coordinates and calculates if has been clicked
    bool isClicked(int x, int y);
};
#endif
