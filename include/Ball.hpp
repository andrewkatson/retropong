#ifndef BALL_H
#define BALL_H
#include <math.h>

#define PI 3.14159265
class Ball{
private:
  float xPos;
  float yPos;
  int angle;
  int radius;
  int speed;
  int ticks;
  int maxTicksBeforeMove;
  int windowX;
  int windowY;

public:
  Ball(float xPos, float yPos, int angle, int radius, int speed);

  void moveForward();
  float calcXPosChange();
  float calcYPosChange();
  void updatePos(float xPos, float yPos);
  bool canMove();

  float getXPos();
  float getYPos();
  int getAngle();
  int getRadius();
  int getSpeed();

  void setXPos(float xPos);
  void setYPos(float yPos);
  void setAngle(int angle);
  void setSpeed(int speed);
  void setWindowSize(int windowX, int windowY);
};

#endif
