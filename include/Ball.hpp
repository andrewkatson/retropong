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
  float speed;
  int resetSpeed;
  int windowX;
  int windowY;
  sf::CircleShape ballCircle;

public:
  Ball(float xPos, float yPos, int angle, int radius, float speed);

  void reset();
  void moveForward(float deltaS);
  float calcXPosChange(float deltaS);
  float calcYPosChange(float deltaS);
  void updatePos(float xPos, float yPos);

  float getXPos();
  float getYPos();
  int getAngle();
  int getRadius();
  float getSpeed();
  float getBallResetSpeed();
  sf::Color getColor();

  void setXPos(float xPos);
  void setYPos(float yPos);
  void setAngle(int angle);
  void setSpeed(float speed);
  void setWindowSize(int windowX, int windowY);
  void setColor(sf::Color color);

  void scaleBall();

  sf::FloatRect getGlobalBounds();
};

#endif
