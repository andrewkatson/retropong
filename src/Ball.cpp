#include "Ball.hpp"


Ball::Ball(float xPos, float yPos, int angle, int radius, float speed){
  this -> xPos = xPos;
  this -> yPos = yPos;
  this -> angle = angle;
  this -> radius = radius;
  this -> speed = speed;
  this -> resetSpeed = speed;
  this -> ticks = 0;
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
  this -> speed = 10;
}

void Ball::moveForward(float deltaS){
  float changeInX = this -> calcXPosChange(deltaS);
  float changeInY = this -> calcYPosChange(deltaS);
  float xPos = this -> getXPos();
  float yPos = this -> getYPos();

  if(changeInX > this -> windowX || changeInY > this -> windowY){
    return;
  }
  if(!(this -> ballCanMove(deltaS))){
    return;
  }
  //cout << "Ball move " << std::endl;
  //cout << "speed " << this -> speed << std::endl;
  //cout << "x change " << changeInX << std::endl;
  //cout << "y change " << changeInY << std::endl;
  this -> updatePos(xPos + changeInX, yPos + changeInY);
}

float Ball::calcXPosChange(float deltaS){
  float speed =  this -> getSpeed();
  float angle = (float) this -> getAngle();

  return deltaS * (speed * cos((angle * PI)/180.0));
}

float Ball::calcYPosChange(float deltaS){
  float speed = (float) this -> getSpeed();
  float angle = (float) this -> getAngle();

  return deltaS *(speed * sin((angle * PI)/180.0));
}

void Ball::updatePos(float xPos, float yPos){
  this -> xPos = xPos;
  this -> yPos = yPos;
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

float Ball::getSpeed(){
  return this -> speed;
}
float Ball::getBallResetSpeed(){
  return this -> resetSpeed;
}
sf::Color Ball::getColor(){
  return (this -> ballCircle).getFillColor();
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

void Ball::setSpeed(float speed){
  this -> speed = speed;
}
void Ball::setWindowSize(int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> scaleBall();
}
void Ball::setColor(sf::Color color){
  (this -> ballCircle).setFillColor(color);
}

//scale the ball because of a change in window size
void Ball::scaleBall(){
  this -> radius =  (this -> windowX)/80;
}

bool Ball::ballCanMove(float deltaS){
  if(this -> ticks > this -> calcMaxTicksBeforeMove(deltaS)){
    this -> ticks = 0;
    return true;
  }
  this -> ticks++;
  return false;
}

//calculate the maximum ticks before the ball can move
float Ball::calcMaxTicksBeforeMove(float deltaS){
  return 200 * deltaS;
}

sf::FloatRect Ball::getGlobalBounds(){
  this -> ballCircle.setPosition(sf::Vector2f(this -> getXPos(), this -> getYPos()));

  return this -> ballCircle.getGlobalBounds();
}
