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
  enum Difficulty {
    easy, medium, hard
  };

  CompView(GameLogic *gameLogic, Difficulty difficulty);

  void updateCompView(int deltaMs);
  void followBall();
  bool canMove();
  int calcMaxTicksBeforeMove();

private:
  Difficulty difficulty;
};

#endif
