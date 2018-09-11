#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Paddle.hpp"
#include <memory>

using std::unique_ptr;
using std::make_shared;

class GameLogic{
public:
  unique_ptr<Paddle> userPaddle;
  unique_ptr<Paddle> compPaddle;
  int windowX;
  int windowY;

  GameLogic(int windowX, int windowY);

  void updateLogic(int deltaMs);
  void updateWindowSize(int windowX, int windowY);
  void moveUserPaddleDown();
  void moveUserPaddleUp();

  int getUserXDim();
  int getUserYDim();
  int getUserXPos();
  int getUserYPos();
};

#endif
