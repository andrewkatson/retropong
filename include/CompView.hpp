#ifndef COMPVIEW_H
#define COMPVIEW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameLogic.hpp"
#include <memory>

using std::shared_ptr;

class CompView{
private:
  GameLogic *gameLogic;
  int ticks;


public:

  CompView(GameLogic *gameLogic);
  ~CompView();

  void updateCompView(float deltaS);
  void followBall(float deltaS);
  bool canMove(float deltaS);
  float calcBallXPosThresholdForMove(float deltaS);
  int calcMaxTicksBeforeMove(float deltaS);

private:
  Paddle::Difficulty difficulty;
};

#endif
