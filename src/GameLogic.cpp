#include "GameLogic.hpp"



GameLogic::GameLogic(int windowX, int windowY, int winningScore){
  this -> userPaddle = unique_ptr<Paddle>(new Paddle(50,50,5,40,10));
  this -> compPaddle = unique_ptr<Paddle>(new Paddle(windowX - 50,50,5,40,10));
  this -> ball = unique_ptr<Ball>(new Ball((float)(windowX / 2), (float)(windowY / 2),
                                  180, 10, 5));
  this -> scoreBoard =  unique_ptr<ScoreBoard>(new ScoreBoard(winningScore));
  this -> updateWindowSize(windowX, windowY);

  srand(time(0));
}

void GameLogic::updateLogic(int deltaMs){
  this -> moveBall();
}

void GameLogic::updateWindowSize(int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> userPaddle -> setWindowSize(windowX, windowY);
  this -> compPaddle -> setWindowSize(windowX, windowY);
  this -> ball -> setWindowSize(windowX, windowY);
}

//Move user paddle
void GameLogic::moveUserPaddleDown(){
  this -> userPaddle -> movePaddle(Paddle::down);
}
void GameLogic::moveUserPaddleUp(){
  this -> userPaddle -> movePaddle(Paddle::up);
}

//Move the computer paddle
void GameLogic::moveCompPaddleDown(){
  this -> compPaddle -> movePaddle(Paddle::down);
}
void GameLogic::moveCompPaddleUp(){
  this -> compPaddle -> movePaddle(Paddle::up);
}

//Move the game ball and determine if there is a collision or a score if it cannot
void GameLogic::moveBall(){


  if(this -> isCollision()){
    this -> handleCollision();

    //keep moving ball away until there is no collision
    while(this -> isCollision()){
      if(this -> ballCanMove()){
        this -> moveBallPositionForward();
      }
    }
  }
  else if(this -> isScore()){
    this -> handleScore();
  }
  else{
    if(this -> ballCanMove()){
      this -> moveBallPositionForward();
    }
  }
}

bool GameLogic::isCollision(){
  float ballX = this ->  getBallXPos();
  float ballY = this -> getBallYPos();
  int ballRadius = this -> getBallRadius();

  //corner hit is a score so do not count as normal collision
  if(this -> ballHitsGoal(ballX, ballY, ballRadius)){
    return false;
  }
  else if(this -> ballHitsNonGoalSides(ballX, ballY, ballRadius)){
    return true;
  }
  else if(this -> ballHitsAPaddle()){
    return true;
  }
  return false;
}

bool GameLogic::ballHitsGoal(float ballX, float ballY, int ballRadius){

  if(this -> ballHitsUserGoal(ballX, ballY, ballRadius)){
    return true;
  }
  else if(this -> ballHitsCompGoal(ballX, ballY, ballRadius)){
    return true;
  }
  return false;
}

bool GameLogic::ballHitsUserGoal(float ballX, float ballY, int ballRadius){
  //the true xs consider the effect of the radius
  float trueBallXLeft = ballX - ballRadius;
  float trueBallXTop = ballX;
  float trueBallXRight = ballX + ballRadius;
  float trueBallXBottom = ballX;

  if(trueBallXTop <= 0.0 || trueBallXLeft <= 0.0 || trueBallXRight <= 0.0 ||
    trueBallXBottom <= 0.0) {
    return true;
  }

  return false;
}

bool GameLogic::ballHitsCompGoal(float ballX, float ballY, int ballRadius){
  //the true xs consider the effect of the radius
  float trueBallXLeft = ballX - (float)ballRadius;
  float trueBallXTop = ballX;
  float trueBallXRight = ballX + (float)ballRadius;
  float trueBallXBottom = ballX;

  float windowX = (float)this -> windowX;

  if(trueBallXTop >= windowX || trueBallXLeft >= windowX ||
    trueBallXRight >= windowX || trueBallXBottom >= windowX){
      return true;
    }

  return false;
}

bool GameLogic::ballHitsNonGoalSides(float ballX, float ballY, int ballRadius){
  //the true  ys consider the effect of the radius
  float trueBallYLeft = ballY;
  float trueBallYTop = ballY - (float)ballRadius;
  float trueBallYRight = ballY;
  float trueBallYBottom = ballY + (float)ballRadius;

  float windowY = (float)this -> windowY;

  //hits the top side
  if(trueBallYTop <= 0.0 || trueBallYLeft <= 0.0 || trueBallYRight <= 0.0 ||
  trueBallYBottom <= 0.0) {
    return true;
  }
  else if(trueBallYTop >= windowY || trueBallYLeft >= windowY
    || trueBallYRight >= windowY  || trueBallYBottom >= windowY){
    return true;
  }
  return false;
}

bool GameLogic::ballHitsAPaddle(){

  if(this -> ballHitsUserPaddle()){
    return true;
  }
  else if(this -> ballHitsCompPaddle()){
    return true;
  }
  return false;
}

bool GameLogic::ballHitsUserPaddle(){
  sf::FloatRect userPaddleBox = (this -> userPaddle) -> getGlobalBounds();
  sf::FloatRect ballBox = (this -> ball) -> getGlobalBounds();

  if(userPaddleBox.intersects(ballBox)){
    return true;
  }
  return false;
}

