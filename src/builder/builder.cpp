#include<iostream>
#include<string>
#include<vector>
#include "builder.h"
#include "../creep/creep.h"


CreepBuilder::CreepBuilder(){
    this->movement = new Path();

    this->wave = 1;

    this->startCoordX = 0;
    this->startCoordY = 0;

    this->creepImage1 = "images/creep1.png";
    this->creepImage2 = "images/creep2.png";
    this->creepImage3 = "images/creep3.png";

    this->woundedImage1 = "images/creep_level_1_is_hit.png";
    this->woundedImage2 = "images/creep_level_2_is_hit.png";
    this->woundedImage3 = "images/creep_level_3_is_hit.png";

    this->bossImage1 = "images/creep.png";

    this->cImageIni = true;
    this->bImageIni = true;
    this->coordIni = true;
}

CreepBuilder::CreepBuilder(Path* mov){

    this->movement = mov;

    this->wave = 1;

    this->startCoordX = 0;
    this->startCoordY = 0;

    this->creepImage1 = "images/creep1.png";
    this->creepImage2 = "images/creep2.png";
    this->creepImage3 = "images/creep3.png";

    this->woundedImage1 = "images/creep_level_1_is_hit.png";
    this->woundedImage2 = "images/creep_level_2_is_hit.png";
    this->woundedImage3 = "images/creep_level_3_is_hit.png";

    this->cImageIni = true;

    this->bossImage1 = "images/creep.png";
    this->bImageIni = true;


    this->coordIni = true;


}

void CreepBuilder::setWave(int waveNum){
    this->wave = waveNum;
}

void CreepBuilder::setPath(Path* mov){

    movement = mov;
    pathIni = true;

}

void CreepBuilder::setStart(int sX, int sY){
    startCoordX = sX;
    startCoordY = sY;

    coordIni = true;
}

void CreepBuilder::setImage(string image, string type){


    if (type == "creep1"){
        creepImage1 = image;
        cImageIni = true;
    }else if (type == "boss1"){
        bossImage1 = image;
        bImageIni = true;
    }

}

void CreepBuilder::incWave(){
    this->wave += 1;
}

void CreepBuilder::setDifficultyMod(int lvl){
    this->difficulty = lvl;
}

int CreepBuilder::getDifficultyMod(){
    return this->difficulty;
}

int CreepBuilder::getWave(){
    return this->wave;

}
//returns new creep given waveNumber and creep Type
Creep* CreepBuilder::Create(int wave, string type){
        int startHP = (this->wave*this->difficulty);

        if (type == "creep1"){
            Creep* creep = (new Creep(wave, startHP, startCoordX,startCoordY, WIDTH, HEIGTH, creepImage1, movement));
            creep->setWoundedImage(woundedImage1);
            return creep;

        }else if (type == "creep2"){
            Creep* creep = (new Creep(wave, (startHP+(3*wave/2)), startCoordX,startCoordY, WIDTH, HEIGTH, creepImage2, movement));
            creep->setWoundedImage(woundedImage2);
            return creep;

        }else if (type == "creep3"){
            Creep* creep = (new Creep(wave, (startHP+(5*wave/3)), startCoordX,startCoordY, WIDTH, HEIGTH, creepImage3, movement));
            creep->setWoundedImage(woundedImage3);
            return creep;
        }else if (type == "boss1"){
            Creep* creep =(new Boss(wave,(startHP*10), startCoordX,startCoordY, WIDTH, HEIGTH, bossImage1, movement));
            creep->setWoundedImage(woundedImage2);
            return creep;
        }else{
            return (new Creep(wave, startHP, startCoordX,startCoordY, WIDTH, HEIGTH, creepImage1, movement));
        }



 }





