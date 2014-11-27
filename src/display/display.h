#ifndef DISPLAY_H
#define DISPLAY_H

#include "../item/item.h"
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <string>

using namespace std;

class Display: public sf::RenderWindow{
  private:
    vector<vector<sf::Sprite*> > sprites;
    vector<sf::Drawable*> drawables;
    float scale;

  public:


    static const bool debugPrint = 0;
    Display();
    Display(int x, int y);
    Display(int x, int y, float scale);
    Display(int x, int y, float scale, string name);
    ~Display();

    void addSprite(sf::Sprite* s, int layer);
    void removeSprite(sf::Sprite* s, int layer);
    void addDrawable(sf::CircleShape*);
    void removeDrawable(sf::CircleShape*);
    sf::Sprite* createSprite(string filename, int posX, int posY);

    void overlay();
    void show();
    void minSize(int* minHeight, int* minWidth);

    float getMouseX();
    float getMouseY();

  private:

    float getScale();
    void setScale(float scale);
};


#endif
