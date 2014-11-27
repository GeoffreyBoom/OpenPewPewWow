
#include <iostream>
#include <string>
#include <vector>
#include "../creep/boss.h"
#include "../creep/creep.h"
#include "../builder/builder.h"


using namespace std;


class CreepFactory : public Creep {

public:

    static vector<Creep*>* Create(CreepBuilder*);


private:
    CreepFactory();

    static int wave;


};
