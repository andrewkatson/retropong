#include "CompView.hpp"

CompView::CompView(GameLogic *gameLogic, Difficulty difficulty){
  this -> gameLogic = gameLogic;
  this -> difficulty = difficulty;
  this -> ticksSinceLastMove = 0;
}

CompView::~CompView(){
  this -> gameLogic = nullptr;
}

void CompView::updateCompView(int deltaS){
  this -> followBall(deltaS);
}

void CompView::followBall(int deltaS){
  int ballX = this -> gameLogic -> getBallXPos();
  int ballY = this -> gameLogic -> getBallYPos();

  int compX = this -> gameLogic -> getCompXPos();
  int compY = this -> gameLogic -> getCompYPos();

  if(this -> canMove(deltaS)){
    if (ballY > compY){
      this -> gameLogic -> moveCompPaddleDown();
    }
    else if(ballY < compY){
      this -> gameLogic -> moveCompPaddleUp();
    }
  }
}

bool CompView::canMove(int deltaS){
  int maxTicksBeforeMove = this -> calcMaxTicksBeforeMove(deltaS);
  float ballXPosThresholdForMove = this -> calcBallXPosThresholdForMove(deltaS);

  int ballXPos = this -> gameLogic -> getBallXPos();

  if(this -> ticksSinceLastMove > maxTicksBeforeMove && ballXPos >= ballXPosThresholdForMove){
    this -> ticksSinceLastMove = 0;
    return true;
  }

  this -> ticksSinceLastMove++;
  return false;
}

int CompView::calcMaxTicksBeforeMove(int deltaS){
  switch(this -> difficulty){
    case hard:
      return 750;
    case medium:
      return 1000;
    case easy:
    default:
      return 2000;
  }
}
float CompView::calcBallXPosThresholdForMove(int deltaS){
  int windowX  = this -> gameLogic -> getWindowX();

  switch(this -> difficulty){
    case hard:
      return (windowX / 6) * 1.5;
    case medium:
      return (windowX / 6) * 2;
    case easy:
    default:
      return (windowX / 6) * 3;
  }
}
