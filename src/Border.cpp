#include "Border.hpp"


Border::Border(int xPos, int yPos, int xDim, int yDim, BorderType borderType, sf::Color color){
  (this -> rect).setPosition(xPos, yPos);
  (this -> rect).setSize(sf::Vector2f(xDim, yDim));
  this -> type = borderType;
  (this -> rect).setFillColor(color);
}

int Border::getXPos(){
  sf::Vector2f pos = (this -> rect).getPosition();
  return  pos.x;
}
int Border::getYPos(){
  sf::Vector2f pos = (this -> rect).getPosition();
  return  pos.y;
}
int Border::getXDim(){
  sf::Vector2f dim = (this -> rect).getSize();
  return  dim.x;
}
int Border::getYDim(){
  sf::Vector2f dim = (this -> rect).getSize();
  return  dim.y;
}
sf::Color Border::getColor(){
  return (this -> rect).getFillColor();
}

void Border::setWindowSize(int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> scaleBorder();
}
void Border::setColor(sf::Color color){
  (this -> rect).setFillColor(color);
}

//scale the border because of a window resize
void Border::scaleBorder(){
  switch(this -> type){
    case Border::top:
      this -> scaleTopBorder();
      break;
    case Border::left:
      this -> scaleLeftBorder();
      break;
    case Border::right:
      this -> scaleRightBorder();
      break;
    case Border::bottom:
      this -> scaleBottomBorder();
      break;
  };
}
//////////////////////////////////////////////////////////////////////////
//only change values for each type of border that are affected by resizing

void Border::scaleTopBorder(){
  int xDim = this -> windowX;
  int yDim = this -> windowY / 60;
  (this -> rect).setSize(sf::Vector2f(xDim, yDim));
}

void Border::scaleLeftBorder(){
  int xPos = this -> getXPos();
  int yPos = this -> windowY/60;
  int xDim = this -> windowX / 160;
  int yDim = this ->  windowY - 2 * (this -> windowY/60);
  (this -> rect).setPosition(xPos, yPos);
  (this -> rect).setSize(sf::Vector2f(xDim, yDim));
}

void Border::scaleRightBorder(){
  int xPos = this -> windowX - (this -> windowX / 160);
  int yPos = this -> windowY / 60;
  int xDim = this -> windowX / 160;
  int yDim = this ->  windowY - 2 * (this -> windowY/60);
  (this -> rect).setPosition(xPos, yPos);
  (this -> rect).setSize(sf::Vector2f(xDim, yDim));
}

void Border::scaleBottomBorder(){
  int xPos = this -> getXPos();
  int yPos = this ->  windowY - (this -> windowY / 60);
  int xDim = this -> windowX;
  int yDim = this -> windowY / 60;
  (this -> rect).setPosition(xPos, yPos);
  (this -> rect).setSize(sf::Vector2f(xDim, yDim));
}
/////////////////////////////////////////////////////////////////////////
sf::FloatRect Border::getGlobalBounds(){
  this -> rect.setSize(sf::Vector2f(this -> getXDim(),this -> getYDim()));
  this -> rect.setPosition(this -> getXPos(), this -> getYPos());

  return this -> rect.getGlobalBounds();
}
