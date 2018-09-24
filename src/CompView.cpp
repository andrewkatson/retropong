#include "CompView.hpp"

CompView::CompView(GameLogic *gameLogic){
  this -> gameLogic = gameLogic;
  this -> difficulty = Paddle::easy;
  this -> ticks = 0;
}

CompView::~CompView(){
  this -> gameLogic = nullptr;
}

void CompView::updateCompView(float deltaS){
  this -> followBall(deltaS);
  this -> difficulty = this -> gameLogic -> getDifficulty();
}

void CompView::followBall(float deltaS){
  int ballX = this -> gameLogic -> getBallXPos();
  int ballY = this -> gameLogic -> getBallYPos();

  int compX = this -> gameLogic -> getCompXPos();
  int compY = this -> gameLogic -> getCompYPos();

  if(this -> canMove(deltaS)){
    if (ballY > compY){
      this -> gameLogic -> moveCompPaddleDown(deltaS);
    }
    else if(ballY < compY){
      this -> gameLogic -> moveCompPaddleUp(deltaS);
    }
  }
}

bool CompView::canMove(float deltaS){
  float ballXPosThresholdForMove = this -> calcBallXPosThresholdForMove(deltaS);
  int ticksBeforeMove = this -> calcMaxTicksBeforeMove(deltaS);
  int ballXPos = this -> gameLogic -> getBallXPos();

  if(ballXPos >= ballXPosThresholdForMove && this -> ticks >= ticksBeforeMove){
    this -> ticks = 0;
    return true;
  }
  this -> ticks++;
  return false;
}

float CompView::calcBallXPosThresholdForMove(float deltaS){
  int windowX  = this -> gameLogic -> getWindowX();

  switch(this -> difficulty){
    case Paddle::hard:
      return (windowX / 6) * 1.5;
    case Paddle::medium:
      return (windowX / 6) * 2;
    case Paddle::easy:
    default:
      return (windowX / 6) * 3;
  }
}
int CompView::calcMaxTicksBeforeMove(float deltaS){
  int windowX  = this -> gameLogic -> getWindowX();

  switch(this -> difficulty){
    case Paddle::hard:
      return 300 * deltaS;
    case Paddle::medium:
      return 500 * deltaS;
    case Paddle::easy:
    default:
      return 2000 * deltaS;
  }
}
