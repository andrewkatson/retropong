#include "UserView.hpp"
#include <iostream>

using std::cout;

UserView::UserView(Paddle *userPaddle, Paddle *compPaddle, Ball *ball){
  this -> userPaddle = userPaddle;
  this -> compPaddle = compPaddle;
  this -> ball = ball;
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
  sf::RectangleShape rectangle;

  int xPos = this -> compPaddle -> getXPos();
  int yPos = this -> compPaddle -> getYPos();
  int xDim = this -> compPaddle -> getXDim();
  int yDim = this -> compPaddle -> getYDim();

  rectangle.setFillColor(sf::Color::White);
  rectangle.setSize(sf::Vector2f(xDim,yDim));
  rectangle.setPosition(xPos, yPos);

  game.draw(rectangle);
}

void UserView::drawBall(sf::RenderWindow &game){
  sf::CircleShape circle;
  sf::Texture texture;
  sf::Sprite sprite;

  float xPos = (float) (this -> ball -> getXPos());
  float yPos = (float) (this -> ball -> getYPos());
  float angle = (float) (this -> ball -> getAngle());
  float radius = (float) (this -> ball -> getRadius());

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
