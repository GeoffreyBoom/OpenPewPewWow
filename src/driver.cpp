#include "item/item.h"
#include "tower/towerViewCLI.h"
#include "tower/basicTower.h"
#include "tower/towerdecorator.h"
#include "tower/flamedecorator.h"
#include "tower/sharpendecorator.h"
#include "tower/shrapneldecorator.h"
#include "tower/frozendecorator.h"
#include "map/map.h"
#include "tile/tile.h"
#include "observer/mapobserver.h"
#include "observer/creepobserver.h"
#include "builder/wavebuilder.h"
#include "display/display.h"

#include "display/sizeconstants.h"

#include <stdlib.h>
#include <stdio.h>
#include "creep/creep.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <dirent.h>
#include <string>

#define concurrent

#ifndef NULL
#define NULL   ((void *) 0)
#endif

const int Mil_Per_Frame = 15;


void EditMap();
void StartGame();

//------support functions------//
//lists a directory
void listDir(string);
//creates observers for creeps
vector<CreepObserver*>* generateCreepObservers(vector<Creep*>* creepList, Display* disp);
//ask for input
string requestInput(string);
//print things
void printOut(string);
//-------End support functions-------//

int main(int args, char** argv){
  while(true){
    string input = requestInput("Do you want to: [Edit] a map, [Start] the game, or [Exit]");
    if(input == "Edit" || input == "edit"){
      EditMap();
    }
    if(input == "Start" || input == "start"){
      StartGame();
    }
    if(input == "Exit"||input == "exit"){
      break;
    }
  }

}

void EditMap(){
  string input = requestInput("Would you like to edit an [Old] map or a [New] map");
  string mapFiles = "mapfiles/";
  string file;
  if(input == "New" || input == "new"){
    int rows;
    int columns;
    printf("\nhow many columns would you like your map to have?\n");
    printf(">");
    cin >> columns;
    printf("\nhow many rows would you like your map to have?\n");
    printf(">");
    cin >> rows;
    Map editable = Map(rows,columns);
    editable.setEditable(true);
    Display dis(100,100,DEFAULT_SCALE);
    MapObserver* obs = new MapObserver(&editable,&dis);
    file = editable.mapeditor(&dis);
    printOut("Finished editing: " + file + " returning to main menu");
    return;
  }
  else{
    listDir(mapFiles);
    string file = requestInput("Which map would you like to edit?");

    Map* editable = NULL;
    try{
      editable = new Map(mapFiles + file);
    }
    catch(int e){
      printOut("the map you are trying to edit is broken or does not exist");
      return;
    }
    editable->setEditable(true);
    Display dis(100,100,DEFAULT_SCALE);
    MapObserver* obs = new MapObserver(editable,&dis);
    file = editable->mapeditor(&dis);
    printOut("Finished editing: " + file + " returning to main menu");
    return;
  }
}


bool gameOver(int waves);

