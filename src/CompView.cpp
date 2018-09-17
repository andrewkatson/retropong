#include "CompView.hpp"

CompView::CompView(GameLogic *gameLogic, Difficulty difficulty){
  this -> gameLogic = gameLogic;
  this -> difficulty = difficulty;
  this -> ticksSinceLastMove = 0;
}

void CompView::updateCompView(int deltaMs){
  this -> followBall();
}

void CompView::followBall(){
  int ballX = this -> gameLogic -> getBallXPos();
  int ballY = this -> gameLogic -> getBallYPos();

  int compX = this -> gameLogic -> getCompXPos();
  int compY = this -> gameLogic -> getCompYPos();

  if(this -> canMove()){
    if (ballY > compY){
      this -> gameLogic -> moveCompPaddleDown();
    }
    else if(ballY < compY){
      this -> gameLogic -> moveCompPaddleUp();
    }
  }
}

bool CompView::canMove(){
  int maxTicksBeforeMove = this -> calcMaxTicksBeforeMove();

  if(this -> ticksSinceLastMove > maxTicksBeforeMove){
    this -> ticksSinceLastMove = 0;
    return true;
  }

  this -> ticksSinceLastMove++;
  return false;
}

int CompView::calcMaxTicksBeforeMove(){
  switch(this -> difficulty){
    case hard:
      return 3000;
    case medium:
      return 5000;
    case easy:
    default:
      return 8000;
  }
}
