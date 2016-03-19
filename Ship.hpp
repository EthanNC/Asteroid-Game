#ifndef SHIP_H
#define SHIP_H
#include "SFML/Graphics.hpp"
#include "Ship.hpp"
#include <iostream>
#include <list>
#include <string>
#include <math.h>

#define DEF_WIDTH 1500
#define DEF_HEIGHT 900

using namespace std;
//Ship class inherites from convexShape class

class Bullet: public sf::CircleShape
{
public:
	Bullet();
	Bullet(int size, sf::Color color);
private:
	sf::CircleShape shape;
	//string cocks;
};


class Ship: public sf::ConvexShape

{
public:
	static const float acceleration_rate;
    static const float max_speed;
    static const float rotation_speed;
	Ship();
	virtual void setLocation(float x, float y) = 0;
	float getXLocation();
	float getYLocation();
	bool isEmpty(list<Bullet> bullets);
	void fire();
	void reload();
	void moveBullets(sf::RenderWindow & window);
	void draw(sf::RenderWindow & window);
	float degToRad(float num);
protected:
	sf::Vector2f velocity; //physic-ish movement system
	sf::Vector2f force;
	sf::Vector2f position;
private:
	sf::Vector2f bDirection; //bullet direction TODO: make this a const
	list<Bullet> bullets;
	list<Bullet> launched;
	int ammoCount; // wait wait
};
				
class PlayerShip: public Ship
{
public:
	PlayerShip();
	PlayerShip(float xValue, float yValue);
	void setLocation(float x, float y);
	void shipEvent(const sf::Event& event);
  	void updateShip(int frametime);
  	void reset();
private:
	int h_move = 0; //move horizontal
	int v_move = 0; //move vertical
};

class EnemyShip: public Ship
{
public:
	EnemyShip();
	EnemyShip(float xValue, float yValue);
	void setLocation(float x, float y);
};

#endif
