#include "Paddle.hpp"

Paddle::Paddle(float xPos, float yPos, int xDim, int yDim, int speed){
  this -> xPos = xPos;
  this -> yPos = yPos;
  this -> xDim = xDim;
  this -> yDim = yDim;
  this -> speed = speed;

  sf::RectangleShape rectangle;

  rectangle.setFillColor(sf::Color::White);
  rectangle.setSize(sf::Vector2f(xDim,yDim));
  rectangle.setPosition(xPos, yPos);

  //rectangle shape used to calculate collision bounds
  this -> paddleRect = rectangle;
}

//reset the paddle to its starting values
void Paddle::reset(int compOrUser){
  int user = 0;
  int comp = 1;

  //different reset values if this is a computer paddle or player paddle
  if (compOrUser == user){
    this -> xPos = (this -> windowX)/160 + 50;
    this -> yPos = (this -> windowY)/60 + 50;
    this -> xDim = (this -> windowX)/160;
    this -> yDim = (this -> windowX)/20;
    this -> speed = 10;
  }
  else{
    this -> xPos = (this -> windowX) - (this -> windowX)/160 - 50;
    this -> yPos = (this -> windowY)/60 + 50;
    this -> xDim = (this -> windowX)/160;
    this -> yDim = (this -> windowX)/20;
    this -> speed = 10;
  }
}

void Paddle::movePaddle(Direction direction, float deltaS){

  switch(direction){
    case up:
      this -> updatePos(this -> xPos, this -> yPos - (this -> speed * deltaS));
      break;
    case down:
      this -> updatePos(this -> xPos, this -> yPos + (this -> speed * deltaS));
      break;
    default:
      break;
  };
}

void Paddle::updatePos(float newXPos, float newYPos){
  //if the new position of the paddle would be off the screen you stop it
  //off screen here is considered as the edges of the border rectangles
  if(newYPos < windowY / 60 || newYPos + this -> yDim > windowY - windowY / 60){
    return;
  }

  this -> xPos = newXPos;
  this -> yPos = newYPos;
}
//change the size of the paddle
void Paddle::changeSize(int newXDim, int newYDim){
  this -> xDim = newXDim;
  this -> yDim = newYDim;
}
//change the stored size of the window
void Paddle::setWindowSize(int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> scalePaddle();
}

void Paddle::setSpeed(int speed){
  this -> speed = speed;
}

void Paddle::setColor(sf::Color color){
  (this -> paddleRect).setFillColor(color);
}

void Paddle::setDifficulty(Difficulty difficulty){
  this -> difficulty = difficulty;
}

//scale the paddle becasue of a window size changeSize
void Paddle::scalePaddle(){
  this -> xDim = (this -> windowX)/160;
  this -> yDim = (this -> windowX)/20;
}

float Paddle::getXPos(){
  return this -> xPos;
}

float Paddle::getYPos(){
  return this -> yPos;
}

int Paddle::getXDim(){
  return this -> xDim;
}

int Paddle::getYDim(){
  return this -> yDim;
}

Paddle::Difficulty Paddle::getDifficulty(){
  return this -> difficulty;
}

sf::Color Paddle::getColor(){
  return (this -> paddleRect).getFillColor();
}
sf::FloatRect Paddle::getGlobalBounds(){
  this -> paddleRect.setSize(sf::Vector2f(this -> getXDim(),this -> getYDim()));
  this -> paddleRect.setPosition(this -> getXPos(), this -> getYPos());

  return this -> paddleRect.getGlobalBounds();
}
