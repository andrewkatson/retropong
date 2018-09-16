#include "Ball.hpp"
#include <iostream>
using std::cout;
using std::cos;
using std::sin;

Ball::Ball(float xPos, float yPos, int angle, int radius, int speed){
  this -> xPos = xPos;
  this -> yPos = yPos;
  this -> angle = angle;
  this -> radius = radius;
  this -> speed = speed;
  this -> ticks = 0;
  this -> maxTicksBeforeMove = speed * 100;
}

void Ball::moveForward(){
  float changeInX = this -> calcXPosChange();
  float changeInY = this -> calcYPosChange();
  float xPos = this -> getXPos();
  float yPos = this -> getYPos();

  //cout << "new x "  << xPos + changeInX << std::endl;
  //cout << "new y " << yPos + changeInY << std::endl;
  //cout << "change in x " << changeInX << std::endl;
  //cout << "change in y " << changeInY << std::endl;
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
}
