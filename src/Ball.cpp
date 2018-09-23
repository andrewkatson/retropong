#include "Ball.hpp"


Ball::Ball(float xPos, float yPos, int angle, int radius, int speed){
  this -> xPos = xPos;
  this -> yPos = yPos;
  this -> angle = angle;
  this -> radius = radius;
  this -> speed = speed;
  this -> resetSpeed = speed;
  this -> ticks = 0;
  this -> maxTicksBeforeMove = speed * 100;

  sf::CircleShape circle;

  circle.setPosition(sf::Vector2f(xPos, yPos));
  circle.setRadius(radius);
  circle.setFillColor(sf::Color::White);

  this -> ballCircle = circle;
}

void Ball::reset(){
  this -> xPos = (float)(this -> windowX / 2);
  this -> yPos = (float)(this -> windowY / 2);
  this -> angle = 180;
  this -> radius =  (this -> windowX)/80;
  this -> speed = (this -> windowY)/160;
}

void Ball::moveForward(){
  float changeInX = this -> calcXPosChange();
  float changeInY = this -> calcYPosChange();
  float xPos = this -> getXPos();
  float yPos = this -> getYPos();

  if(changeInX > this -> windowX || changeInY > this -> windowY){
    return;
  }
  this -> updatePos(xPos + changeInX, yPos + changeInY);
}

float Ball::calcXPosChange(){
  float speed = (float) this -> getSpeed();
  float angle = (float) this -> getAngle();

  return speed * cos((angle * PI)/180);
}

float Ball::calcYPosChange(){
  float speed = (float) this -> getSpeed();
  float angle = (float) this -> getAngle();
  return (speed * sin((angle * PI)/180));
}

void Ball::updatePos(float xPos, float yPos){
  this -> xPos = xPos;
  this -> yPos = yPos;
}

bool Ball::canMove(){
  if(this -> ticks > this -> maxTicksBeforeMove){
    this -> ticks = 0;
    return true;
  }
  else{
    this -> ticks  = this -> ticks + 1;
    return false;
  }
}

float Ball::getXPos(){
  return this -> xPos;
}

float Ball::getYPos(){
  return this -> yPos;
}

int Ball::getAngle(){
  return this -> angle;
}

int Ball::getRadius(){
  return this -> radius;
}

int Ball::getSpeed(){
  return this -> speed;
}
int Ball::getBallResetSpeed(){
  return this -> resetSpeed;
}

void Ball::setXPos(float xPos){
  this -> xPos = xPos;
}
void Ball::setYPos(float yPos){
  this -> yPos = yPos;
}
void Ball::setAngle(int angle){
  this -> angle = angle;
}

void Ball::setSpeed(int speed){
  this -> speed = speed;
}
void Ball::setWindowSize(int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> scaleBall();
}

//scale the ball because of a change in window size
void Ball::scaleBall(){
  this -> radius =  (this -> windowX)/80;
}

sf::FloatRect Ball::getGlobalBounds(){
  this -> ballCircle.setPosition(sf::Vector2f(this -> getXPos(), this -> getYPos()));

  return this -> ballCircle.getGlobalBounds();
}
