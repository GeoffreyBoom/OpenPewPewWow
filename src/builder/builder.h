#ifndef CREEPBUILDER_H
#define CREEPBUILDER_H
#include<iostream>
#include<string>
#include "../creep/creep.h"
#include "../creep/boss.h"
 // CREEPBUILDER_H

using namespace std;

class CreepBuilder{

public:

    //Only requirement is path object
    CreepBuilder();
    CreepBuilder(Path*);

    //returns new creep given waveNumber and creep Type
    Creep* Create(int, string);

    void setWave(int);
    void setPath(Path*);
    void setStart(int,int);
    void setImage(string, string);
    void incWave();
    void setDifficultyMod(int);

    int getDifficultyMod();
    int getWave();

    Path* getPath();




private:

    Path* movement;
    int startCoordX;
    int startCoordY;
    int difficulty = 2;

    const int WIDTH = 50;
    const int HEIGTH = 50;

    string creepImage1;
    string creepImage2;
    string creepImage3;
    string bossImage1;

    string woundedImage1;
    string woundedImage2;
    string woundedImage3;

    bool cImageIni = false;
    bool bImageIni = false;

    bool coordIni = false;
    bool pathIni = false;

    int wave;

};
#endif
