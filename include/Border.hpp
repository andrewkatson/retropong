#ifndef BORDER_H
#define BORDER_H
#include <SFML/Graphics.hpp>
class Border{
private:
  sf::RectangleShape rect;
  int windowX;
  int windowY;
public:
  enum BorderType{
    top, left, right, bottom
  };

  Border(int xPos, int yPos, int xDim, int yDim, BorderType borderType, sf::Color color);

  int getXPos();
  int getYPos();
  int getXDim();
  int getYDim();
  sf::Color getColor();

  void setWindowSize(int windowX, int windowY);
  void setColor(sf::Color color);

  void scaleBorder();
  void scaleTopBorder();
  void scaleLeftBorder();
  void scaleRightBorder();
  void scaleBottomBorder();

  sf::FloatRect getGlobalBounds();

private:
  BorderType type;
};

#endif
