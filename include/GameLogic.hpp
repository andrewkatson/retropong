#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Paddle.hpp"

class GameLogic{
private:
  Paddle *userPaddle;
  Paddle *compPaddle;
public:
  GameLogic();

  void updateLogic(int deltaMs);

  int getUserXDim();
  int getUserYDim();
  int getUserXPos();
  int getUserYPos();
};

#endif
