#ifndef BALL_H
#define BALL_H

class Ball{
private:
  int angle;
  int xPos;
  int yPos;

public:
  Ball(int xPos, int yPos, int angle);

  void updatePos(int xPos, int yPos);

  int getXPos();
  int getYPos();
  int getAngle();
};

#endif
