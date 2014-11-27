#ifndef WAVEBUILDER_H_INCLUDED
#define WAVEBUILDER_H_INCLUDED

#include<iostream>
#include<string>
#include<vector>

#include "../creep/creep.h"
#include "../creep/boss.h"
#include "../builder/builder.h"
#include "../observer/creepobserver.h"
#include "../factory/creepfactory.h"
#include "../path/path.h"
#include "../display/display.h"
#include "../player/Player.h"


using namespace std;

class WaveBuilder{

public:

   WaveBuilder();
   WaveBuilder(Path*,Display*);

   void spawnWave();

   void setWave(int);
   void setDifficulty(int);
   void setPath(Path*);
   void setStartCoords(int,int);

   int getWave();
   int getDifficulty();
   Path* getPath();

   void tickAll();

   bool waveOver();


   vector<Creep*>* getCreeps();


private:
   int bufferTop;
   int creepBuffer;
   CreepBuilder* cBuild;
   vector<Creep*>* cList;
   vector<Creep*>* gameCreeps;
   Display* disp;
   Creep* lastCreep;


};






#endif // WAVEBUILDER_H_INCLUDED