bool GameLogic::ballHitsCompPaddle(){
  sf::FloatRect compPaddleBox = (this -> compPaddle) -> getGlobalBounds();
  sf::FloatRect ballBox = (this -> ball) -> getGlobalBounds();

  if(compPaddleBox.intersects(ballBox)){
    return true;
  }
  return false;
}


void GameLogic::handleCollision(){
  // +/- 10 angle
  int randomAngleVariation = (rand() % 21) - 10;

  int ballAngle = this -> getBallAngle();
  float ballX = this -> getBallXPos();
  float ballY = this -> getBallYPos();
  int ballRadius = this -> getBallRadius();

  int newAngle = 0;
  //if the collision occured on the top or bottom the angle needs to be negated
  if(this -> ballHitsNonGoalSides(ballX, ballY, ballRadius)){
    newAngle = (-1) * (180 - ballAngle) + randomAngleVariation;
  }
  else{
    newAngle = (180 - ballAngle) + randomAngleVariation;
  }

  this -> setBallAngle(newAngle);

}

bool GameLogic::isScore(){
  float ballX = this -> getBallXPos();
  float ballY = this -> getBallYPos();
  int ballRadius = this -> getBallRadius();

  if(this -> ballHitsGoal(ballX, ballY, ballRadius)){
    return true;
  }
  return false;
}

void GameLogic::handleScore(){
  float ballX = this -> getBallXPos();
  float ballY = this -> getBallYPos();
  int ballRadius = this -> getBallRadius();
  if(this -> ballHitsUserGoal(ballX, ballY,ballRadius)){
    this -> scoreBoard -> incrementUserScore();
  }
  else{
    this -> scoreBoard -> incrementCompScore();
  }

  ScoreBoard::Side winner = this -> scoreBoard -> hasWon();

  this -> handlePotentialWin(winner);

  this -> resetBall();
}

void GameLogic::handlePotentialWin(ScoreBoard::Side winner){
  if(winner != ScoreBoard::neither){
    this -> setBallSpeed(0);
    this -> setUserPaddleSpeed(0);
    this -> setCompPaddleSpeeD(0);
  }
}

void GameLogic::resetBall(){
  float halfWindowX = (float) (this -> windowX)/2;
  float halfWindowY = (float) (this -> windowY)/2;

  this -> setBallXPos(halfWindowX);
  this -> setBallYPos(halfWindowY);

  this -> setBallSpeed(0);

}

void GameLogic::unpauseBall(){
  if(this -> getBallSpeed() != this -> getBallResetSpeed()){
    this -> setBallSpeed(this -> getBallResetSpeed());
  }
}

void GameLogic::moveBallPositionForward(){
  this -> ball -> moveForward();
}

bool GameLogic::ballCanMove(){
  this -> ball -> canMove();
}

int GameLogic::getUserScore(){
  return this -> scoreBoard -> getUserScore();
}
int GameLogic::getCompScore(){
  return this -> scoreBoard -> getCompScore();
}

//Grab data on user paddle
int GameLogic::getUserXDim(){
  return this -> userPaddle -> getXDim();
}

int GameLogic::getUserYDim(){
  return this -> userPaddle -> getYDim();
}

int GameLogic::getUserXPos(){
  return this -> userPaddle -> getXPos();
}

int GameLogic::getUserYPos(){
  return this -> userPaddle -> getYPos();
}


//Grab data on computer paddle
int GameLogic::getCompXDim(){
  return this -> compPaddle -> getXDim();
}

int GameLogic::getCompYDim(){
  return this -> compPaddle -> getYDim();
}

int GameLogic::getCompXPos(){
  return this -> compPaddle -> getXPos();
}

int GameLogic::getCompYPos(){
  return this -> compPaddle -> getYPos();
}


//Grab data on the game ball
float GameLogic::getBallXPos(){
  return this -> ball -> getXPos();
}

float GameLogic::getBallYPos(){
  return this -> ball -> getYPos();
}

int GameLogic::getBallRadius(){
  return this -> ball -> getRadius();
}
int GameLogic::getBallAngle(){
  return this -> ball -> getAngle();
}
int GameLogic::getBallSpeed(){
  return this -> ball -> getSpeed();
}
int GameLogic::getBallResetSpeed(){
  return this -> ball -> getBallResetSpeed();
}


//Change ball data
void GameLogic::setBallXPos(float newXPos){
  this -> ball -> setXPos(newXPos);
}
void GameLogic::setBallYPos(float newYPos){
  this -> ball -> setYPos(newYPos);
}
void GameLogic::setBallAngle(int newAngle){
  this -> ball -> setAngle(newAngle);
}
void GameLogic::setBallSpeed(int newSpeed){
  this -> ball -> setSpeed(newSpeed);
}

//Change user paddle data
void GameLogic::setUserPaddleSpeed(int newSpeed){
  this -> userPaddle -> setSpeed(newSpeed);
}

//Change comp paddle data
void GameLogic::setCompPaddleSpeeD(int newSpeed){
  this -> compPaddle -> setSpeed(newSpeed);
}
