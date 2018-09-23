#ifndef PADDLE_H
#define PADDLE_H
#include <SFML/Graphics.hpp>
class Paddle{
private:
  int xPos;
  int yPos;
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

  Paddle(int xPos, int yPos, int xDim, int yDim, int speed);

  void reset(int compOrUser);

  void movePaddle(Direction direction);

  void updatePos(int newXPos, int newYPos);

  void changeSize(int newXDim, int newYDim);

  void setWindowSize(int windowX, int windowY);

  void scalePaddle();

  int getXPos();

  int getYPos();

  int getXDim();

  int getYDim();

  void setSpeed(int speed);

  sf::FloatRect getGlobalBounds();
};

#endif
