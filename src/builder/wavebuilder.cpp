#include "wavebuilder.h"


WaveBuilder::WaveBuilder(){
   this->cBuild = new CreepBuilder();
   this->bufferTop = 10;
   this->creepBuffer = 0;

}

WaveBuilder::WaveBuilder(Path* path, Display* display){
  this->cBuild = new CreepBuilder(path);
  this->disp = display;
  this->bufferTop = 50;
  this->creepBuffer = 0;

}


void WaveBuilder::spawnWave(){

    this->cList = CreepFactory::Create(cBuild);


    this->gameCreeps = new vector<Creep*>;

    this->cBuild->incWave();


    printf("\n---Creep Wave Spawned---\n");



}

void WaveBuilder::tickAll(){
    int creepNum = this->cList->size();



    if(creepNum > 0){
        if (creepBuffer == 0){
          this->gameCreeps->push_back(cList->back());
          CreepObserver* creepobs = new CreepObserver(this->cList->back(), this->disp);
          cList->pop_back();


        }
        creepBuffer = (creepBuffer + 1) % bufferTop;
      }


    creepNum = this->gameCreeps->size();


    for (int i = 0; i<creepNum; i++){



        (*gameCreeps)[i]->tick();

        if ((gameCreeps->size() == 1)&&(cList->size() == 0)){
            lastCreep = (*gameCreeps)[i];
        }


        if ((*gameCreeps)[i]->isKilled()){
           Player::getPlayer()->deposit((*gameCreeps)[i]->getReward());
        }

        //Creeps in game can either reach the end, or get killed, in which case they're deleted
        if((!(*gameCreeps)[i]->getPath()->hasNext()&&(*gameCreeps)[i]->reachedTarget())||((*gameCreeps)[i]->isKilled())){


           if (!((*gameCreeps)[i]->isKilled())){
              Player::getPlayer()->subLife();
              cout << "\n----" <<"Current Health : " << Player::getPlayer()->getLife() << "----" << endl;
           }

          delete (*gameCreeps)[i];
          (*gameCreeps).erase((*gameCreeps).begin()+i);

        }





         creepNum = this->gameCreeps->size();
    }




}

void WaveBuilder::setPath(Path* path){
    this->cBuild->setPath(path);
}

void WaveBuilder::setWave(int wave){
    this->cBuild->setWave(wave);
}


void WaveBuilder::setDifficulty(int diff){
    this->cBuild->setDifficultyMod(diff);
}

void WaveBuilder::setStartCoords(int x, int y){
    this->cBuild->setStart(x,y);
}



int WaveBuilder::getWave(){
    return cBuild->getWave();
}

int WaveBuilder::getDifficulty(){
    return cBuild->getDifficultyMod();
}

bool WaveBuilder::waveOver(){
    if((gameCreeps->size() == 0)&&(cList->size()==0)){
        //lastCreep->~Subject();
        printf("\n---Wave terminated, all creeps reached the end---\n");
    }

    return ((gameCreeps->size() == 0)&&(cList->size()==0));
}

vector<Creep*>* WaveBuilder::getCreeps(){
    return this->gameCreeps;
}


