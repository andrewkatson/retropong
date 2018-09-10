#include "../include/Paddle.hpp"

Paddle::Paddle(int xPos, int yPos, int xDim, int yDim){
  this -> xPos = xPos;
  this -> yPos = yPos;
  this -> xDim = xDim;
  this -> yDim = yDim;
}

void Paddle::updatePos(int newXPos, int newYPos){
  this -> xPos = newXPos;
  this ->yPos = newYPos;
}

void Paddle::changeSize(int newXDim, int newYDim){
  this -> xDim = newXDim;
  this -> yDim = newYDim;
}

int Paddle::getXPos(){
  return this -> xPos;
}

int Paddle::getYPos(){
  return this -> yPos;
}

int Paddle::getXDim(){
  return this -> xDim;
}

int Paddle::getYDim(){
  return this -> yDim;
}