void StartGame(){

  int waves = 5;
  int startWave = 1;
  printf("\nhow many waves would you like to play?\n");
  printf(">");
  cin >> waves;
  if(waves < 1){
    printf("\n----Invalid Wave Number----\n");
    return;
  }
  printf("\nWhat wave would you like to start on?\n");
  printf(">");
  cin >> startWave;
  if(startWave < 1){
    printf("\n----Invalid Start Wave----\n");
    return;
  }
  //request map
  listDir("mapfiles/");
  string mapChoice = requestInput("which map would you like to play on?");
  printOut("You chose: " + mapChoice);
  //load map
  string mapFiles = "mapfiles/";
  Map* map = NULL;
  try{
    map = new Map(mapFiles + mapChoice);
  }
  catch(int e){
    printOut("the map you are trying to edit is broken or does not exist");
    return;
  }
  catch(...){
    printOut("an unknown error occured.");
    return;
  }
  //initialize game
  Display* display = new Display(map->getColumns() * TILE_WIDTH * DEFAULT_SCALE,
      map->getRows()*TILE_HEIGHT* DEFAULT_SCALE+ TILE_HEIGHT*DEFAULT_SCALE,
      DEFAULT_SCALE,
      "MainGame");
  MapObserver* mapobs = new MapObserver(map, display);
  WaveBuilder* wBuild = new WaveBuilder(map->getPath(), display);
  wBuild->setWave(startWave);
  map->notify();


  //creating done click
  Item* done = new Item(0,map->getRows()*TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT,"images/done.png");
  sf::Sprite* donesprite = display->createSprite(done->getImage(),done->getPosX(),done->getPosY());
  display->addSprite(donesprite, 3);

  sf::Clock clock;

  //load wave data structure
  //while more waves:
#ifdef concurrent
  while(!gameOver(waves)){
    //Int32 time = time.asMilliseconds();
    display->show();
    //start tower selection process
    //while they haven't asked for new wave
    bool clicked = 0;
    int x = -1;
    int y = -1;

    //Wave Loop
    wBuild->setStartCoords(map->getStartColumn()*TILE_WIDTH+TILE_WIDTH/2,
            map->getStartRow()*TILE_HEIGHT+TILE_HEIGHT/2);
    wBuild->spawnWave();
    cout << "\n" <<"---Current Wave : " << (wBuild->getWave()-1) << "---" << endl;
    cout << "\n" <<"---Current Health : " << Player::getPlayer()->getLife() << "---" << endl;
    bool startWave = false;
    printOut("Buy or Upgrade your Towers!");
    printf("\n----Your current money is: %i----\n", Player::getPlayer()->getMoney());
    do{
      //processing display events
      sf::Event event = sf::Event();
      while(display->pollEvent(event)){
        if (event.type == sf::Event::Closed){
          display->close();
          printOut("Game Exited");
          return;
        }
        if (event.type == sf::Event::MouseButtonReleased){
          clicked = false;
        }
        if (event.type == sf::Event::MouseButtonPressed && !clicked){
          clicked = true;
          x = display->getMouseX();
          y = display->getMouseY();
        }
      }

      int row;
      int column;

      if(x != -1 && y != -1 && !clicked){
        row = y / TILE_HEIGHT;
        column = x / TILE_WIDTH;

        if(done->isClicked(x,y)){
          printOut("done editing");
          startWave = true;
        }
        else{
          map->editTower(row,column,display);
        }
        display->show();
        x = -1; y = -1;
      }

      if(startWave){
        //tick creeps
        wBuild->tickAll();

        //towers get ticked here
        map->tick(wBuild->getCreeps());

        //show display
        display->show();


        Player::getPlayer()->incTick();

      }

      sf::Time time = clock.getElapsedTime();

      sf::Time timeleft = sf::milliseconds(Mil_Per_Frame) - time;

      if(timeleft.asMilliseconds() > 0){
        sf::sleep(timeleft);
      }
      if(!Player::getPlayer()->isAlive()){
        break;
      }
    }while(!(wBuild->waveOver()));
    waves--;
    //end loop
  }
#else
  while(!gameOver(waves)){
    //Int32 time = time.asMilliseconds();
    display->show();
    //start tower selection process
    //while they haven't asked for new wave
    bool clicked = 0;
    int x = -1;
    int y = -1;

    printf("Buy or Upgrade your Towers!\n");
    while(true){
      //processing display events
      sf::Event event = sf::Event();
      while(display->pollEvent(event)){
        if (event.type == sf::Event::Closed){
          display->close();
          printf("game exited\n");
          return;
        }
        if (event.type == sf::Event::MouseButtonReleased){
          clicked = false;
        }
        if (event.type == sf::Event::MouseButtonPressed && !clicked){
          clicked = true;
          x = display->getMouseX();
          y = display->getMouseY();
        }
      }

      int row;
      int column;

      if(x != -1 && y != -1 && !clicked){
        row = y / TILE_HEIGHT;
        column = x / TILE_WIDTH;

        if(done->isClicked(x,y)){
          printf("\n----done editing----\n\n");
          break;
        }

        map->editTower(row,column,display);
        display->show();
        x = -1; y = -1;
      }
      sf::sleep(sf::milliseconds(100));
    }

    //end loop


    //Wave Loop
    wBuild->setStartCoords(map->getStartColumn()*TILE_WIDTH+TILE_WIDTH/2,
            map->getStartRow()*TILE_HEIGHT+TILE_HEIGHT/2);
    wBuild->spawnWave();
    cout << "\n" <<"Current Health : " << Player::getPlayer()->getLife()<< "\n" << endl;


    do{

      clock.restart();
      sf::Time itime = clock.getElapsedTime();

      sf::Event event = sf::Event();
      while(display->pollEvent(event)){
        if (event.type == sf::Event::Closed){
          display->close();
          printf("game exited\n");
          return;
        }
      }
      //tick creeps
      wBuild->tickAll();

      //towers get ticked here
      map->tick(wBuild->getCreeps());

      //show display
      display->show();

      Player::getPlayer()->incTick();

      if(!Player::getPlayer()->isAlive()){
        break;
      }

      sf::Time time = clock.getElapsedTime();

      sf::Time timeleft = sf::milliseconds(Mil_Per_Frame) - time;

      if(timeleft.asMilliseconds() > 0){
        sf::sleep(timeleft);
      }

    }while(!(wBuild->waveOver()));
    waves--;
    //end loop
  }
#endif

  if (!(Player::getPlayer()->isAlive())){
    cout << "\n" << "----GAME OVER -- PLAYER DEFEATED----" << endl;
  }else{
    cout << "\n" << "----Victory! All waves cleared----" << endl;
  }
  Player::getPlayer()->reset();



  delete map;
  display->close();
  delete display;
}

bool gameOver(int waves){
  return (waves == 0)||(!(Player::getPlayer()->isAlive()));
}


vector<CreepObserver*>* generateCreepObservers(vector<Creep*>* creepList, Display* disp){

    vector<CreepObserver*>* obsList = new vector<CreepObserver*>;

    for(int i=0; i<creepList->size(); i++){
      CreepObserver * creepobs = new CreepObserver((*creepList)[i],disp);
      obsList->push_back(creepobs);
    }
    return obsList;

}


void listDir(string folder){
  DIR *dir;
  struct dirent *ent;
  printf("In Folder: %s\n", folder.c_str());
  if ((dir = opendir (folder.c_str())) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      if(string(ent->d_name) != string("..") && string(ent->d_name) != string("."))
        printf ("\t%s\n", ent->d_name);
    }
    closedir (dir);
  }
  else {
    perror ("could not open folder");
  }
}

void printOut(string toPrint){
  printf("\n----%s----\n",toPrint.c_str());
}

string requestInput(string request){
  string returnString = "";
  printf("\n%s\n",request.c_str());
  printf(">");
  cin >> returnString;
  return returnString;
}
