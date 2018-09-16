#ifndef GAMELOGIC_H
#define GAMELOGIC_H


#include "ScoreBoard.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include <memory>
#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout;
using std::abs;
using std::unique_ptr;
using std::make_shared;

class GameLogic{
public:
  unique_ptr<Paddle> userPaddle;
  unique_ptr<Paddle> compPaddle;
  unique_ptr<Ball> ball;
  unique_ptr<ScoreBoard> scoreBoard;
  int windowX;
  int windowY;

  GameLogic(int windowX, int windowY, int winningScore);

  void updateLogic(int deltaMs);
  void updateWindowSize(int windowX, int windowY);

  void moveUserPaddleDown();
  void moveUserPaddleUp();
  void moveCompPaddleDown();
  void moveCompPaddleUp();
  void moveBall();

  bool isCollision();
  bool ballHitsGoal(float ballX, float ballY, int ballRadius);
  bool ballHitsUserGoal(float ballX, float ballY, int ballRadius);
  bool ballHitsCompGoal(float ballX, float ballY, int ballRadius);
  bool ballHitsNonGoalSides(float ballX, float ballY, int ballRadius);
  bool ballHitsAPaddle(float ballX, float ballY, int ballRadius);
  bool ballHitsUserPaddle(float ballX, float ballY, int ballRadius);
  bool ballHitsCompPaddle(float ballX, float ballY, int ballRadius);
  void calcTrueBallDimensions(float ballX, float ballY, int ballRadius,
     float (&dimensionArray)[8]);
  bool withinPaddleX(float trueBallX, int paddleX, int paddleXDim);
  bool withinPaddleY(float trueBallY, int paddleY, int paddleYDim);
  void handleCollision();
  bool isScore();
  void handleScore();
  void handlePotentialWin(ScoreBoard::Side winner);
  void resetBall();
  void moveBallPositionForward();
  bool ballCanMove();

  int getUserXDim();
  int getUserYDim();
  int getUserXPos();
  int getUserYPos();
  int getCompXDim();
  int getCompYDim();
  int getCompXPos();
  int getCompYPos();
  float getBallXPos();
  float getBallYPos();
  int getBallRadius();
  int getBallAngle();
  int getBallSpeed();

  void setBallXPos(float newXPos);
  void setBallYPos(float newYPos);
  void setBallAngle(int newAngle);
  void setBallSpeed(int newSpeed);

  void setUserPaddleSpeed(int newSpeed);

  void setCompPaddleSpeeD(int newSpeed);
};

#endif
