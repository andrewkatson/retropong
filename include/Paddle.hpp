#ifndef PADDLE_H
#define PADDLE_H

class Paddle{
private:
  int xPos;
  int yPos;
  int xDim;
  int yDim;
  int speed;
  int windowX;
  int windowY;

  public:
  enum Direction {
    up, down
  };

  Paddle(int xPos, int yPos, int xDim, int yDim, int speed);

  void movePaddle(Direction direction);

  void updatePos(int newXPos, int newYPos);

  void changeSize(int newXDim, int newYDim);

  void setWindowSize(int windowX, int windowY);

  int getXPos();

  int getYPos();

  int getXDim();

  int getYDim();

  void setSpeed(int speed);

};

#endif
