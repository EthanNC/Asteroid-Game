#include "GameEngine.hpp"

#define FPS 60
#define DEF_WIDTH 1500
#define DEF_HEIGHT 900
#define _USE_MATH_DEFINES

//TODO here: set the ship location
GameEngine::GameEngine()
{
  window.create(sf::VideoMode(DEF_WIDTH, DEF_HEIGHT), "SFML window", sf::Style::Close);
}

GameEngine::GameEngine(string windowName, int width, int height)
{
  window.create(sf::VideoMode(width, height), windowName); // creates the window
    background.setBackground("starfield.png", sf::Vector2f(1500, 900));
  window.setFramerateLimit(FPS);
  window.setKeyRepeatEnabled(true);
}

void GameEngine::runGame()
{
  while(window.isOpen()){ 
    handleEvents(); //eventLoop 
    player.updateShip(clock.restart().asMilliseconds()); //game frametime
    window.clear();
    background.draw(window); //draw star background
    player.draw(window);
    window.draw(enemy);
    window.display();
  }
}

void GameEngine::handleEvents()
{
  while (window.pollEvent(event))
  {
     // Request for closing the window                                     
     if(event.type == sf::Event::Closed)
	       window.close();
  }
  player.shipEvent(event); //keyboard  commands
}

Background::Background(){

}

void Background::draw(sf::RenderWindow & window){
  window.draw(*this);
}

void Background::setBackground(string name, sf::Vector2f pos){
  if(!BGI.loadFromFile(name))
    cout << "BG did not load" << endl;
  setTexture(BGI);
}








