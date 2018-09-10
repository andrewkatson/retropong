#include "../include/UserView.hpp"
#include <SFML/Graphics.hpp>


UserView::UserView(sf::RenderWindow &game){
  this -> game = &game;

}

void UserView::updateUserView(int deltaMs){
  drawUserPaddle();


}

void UserView::drawUserPaddle(){
  sf::RectangleShape rectangle;

  int xDim = this -> gameLogic -> getUserXDim();
  int yDim = this -> gameLogic -> getUserYDim();
  int xPos = this -> gameLogic -> getUserXPos();
  int yPos = this -> gameLogic -> getUserYPos();

  rectangle.setFillColor(sf::Color::White);
  rectangle.setSize(sf::Vector2f(xDim,yDim));
  rectangle.setPosition(xPos, yPos);

  this -> game -> draw(rectangle);
}
