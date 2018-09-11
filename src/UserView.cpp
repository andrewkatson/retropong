#include "../include/UserView.hpp"
#include <iostream>

using std::cout;

UserView::UserView(Paddle *userPaddle, Paddle *compPaddle){
  this -> userPaddle = userPaddle;
  this -> compPaddle = compPaddle;
}

void UserView::updateUserView(int deltaMs, sf::RenderWindow &game){
  game.clear();

  this -> drawUserPaddle(game);
  this -> drawCompPaddle(game);

  game.display();

}

void UserView::drawUserPaddle(sf::RenderWindow &game){
  sf::RectangleShape rectangle;
  int xPos = this -> userPaddle -> getXPos();
  int yPos = this -> userPaddle -> getYPos();
  int xDim = this -> userPaddle -> getXDim();
  int yDim = this -> userPaddle -> getYDim();

  rectangle.setFillColor(sf::Color::White);
  rectangle.setSize(sf::Vector2f(xDim,yDim));
  rectangle.setPosition(xPos, yPos);

  game.draw(rectangle);

}

void UserView::drawCompPaddle(sf::RenderWindow &game) {

}
