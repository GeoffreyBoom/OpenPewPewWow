
#ifndef BOSS_H
#define BOSS_H

#include "creep.h"

class Boss :public Creep{
	public:

        Boss();
		Boss(int, int, int, int, int, int, string, Path*);

};

#endif
