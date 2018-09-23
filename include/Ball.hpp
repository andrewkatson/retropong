#ifndef BALL_H
#define BALL_H
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

#define PI 3.14159265
using std::cout;
using std::cos;
using std::sin;

class Ball{
private:
  float xPos;
  float yPos;
  int angle;
  int radius;
  int speed;
  int resetSpeed;
  int ticks;
  int maxTicksBeforeMove;
  int windowX;
  int windowY;
  sf::CircleShape ballCircle;

public:
  Ball(float xPos, float yPos, int angle, int radius, int speed);

  void reset();
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
  int getBallResetSpeed();

  void setXPos(float xPos);
  void setYPos(float yPos);
  void setAngle(int angle);
  void setSpeed(int speed);
  void setWindowSize(int windowX, int windowY);

  void scaleBall();

  sf::FloatRect getGlobalBounds();
};

#endif
