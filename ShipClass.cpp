#include "Ship.hpp"

using namespace std;

const float Ship::acceleration_rate = .5f;
const float Ship::max_speed = 2.0f;
const float Ship::rotation_speed = 0.3f;

Ship::Ship(){
  //empty constructor- not used
ammoCount = 10;
}

//uses setPosition from ConvexShape class
void Ship::setLocation(float x, float y){
  setPosition(sf::Vector2f(x,y));
  ammoCount = 10;
}

//returns x cordinate
float Ship::getXLocation(){
  sf::Vector2f x;
  x = getPosition();
  return x.x;
}

//returns y cordinate
float Ship::getYLocation(){
	sf::Vector2f y;
	y = getPosition();
	return y.y;
}
PlayerShip::PlayerShip(){
  float x = 0;
  float y = 0;

  setPointCount(8);

  setPoint(0, (sf::Vector2f(x + 20, y)));
  setPoint(1, (sf::Vector2f(x, y - 10)));
  setPoint(2, (sf::Vector2f(x - 20, y - 12)));
  setPoint(3, (sf::Vector2f(x - 10, y - 5)));
  setPoint(4, (sf::Vector2f(x - 10, y + 5)));
  setPoint(5, (sf::Vector2f(x - 20, y + 12)));
  setPoint(6, (sf::Vector2f(x, y + 10)));
  setPoint(7, (sf::Vector2f(x + 20, y)));
  setFillColor(sf::Color::Blue);

  v_move = 0;
  h_move = 0;

  reset();

}

PlayerShip::PlayerShip(float xValue, float yValue){
  //Init CovexShape

  setPointCount(3);
  setPoint(0, sf::Vector2f(xValue, yValue));
  setPoint(1, sf::Vector2f(xValue, yValue+10));
  setPoint(2, sf::Vector2f(xValue+25, yValue+5));
  setFillColor(sf::Color::Red);

}

void PlayerShip::setLocation(float x, float y){
   setPosition(sf::Vector2f(x,y));
}

EnemyShip::EnemyShip(){
  setPointCount(3);
  setPoint(0, sf::Vector2f(0, 0));
  setPoint(1, sf::Vector2f(0, 10));
  setPoint(2, sf::Vector2f(25, 5));
  setFillColor(sf::Color::Red);


}
EnemyShip::EnemyShip(float xValue, float yValue){
  //Init CovexShape 
  setPointCount(3);
  setPoint(0, sf::Vector2f(xValue, yValue));
  setPoint(1, sf::Vector2f(xValue, yValue+10));
  setPoint(2, sf::Vector2f(xValue+25, yValue+5));
  setFillColor(sf::Color::Blue);
}

void EnemyShip::setLocation(float x, float y){
   setPosition(sf::Vector2f(x,y));
}

Bullet::Bullet(){
  setRadius(5);
  setOutlineColor(sf::Color::Red);
  setOutlineThickness(1);
}

Bullet::Bullet(int size, sf::Color color){
  setRadius(size);
  setOutlineColor(color);
  setOutlineThickness(5);
}

bool Ship::isEmpty(list<Bullet> bullets){
  if(bullets.empty())
    return true;
  else
    return false;
}

void Ship::fire(){
  float x = this->getXLocation();
  float y = this->getYLocation();

  list<Bullet>::iterator iter;
  if(!isEmpty(bullets))
  {
    launched.push_front(bullets.front()); //bullet in
    bullets.pop_front();
    iter = launched.begin();
    iter-> setPosition(sf::Vector2f(x,y));
    //iter++;

  }
  else
  {
    reload();
  }
}

void Ship::moveBullets(sf::RenderWindow & window){
  list<Bullet>::iterator iter;
  bDirection.x = cos(degToRad(getRotation()));
  bDirection.y = sin(degToRad(getRotation()));
  if(!isEmpty(launched)){
    for(iter = launched.begin(); iter != launched.end(); iter++)
    {
      iter->move(bDirection);
      window.draw(*iter);
    }
    bDirection.x = 0;
    bDirection.y = 0;
  }

}
void Ship::draw(sf::RenderWindow & window){
  window.draw(*this);
  moveBullets(window);

}

void Ship::reload()
{
  Bullet bulletObj;
  for(int i = 0; bullets.size() != ammoCount; i++)
  {
    bullets.push_back(bulletObj);
  }
}


void PlayerShip::shipEvent(const sf::Event& event){
  h_move = 0;
  v_move = 0;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    v_move = 1;

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    h_move = 1;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
    velocity.x = 0; //throttle
    velocity.y = 0;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    h_move = -1; 
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    fire();
}

void PlayerShip::updateShip(int frametime){
  float angle;
  angle = getRotation();
  if(h_move != 0){
    rotate(h_move *rotation_speed*frametime);
  
  }

  if(v_move != 0){
    force.x = cos(degToRad(angle)); //direction x
    force.y = sin(degToRad(angle)); //direction y

    force.x *= v_move * acceleration_rate * frametime;
    force.y *= v_move * acceleration_rate * frametime;

    velocity += force;
    //Pythag to stop player from moving to fast
    //totalVelocity is highest momentum the ship can reach
    double totalVelocity = sqrt((velocity.x * velocity.x)+(velocity.y * velocity.y));
    if(totalVelocity > max_speed){  
      velocity.x *= max_speed / totalVelocity;
      velocity.y *= max_speed / totalVelocity;
    }
  }
  position = getPosition();
  position += velocity;  // 
  this -> move(velocity);
  // player ship boundry
  if(position.y > 900)
  {
    setPosition(position.x, 0);
  }
  if(position.y < 0)
  {
    setPosition(position.x, 900);
  }
  if(position.x > 1500)
  {
    setPosition(0, position.y);
  }
  if(position.x < 0)
  {
    setPosition(1500, position.y);
  }
  

}

void PlayerShip::reset() {
    setPosition(DEF_WIDTH / 2, DEF_HEIGHT / 2);
    setRotation(0.0f);
    velocity.x = 0.0f;
    velocity.y = 0.0f;
}

float Ship::degToRad(float num){
  num = num * (M_PI/180.0);
  return num;
}



