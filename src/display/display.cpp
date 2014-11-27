#include "display.h"
bool debug_print = false;
bool surface = false;

//makes a display with width 0, height 0, and names it "Tower Defense X"
Display::Display()
  : Display(0,0){}

//makes a display with width x, height y, and names it "Tower Defense X"
Display::Display(int x, int y)
 : Display(x,y,1){}

Display::Display(int x, int y, float scale)
  : Display(x, y, scale, "TDefenseX"){}

//makes a display with width x, height y, and names it name
Display::Display(int x, int y, float scale, string name)
  :sf::RenderWindow(sf::VideoMode(x,y), name) {
  setScale(scale);
}

//destructor
Display::~Display(){}

float Display::getScale() {
  return scale;
}

void Display::setScale(float scale) {
  this->scale = scale;
}

void Display::removeSprite(sf::Sprite* s, int layer) {
  for(int i = 0; i < sprites[layer].size(); i++){
    if (sprites[layer][i] == s){
      sprites[layer].erase(sprites[layer].begin()+i);
    }
  }
}

void Display::addSprite(sf::Sprite* s, int layer) {
  if(sprites.size() <= layer){
    sprites.resize(layer+1);
  }
  s->setScale(getScale(),getScale());
  float x = s->getPosition().x * getScale();
  float y = s->getPosition().y * getScale();
  s->setPosition(x,y);

  sprites[layer].push_back(s);
}

void Display::addDrawable(sf::CircleShape* drawable){
  float x = drawable->getPosition().x * getScale();
  float y = drawable->getPosition().y * getScale();
  drawable->setPosition(x,y);
  drawables.push_back(drawable);
}
void Display::removeDrawable(sf::CircleShape* drawable){
  for(int i = 0; i < drawables.size(); i++){
    if (drawables[i] == drawable){
      drawables.erase(drawables.begin()+i);
    }
  }
}

//currently not working
void Display::minSize(int* minHeight, int* minWidth){
  * minHeight = 0;
  * minWidth = 0;
  for(int layer = 0; layer < sprites.size(); layer++){
    for(int currSprite = 0;currSprite < sprites[layer].size();currSprite++){
      sf::Sprite* sprite = sprites[layer][currSprite];
      sf::FloatRect rect = sprite->getGlobalBounds();
      if((rect.left + rect.width) > *minWidth){
        *minWidth = rect.left + rect.width;
      }
      if((rect.top + rect.height) > *minHeight){
        *minHeight = rect.top + rect.height;
      }
    }
  }
}

//clears the screen and shows all the items
void Display::show(){
  sf::Vector2u curr = getSize();
  int currHeight = curr.y;
  int currWidth = curr.x;
  int minHeight = 0;
  int minWidth = 0;
  //seeing if the window is big enough for all items
  if(!surface){
    minSize(&minHeight,&minWidth);
    if(!(minWidth == currWidth && minHeight == currHeight)&&(minWidth > 0 && minHeight > 0)){
      if(debugPrint) printf("%i,%i,%i,%i\n",minHeight,currHeight,minWidth,currWidth);
      if(debug_print){printf("expanding display to %i, %i\n",minWidth,minHeight);}
      create(sf::VideoMode(minWidth,minHeight),"TDefenseX");
      sf::sleep(sf::milliseconds(100));
    }
  }
  clear();
  overlay();
}

//doesn't clear the screen, overlays the items.
void Display::overlay(){
  for(int i = 0; i < sprites.size();i++){
    for(int j = 0; j < sprites[i].size();j++){
      draw(*sprites[i][j]);
    }
  }
  for(int i = 0; i < drawables.size();i++){
    draw(*drawables[i]);
  }
  display();
}


//returns the x coordinate of the mouse.
float Display::getMouseX(){
  if(debugPrint){
    printf("posx: %i\n", sf::Mouse::getPosition(* this).x);
    printf("posx / scale: %f\n", sf::Mouse::getPosition(* this).x / getScale());
    printf("scale: %f\n", getScale());
  }
  int minHeight = 0;
  int minWidth = 0;
  minSize(&minHeight,&minWidth);
  double actualWidth = getSize().x;
  return ((float)sf::Mouse::getPosition(* this).x) / getScale() * (minWidth / actualWidth);
}
//returns the y coordinate of the mouse
float Display::getMouseY(){
  int minHeight = 0;
  int minWidth = 0;
  minSize(&minHeight,&minWidth);
  double actualHeight = getSize().y;
  return ((float)sf::Mouse::getPosition(* this).y) / getScale() * (minHeight / actualHeight);
}

sf::Sprite* Display::createSprite(string filename, int posX, int posY) {
  static map<string, sf::Texture*> textures = map<string, sf::Texture*>();
  if(textures.count(filename) == 0){
    if(debugPrint) printf("File name '%s' not found in textures,\nloading from file and adding to map\n", filename.c_str());
    sf::Texture* texture = new sf::Texture();
    if(debugPrint) printf("1/2\n");
    texture->loadFromFile(filename);
    if(debugPrint)printf("2/2\n");
    textures[filename] = texture;
  }
  if(debugPrint)printf("creating new Sprite.\n");
  sf::Sprite* sprite = new sf::Sprite(*textures[filename]);
  sprite->setPosition(posX,posY);
  if(debugPrint)printf("Sprite created\n");
  return sprite;
}
