#include "../include/GameLogic.hpp"

GameLogic::GameLogic(int windowX, int windowY){
  this -> userPaddle = unique_ptr<Paddle>(new Paddle(50,50,5,40,10));
  this -> compPaddle = unique_ptr<Paddle>(new Paddle(50,50,5,40,10));

  this -> updateWindowSize(windowX, windowY);
}

void GameLogic::updateLogic(int deltaMs){

}

void GameLogic::updateWindowSize(int windowX, int windowY){
  this -> userPaddle -> setWindowSize(windowX, windowY);
  this -> compPaddle -> setWindowSize(windowX, windowY);
}

void GameLogic::moveUserPaddleDown(){
  this -> userPaddle -> movePaddle(Paddle::down);

}
void GameLogic::moveUserPaddleUp(){
  this -> userPaddle -> movePaddle(Paddle::up);
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
