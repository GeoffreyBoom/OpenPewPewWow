/*
 * tilemanager.cpp
 *
 *  Created on: Nov 22, 2014
 *      Author: geoffrey
 */
#include "map.h"
#include <string>

void Map::tick(vector<Creep*>* creeps){
  for(int index = 0; index < towerTiles.size();index++){
    if(towerTiles[index]->hasTower()){

      BasicTower* focusTower = towerTiles[index]->getTower();
      focusTower->tick(creeps);

    }
  }
}

void Map::editTower(int row, int column, Display* dis){
  if(isTowerTile(row,column)){
    if(tileHasTower(row,column)){
      changeTower(row,column, dis);
    }
    else{
      buyTower(row,column, dis);
    }
  }
  else{
    printf("\n----that is not a tower tile----\n");
  }
}
void Map::buyTower(int row, int column, Display* dis){
  BasicTower* newTower = new BasicTower(column*TILE_WIDTH,row*TILE_HEIGHT);
  string confirm = "";
  printf("\nTower cost: %i is this okay? [y/n]\n>",newTower->getBuyingPrice());
  cin >> confirm;
  if(confirm == "y" || confirm == "Y"){
	  if(Player::getPlayer()->withdraw(newTower->getBuyingPrice())){
		 setTower(row,column,newTower);
		 TowerViewCLI* towerObs = new TowerViewCLI(newTower,dis);
		 printf("\n----added a tower----\n");
	  }
	  else{
		  printf("\n----You do not have sufficient funds----\n");
	  }
  }else{
	  delete newTower;
  }
}

void Map::changeTower(int row, int column, Display* dis){
  printf("Your tower: ");
  getTower(row,column)->displayInfo();
  string input = "";
  printf("\nWould you like to [upgrade], change [strategy] or [sell] the tower or exit\n");
  printf(">");
  cin >> input;
  if(input == "sell"){
    sellTower(row,column);
  }
  else if(input == "upgrade"){
    upgradeTower(row,column,dis);
  }
  else if(input =="change strategy" || input =="strategy" ){
	  changeStrategy(row,column);
  }
  else if(input == "wow"){
    Player::getPlayer()->muchCheat();
  }
  else if(input == "exit"){
    return;
  }

  //if the input was wrong, recurse
  else{
    changeTower(row,column,dis);
  }
}

void Map::changeStrategy(int row, int column){
	Tile* tile = getTilePointer(row,column);
	printf("\nYou can chose between : [closest], [strongest], [weakest], [frozen], [end]\n");
	printf(">");
	string input = "";
	cin >> input;
	BasicTower * tower =tile->getTower();
	if(input == "closest" ){
		tower->setStrategy(new Closest);
	}else if(input == "weakest") {
		tower->setStrategy(new Weakest);
	}else if (input == "strongest"){
		tower->setStrategy(new Strongest);
	}else if (input == "frozen"){
	  tower->setStrategy(new NotFrozenTargeting);
	}else if (input == "end"|| input == "close to the end"){
	  tower->setStrategy(new CloseToTheEdge);
	}else{
		tower->setStrategy(new TargetingPatern);
	}
	tower->displayInfo();
}
void Map::sellTower(int row, int column){
  Player::getPlayer()->deposit(getTower(row,column)->getRefundValue());
  delete getTower(row,column);
  setTower(row,column,NULL);
  printf("\n----Tower Sold----\n");
}

void Map::upgradeTower(int row, int column, Display* dis){
  Tile* tile = getTilePointer(row,column);
  printf("\nWould you like to upgrade with: [sharpen], [flame], [freezing], [shrapnel], [sniper], [speed]\n");
  printf(">");
  string input = "";
  cin >> input;
  printf("\nhow many times would you like to upgrade?\n>");
  int times = 1;
  cin >> times;
  while(Player::getPlayer()->withdraw(getTower(row,column)->getUpgradePrice()) && times-- > 0){
    BasicTower* upTower = NULL;
    if(input == "sharpen"){
      upTower = new SharpenDecorator(tile->getTower());
    }
    else if(input == "flame"){
      upTower = new FlameDecorator(tile->getTower());
    }
    else if(input == "freezing"){
      upTower = new FrozenDecorator(tile->getTower());
    }
    else if(input == "shrapnel"){
      upTower = new ShrapnelDecorator(tile->getTower());
    }
    else if(input == "sniper"){
      upTower = new SniperDecorator(tile->getTower());
    }
    else if(input == "speed"){
      upTower = new SpeedDecorator(tile->getTower());
    }
    if(upTower == NULL){
      upgradeTower(row,column,dis);
    }
    else{
      setTower(row,column,upTower);
      tile->getTower()->displayInfo();
    }
  }
  if(times > 0){
    printf("\n----insufficient funds for the remaining %i upgrades----\n",times);
  }
}


