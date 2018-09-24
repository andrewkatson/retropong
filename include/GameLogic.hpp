#ifndef GAMELOGIC_H
#define GAMELOGIC_H


#include "ScoreBoard.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Border.hpp"
#include "MainMenu.hpp"
#include "OptionMenu.hpp"
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
  unique_ptr<OptionMenu> optionMenu;

  int windowX;
  int windowY;
  bool isPaused;
  bool isGameOver;
  bool isMainMenu;
  bool isOptionsMenu;
  bool enteredKonamiCode;


  GameLogic(int windowX, int windowY, int winningScore);

  void init(int windowX, int windowY, int winningScore);
  void startPlaying();
  void startOptionsMenu();
  void restartGame();
  void switchToMainMenu();
  void shutdownGame(sf::RenderWindow  &game);

  void updateWindowSize(int windowX, int windowY);
  void updateLogic(float deltaS);

  void handleClickedDropDown(vector<int> clickDropDown);

  void handleClickedGameObjectSelect(int objectSelectedIndex);
  void handleClickedColorSelect(int objectSelectedIndex);
  void handleClickedDifficultySelect(int objectSelectedIndex);

  void switchColor(string chosenColor);
  sf::Color getCurrentlySelectedColor();
  Paddle::Difficulty getCurrentlySelectedDifficulty();
  int getColorIndexOfCurrentlySelectedObject();
  sf::Color getColorOfObject(string objectName);

  void moveUserPaddleDown(float deltaS);
  void moveUserPaddleUp(float deltaS);
  void moveCompPaddleDown(float deltaS);
  void moveCompPaddleUp(float deltaS);
  void moveBall(float deltaS);

  bool ballWithinBounds();
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
  void enableKonamiCode();
  void disableKonamiCode();
  void moveBallPositionForward(float deltaS);

  bool isMainMenuOn();
  bool isOptionsMenuOn();
  bool isGamePaused();
  bool isGameEnded();
  bool isKonamiCode();

  ScoreBoard::Side getWinningSide();

  int getUserScore();
  int getCompScore();

  int getUserXDim();
  int getUserYDim();
  float getUserXPos();
  float getUserYPos();
  sf::Color getUserPaddleColor();

  int getCompXDim();
  int getCompYDim();
  float getCompXPos();
  float getCompYPos();
  sf::Color getCompPaddleColor();

  float getBallXPos();
  float getBallYPos();
  int getBallRadius();
  int getBallAngle();
  int getBallSpeed();
  int getBallResetSpeed();
  sf::Color getBallColor();

  int getWindowX();
  int getWindowY();

  int getTopBorderXDim();
  int getTopBorderYDim();
  int getTopBorderXPos();
  int getTopBorderYPos();
  sf::Color getTopBorderColor();

  int getBottomBorderXDim();
  int getBottomBorderYDim();
  int getBottomBorderXPos();
  int getBottomBorderYPos();
  sf::Color getBottomBorderColor();

  int getLeftBorderXDim();
  int getLeftBorderYDim();
  int getLeftBorderXPos();
  int getLeftBorderYPos();
  sf::Color getLeftBorderColor();

  int getRightBorderXDim();
  int getRightBorderYDim();
  int getRightBorderXPos();
  int getRightBorderYPos();
  sf::Color getRightBorderColor();

  sf::FloatRect getMainMenuPlayButtonBoundBox();
  int getMainMenuPlayButtonCharSize();

  sf::FloatRect getMainMenuOptionMenuButtonBoundBox();
  int getMainMenuOptionMenuButtonCharSize();

  sf::FloatRect getMainMenuQuitButtonBoundBox();
  int getMainMenuQuitButtonCharSize();

  DropDown * getOptionMenuObjectSelect();

  DropDown * getOptionMenuColorSelect();

  DropDown * getOptionMenuDifficultySelect();

  Button * getOptionMenuBackButton();

  int getGameObjectSelected();

  int getGameDifficultySelected();

  Paddle::Difficulty getDifficulty();

  void setTopBorderColor(sf::Color &color);

  void setBottomBorderColor(sf::Color &color);

  void setLeftBorderColor(sf::Color &color);

  void setRightBorderColor(sf::Color &color);

  void setBallXPos(float newXPos);
  void setBallYPos(float newYPos);
  void setBallAngle(int newAngle);
  void setBallSpeed(int newSpeed);
  void setBallColor(sf::Color &color);

  void setUserPaddleSpeed(int newSpeed);
  void setUserPaddleColor(sf::Color &color);

  void setCompPaddleSpeed(int newSpeed);
  void setCompPaddleColor(sf::Color &color);
};

#endif
