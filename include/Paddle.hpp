#ifndef PADDLE_H
#define PADDLE_H

class Paddle{
private:
  int xPos;
  int yPos;
  int xDim;
  int yDim;

  public:
  Paddle(int xPos, int yPos, int xDim, int yDim);

  void updatePos(int newXPos, int newYPos);

  void changeSize(int newXDim, int newYDim);

  int getXPos();

  int getYPos();

  int getXDim();

  int getYDim();

};

#endif
