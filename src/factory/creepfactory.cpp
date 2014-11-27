#include "../factory/creepfactory.h"

vector<Creep*>* CreepFactory::Create(CreepBuilder* builder){

    int waveNum = builder->getWave();
    int numCreeps;

    if (waveNum < 10){
        numCreeps = (10 + waveNum/2);

    }else{
        numCreeps = (waveNum*1.5 + 1);
    }

    vector<Creep*>* bunker = new vector<Creep*>;

    if (waveNum%10 == 0){
        bunker->push_back(builder->Create(waveNum,"boss1"));
    }

    for(int i = 0; i<numCreeps; i++ ){

        switch(bunker->size()%3){
        case 1:
            bunker->push_back(builder->Create(waveNum,"creep1"));
            break;
        case 2:
            bunker->push_back(builder->Create(waveNum,"creep2"));
            break;
        default:
            bunker->push_back(builder->Create(waveNum,"creep3"));
            break;

        }


    }



    return bunker;


 }







