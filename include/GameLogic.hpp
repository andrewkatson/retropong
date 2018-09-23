#ifndef GAMELOGIC_H
#define GAMELOGIC_H


#include "ScoreBoard.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Border.hpp"
#include "MainMenu.hpp"
#include <SFML/Graphics.hpp>
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
  unique_ptr<Border> topBorder;
  unique_ptr<Border> bottomBorder;
  unique_ptr<Border> leftBorder;
  unique_ptr<Border> rightBorder;
  unique_ptr<MainMenu> mainMenu;
  int windowX;
  int windowY;
  bool isPaused;
  bool isGameOver;
  bool isMainMenu;
  bool isOptionsMenu;


  GameLogic(int windowX, int windowY, int winningScore);

  void init(int windowX, int windowY, int winningScore);
  void startPlaying();
  void startOptionsMenu();
  void restartGame();
  void shutdownGame(sf::RenderWindow  &game);

  void updateWindowSize(int windowX, int windowY);
  void updateLogic(int deltaS);


  void moveUserPaddleDown();
  void moveUserPaddleUp();
  void moveCompPaddleDown();
  void moveCompPaddleUp();
  void moveBall();

  bool isCollision();
  bool ballHitsGoal();
  bool ballHitsUserGoal();
  bool ballHitsCompGoal();
  bool ballHitsNonGoalSides();
  bool ballHitsTopSide();
  bool ballHitsBottomSide();
  bool ballHitsAPaddle();
  bool ballHitsUserPaddle();
  bool ballHitsCompPaddle();
  void handleCollision();
  bool isScore();
  void handleScore();
  void handlePotentialWin(ScoreBoard::Side winner);
  void resetBall();
  void pauseGame();
  void unPauseGame();
  void unpauseBall();
  void moveBallPositionForward();
  bool ballCanMove();
  bool isMainMenuOn();
  bool isOptionsMenuOn();
  bool isGamePaused();
  bool isGameEnded();

  ScoreBoard::Side getWinningSide();

  int getUserScore();
  int getCompScore();

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
  int getBallResetSpeed();

  int getWindowX();
  int getWindowY();

  int getTopBorderXDim();
  int getTopBorderYDim();
  int getTopBorderXPos();
  int getTopBorderYPos();

  int getBottomBorderXDim();
  int getBottomBorderYDim();
  int getBottomBorderXPos();
  int getBottomBorderYPos();

  int getLeftBorderXDim();
  int getLeftBorderYDim();
  int getLeftBorderXPos();
  int getLeftBorderYPos();

  int getRightBorderXDim();
  int getRightBorderYDim();
  int getRightBorderXPos();
  int getRightBorderYPos();

  sf::FloatRect getMainMenuPlayButtonBoundBox();
  int getMainMenuPlayButtonCharSize();

  sf::FloatRect getMainMenuOptionMenuButtonBoundBox();
  int getMainMenuOptionMenuButtonCharSize();

  void setBallXPos(float newXPos);
  void setBallYPos(float newYPos);
  void setBallAngle(int newAngle);
  void setBallSpeed(int newSpeed);

  void setUserPaddleSpeed(int newSpeed);
  void setCompPaddleSpeed(int newSpeed);
};

#endif
