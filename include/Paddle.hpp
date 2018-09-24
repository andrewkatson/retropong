#ifndef PADDLE_H
#define PADDLE_H
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
class Paddle{
private:
  float xPos;
  float yPos;
  int xDim;
  int yDim;
  int speed;
  int windowX;
  int windowY;
  sf::RectangleShape paddleRect;

  public:
  enum Direction {
    up, down
  };
  enum Difficulty {
    easy, medium, hard
  };

  Paddle(float xPos, float yPos, int xDim, int yDim, int speed);

  void reset(int compOrUser);

  void movePaddle(Direction direction, float deltaS);

  void updatePos(float newXPos, float newYPos);

  void changeSize(int newXDim, int newYDim);

  void setWindowSize(int windowX, int windowY);

  void setSpeed(int speed);

  void setColor(sf::Color color);

  void setDifficulty(Difficulty difficulty);

  void scalePaddle();

  float getXPos();

  float getYPos();

  int getXDim();

  int getYDim();

  Difficulty getDifficulty();

  sf::Color getColor();

  sf::FloatRect getGlobalBounds();

private:
    Difficulty difficulty;
};

#endif
