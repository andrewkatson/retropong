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
  int ticksSinceLastMove;


public:

  CompView(GameLogic *gameLogic);
  ~CompView();

  void updateCompView(int deltaS);
  void followBall(int deltaS);
  bool canMove(int deltaS);
  int calcMaxTicksBeforeMove(int deltaS);
  float calcBallXPosThresholdForMove(int deltaS);

private:
  Paddle::Difficulty difficulty;
};

#endif
