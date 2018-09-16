#include "Paddle.hpp"

Paddle::Paddle(int xPos, int yPos, int xDim, int yDim, int speed){
  this -> xPos = xPos;
  this -> yPos = yPos;
  this -> xDim = xDim;
  this -> yDim = yDim;
  this -> speed = speed;
}

void Paddle::movePaddle(Direction direction){

  switch(direction){
    case up:
      this -> updatePos(this -> xPos, this -> yPos - this -> speed);
      break;
    case down:
      this -> updatePos(this -> xPos, this -> yPos + this -> speed);
      break;
    default:
      break;
  };
}

void Paddle::updatePos(int newXPos, int newYPos){
  if(newYPos < 0 || newYPos + this -> yDim > windowY){
    return;
  }

  this -> xPos = newXPos;
  this -> yPos = newYPos;
}

void Paddle::changeSize(int newXDim, int newYDim){
  this -> xDim = newXDim;
  this -> yDim = newYDim;
}

void Paddle::setWindowSize(int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
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

void Paddle::setSpeed(int speed){
  this -> speed = speed;
}
