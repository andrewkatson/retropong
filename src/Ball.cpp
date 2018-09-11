#include "../include/Ball.hpp"

Ball::Ball(int xPos, int yPos, int angle){
  this -> xPos = xPos;
  this -> yPos = yPos;
  this -> angle = angle;
}

void Ball::updatePos(int xPos, int yPos){
  this -> xPos = xPos;
  this -> yPos = yPos;
}

int Ball::getXPos(){
  return this -> xPos;
}

int Ball::getYPos(){
  return this -> yPos;
}

int Ball::getAngle(){
  return this -> angle;
}
