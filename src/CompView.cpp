#include "CompView.hpp"

CompView::CompView(GameLogic *gameLogic){
  this -> gameLogic = gameLogic;
  this -> difficulty = Paddle::easy;

}

CompView::~CompView(){
  this -> gameLogic = nullptr;
}

void CompView::updateCompView(int deltaS){
  this -> followBall(deltaS);
  this -> difficulty = this -> gameLogic -> getDifficulty();
}

void CompView::followBall(int deltaS){
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

bool CompView::canMove(int deltaS){
  float ballXPosThresholdForMove = this -> calcBallXPosThresholdForMove(deltaS);

  int ballXPos = this -> gameLogic -> getBallXPos();

  if(ballXPos >= ballXPosThresholdForMove){
    return true;
  }
  return false;
}

float CompView::calcBallXPosThresholdForMove(int deltaS){
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
