/*
  91.201 Assignment 10
  GameEngine.cpp, GameEngine.hpp, main.cpp, ship.hpp, ShipClass.cpp
  Purpose: Added star Background and the best Goddman physics system 
  TODO: GET Bullets to work with physics system
  TODO: Make enemy AI
  @author Ethan Cumming
  @version 1.0 12/4/15

*/

#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Ship.hpp"
#include <string>
#include <math.h>

using namespace std;
//Class sperate class for generating stars in background
class Background: public sf::Sprite{
  private:
    //Background Image
    sf::Texture BGI;
    sf::Sprite BG;

  public:
    // Use a constructor
    Background();
    void draw(sf::RenderWindow & window);
    void setBackground(string name, sf::Vector2f pos);
    

};
//Main game class
class GameEngine
{
public:
  GameEngine();
  GameEngine(string windowName, int width, int height);
  void runGame();
  void handleEvents();
private:
  sf::RenderWindow window;
  sf::Clock clock;
  sf::Event event;
  Background background;
  PlayerShip player; //player ship
  EnemyShip enemy; //enemy ship
};




#endif
