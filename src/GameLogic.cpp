#include "../include/GameLogic.hpp"

GameLogic::GameLogic(){
  this -> userPaddle = new Paddle(0,0,50,100);
  this -> compPaddle = new Paddle(0,100,50,100);
}

void GameLogic::updateLogic(int deltaMs){

}

int GameLogic::getUserXDim(){
  return this -> userPaddle -> getXDim();
}

int GameLogic::getUserYDim(){
  return this -> userPaddle -> getYDim();
}

int GameLogic::getUserXPos(){
  return this -> userPaddle -> getXPos();
}

int GameLogic::getUserYPos(){
  return this -> userPaddle -> getYPos();
}
