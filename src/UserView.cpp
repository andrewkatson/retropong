#include "UserView.hpp"
#include <iostream>

using std::cout;

UserView::UserView(GameLogic *gameLogic){
  this -> gameLogic = gameLogic;
}

void UserView::updateUserView(int deltaMs, sf::RenderWindow &game){
  game.clear();

  this -> drawUserPaddle(game);
  this -> drawCompPaddle(game);
  this -> drawBall(game);

  game.display();

}

void UserView::drawUserPaddle(sf::RenderWindow &game){
  sf::RectangleShape rectangle;

  int xPos = this -> gameLogic -> getUserXPos();
  int yPos = this -> gameLogic -> getUserYPos();
  int xDim = this -> gameLogic -> getUserXDim();
  int yDim = this -> gameLogic -> getUserYDim();

  rectangle.setFillColor(sf::Color::White);
  rectangle.setSize(sf::Vector2f(xDim,yDim));
  rectangle.setPosition(xPos, yPos);

  game.draw(rectangle);

}

void UserView::drawCompPaddle(sf::RenderWindow &game) {
  sf::RectangleShape rectangle;

  int xPos = this -> gameLogic -> getCompXPos();
  int yPos = this -> gameLogic -> getCompYPos();
  int xDim = this -> gameLogic -> getCompXDim();
  int yDim = this -> gameLogic -> getCompYDim();

  rectangle.setFillColor(sf::Color::White);
  rectangle.setSize(sf::Vector2f(xDim,yDim));
  rectangle.setPosition(xPos, yPos);

  game.draw(rectangle);
}

void UserView::drawBall(sf::RenderWindow &game){
  sf::CircleShape circle;
  sf::Texture texture;
  sf::Sprite sprite;

  float xPos = (float) (this -> gameLogic -> getBallXPos());
  float yPos = (float) (this -> gameLogic -> getBallYPos());
  float angle = (float) (this -> gameLogic -> getBallAngle());
  float radius = (float) (this -> gameLogic -> getBallRadius());

  circle.setPosition(sf::Vector2f(xPos, yPos));
  circle.setRadius(radius);
  circle.setFillColor(sf::Color::White);
  game.draw(circle);

  /*
  //try to load texture from file
  if(!texture.loadFromFile("../image/ppeers1.png")){
    circle.setFillColor(sf::Color::White);
    game.draw(circle);
  }
  else{
      sprite.setTexture(texture);
      sprite.setPosition(sf::Vector2f(xPos, yPos));
      sprite.setRotation(angle);
      sprite.setScale(0.25f, 0.2f);
      game.draw(sprite);
  }
  */
}
