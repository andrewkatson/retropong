#include "GameLogic.hpp"



GameLogic::GameLogic(int windowX, int windowY, int winningScore){
  this -> init(windowX, windowY, winningScore);

  srand(time(0));
}

void GameLogic::init(int windowX, int windowY, int winningScore){
  this -> isPaused = true;
  this -> isGameOver = false;
  this -> isMainMenu = true;
  this -> isOptionsMenu = false;
  this -> userPaddle = unique_ptr<Paddle>(new Paddle(windowX/160 + 50,windowY/60 + 50,windowX/160,windowX/20,10));
  this -> compPaddle = unique_ptr<Paddle>(new Paddle(windowX - windowX/160 - 50,windowY/60 + 50, windowX/160,windowX/20,10));
  this -> ball = unique_ptr<Ball>(new Ball((float)(windowX / 2), (float)(windowY / 2),
                                  180, windowX/80, windowY/160));
  this -> scoreBoard =  unique_ptr<ScoreBoard>(new ScoreBoard(winningScore));
  this -> topBorder = unique_ptr<Border>(new Border(0,0,windowX, windowY / 60, Border::top));
  this -> bottomBorder = unique_ptr<Border>(new Border(0, windowY - (windowY / 60),
                                            windowX, windowY / 60, Border::bottom));
  this -> leftBorder = unique_ptr<Border>(new Border(0,windowY/60,windowX / 160,
                                          windowY - 2 * (windowY/60), Border::left));
  this -> rightBorder = unique_ptr<Border>(new Border(windowX - (windowX / 160),
                                           windowY / 60, windowX / 160,
                                           windowY - 2 * (windowY/60), Border::right));
  this -> mainMenu = unique_ptr<MainMenu>(new MainMenu(windowX, windowY));
  this -> updateWindowSize(windowX, windowY);
}

//start a game from the main menu
void GameLogic::startPlaying(){
  this -> isMainMenu = false;
}

//void start up the options menu from the main menu
void GameLogic::startOptionsMenu(){
  this -> isMainMenu = false;
  this -> isOptionsMenu = true;
}


//game is restarted
void GameLogic::restartGame(){
  this -> isPaused = true;
  this -> isGameOver = false;
  this -> isMainMenu = true;
  this -> isOptionsMenu = false;
  int user = 0;
  int comp = 1;
  //reset to original values and positions
  this -> userPaddle -> reset(user);
  this -> compPaddle -> reset(comp);
  this -> ball -> reset();
  this -> scoreBoard -> reset();
}

void GameLogic::shutdownGame(sf::RenderWindow  &game){
  game.close();
}

//when window is resized let all objects know
void GameLogic::updateWindowSize(int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> userPaddle -> setWindowSize(windowX, windowY);
  this -> compPaddle -> setWindowSize(windowX, windowY);
  this -> ball -> setWindowSize(windowX, windowY);
  this -> topBorder -> setWindowSize(windowX, windowY);
  this -> bottomBorder -> setWindowSize(windowX, windowY);
  this -> leftBorder -> setWindowSize(windowX, windowY);
  this -> rightBorder -> setWindowSize(windowX, windowY);
  this -> mainMenu -> setWindowSize(windowX, windowY);
}


void GameLogic::updateLogic(int deltaS){
  this -> moveBall();
  if(this -> isPaused){
    this -> pauseGame();
  }
  else{
    this -> unPauseGame();
  }
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
  if(this -> ballHitsGoal()){
    return false;
  }
  else if(this -> ballHitsNonGoalSides()){
    return true;
  }
  else if(this -> ballHitsAPaddle()){
    return true;
  }
  return false;
}

bool GameLogic::ballHitsGoal(){

  if(this -> ballHitsUserGoal()){
    return true;
  }
  else if(this -> ballHitsCompGoal()){
    return true;
  }
  return false;
}

bool GameLogic::ballHitsUserGoal(){
  sf::FloatRect userGoalBox = (this -> leftBorder) -> getGlobalBounds();
  sf::FloatRect ballBox = (this -> ball) -> getGlobalBounds();

  if(userGoalBox.intersects(ballBox)){
    return true;
  }

  return false;
}

bool GameLogic::ballHitsCompGoal(){
  sf::FloatRect compGoalBox = (this -> rightBorder) -> getGlobalBounds();
  sf::FloatRect ballBox = (this -> ball) -> getGlobalBounds();

  if(compGoalBox.intersects(ballBox)){
    return true;
  }

  return false;
}

bool GameLogic::ballHitsNonGoalSides(){

  if(this -> ballHitsTopSide()){
    return true;
  }
  else if(this -> ballHitsBottomSide()){
    return true;
  }
  return false;
}

bool GameLogic::ballHitsTopSide(){
  sf::FloatRect topSideBox = (this -> topBorder) -> getGlobalBounds();
  sf::FloatRect ballBox = (this -> ball) -> getGlobalBounds();

  if(topSideBox.intersects(ballBox)){
    return true;
  }
  return false;

}

bool GameLogic::ballHitsBottomSide(){
  sf::FloatRect bottomSideBox = (this -> bottomBorder) -> getGlobalBounds();
  sf::FloatRect ballBox = (this -> ball) -> getGlobalBounds();

  if(bottomSideBox.intersects(ballBox)){
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
  if(this -> ballHitsNonGoalSides()){
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

  if(this -> ballHitsGoal()){
    return true;
  }
  return false;
}

void GameLogic::handleScore(){
  float ballX = this -> getBallXPos();
  float ballY = this -> getBallYPos();
  int ballRadius = this -> getBallRadius();
  if(this -> ballHitsUserGoal()){
    this -> scoreBoard -> incrementCompScore();
  }
  else{
    this -> scoreBoard -> incrementUserScore();
  }

  ScoreBoard::Side winner = this -> scoreBoard -> hasWon();

  this -> handlePotentialWin(winner);

  this -> resetBall();

  this -> pauseGame();
}

void GameLogic::handlePotentialWin(ScoreBoard::Side winner){
  if(winner != ScoreBoard::neither){
    this -> pauseGame();
    this -> isGameOver = true;
  }
}

void GameLogic::resetBall(){
  float halfWindowX = (float) (this -> windowX)/2;
  float halfWindowY = (float) (this -> windowY)/2;

  this -> setBallXPos(halfWindowX);
  this -> setBallYPos(halfWindowY);
  this -> setBallAngle(180);
  this -> setBallSpeed(0);

}

void GameLogic::pauseGame(){
  this -> isPaused = true;
  this -> setBallSpeed(0);
  this -> setUserPaddleSpeed(0);
  this -> setCompPaddleSpeed(0);
}

void GameLogic::unPauseGame(){
  this -> isPaused = false;
  this -> setBallSpeed(5);
  this -> setUserPaddleSpeed(10);
  this -> setCompPaddleSpeed(10);
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

bool GameLogic::isMainMenuOn(){
  return this -> isMainMenu;
}

bool GameLogic::isOptionsMenuOn(){
  return this -> isOptionsMenu;
}

bool GameLogic::isGamePaused(){
  return this -> isPaused;
}

bool GameLogic::isGameEnded(){
  return this -> isGameOver;
}

ScoreBoard::Side GameLogic::getWinningSide(){
  return this -> scoreBoard -> hasWon();
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

//Get window data
int GameLogic::getWindowX(){
  return this -> windowX;
}

int GameLogic::getWindowY(){
  return this -> windowY;
}

//Get top border  box data
int GameLogic::getTopBorderXDim(){
  return this -> topBorder -> getXDim();
}
int GameLogic::getTopBorderYDim(){
  return this -> topBorder -> getYDim();
}
int GameLogic::getTopBorderXPos(){
  return this -> topBorder -> getXPos();
}
int GameLogic::getTopBorderYPos(){
  return this -> topBorder -> getYPos();
}

//Get bottom border box data
int GameLogic::getBottomBorderXDim(){
  return this -> bottomBorder -> getXDim();
}
int GameLogic::getBottomBorderYDim(){
  return this -> bottomBorder -> getYDim();
}
int GameLogic::getBottomBorderXPos(){
  return this -> bottomBorder -> getXPos();
}
int GameLogic::getBottomBorderYPos(){
  return this -> bottomBorder -> getYPos();
}

//Get left border box data
int GameLogic::getLeftBorderXDim(){
  return this -> leftBorder -> getXDim();
}
int GameLogic::getLeftBorderYDim(){
  return this -> leftBorder -> getYDim();
}
int GameLogic::getLeftBorderXPos(){
  return this -> leftBorder -> getXPos();
}
int GameLogic::getLeftBorderYPos(){
  return this -> leftBorder -> getYPos();
}

//Get right border box data
int GameLogic::getRightBorderXDim(){
  return this -> rightBorder -> getXDim();
}
int GameLogic::getRightBorderYDim(){
  return this -> rightBorder -> getYDim();
}
int GameLogic::getRightBorderXPos(){
  return this -> rightBorder -> getXPos();
}
int GameLogic::getRightBorderYPos(){
  return this -> rightBorder -> getYPos();
}

//Get main menu button data
sf::FloatRect GameLogic::getMainMenuPlayButtonBoundBox(){
  return this -> mainMenu -> getPlayButtonGlobalBounds();
}

int GameLogic::getMainMenuPlayButtonCharSize(){
  return this -> mainMenu -> getPlayButtonCharSize();
}

sf::FloatRect GameLogic::getMainMenuOptionMenuButtonBoundBox(){
  return this -> mainMenu -> getOptionsMenuButtonGlobalBounds();
}
int GameLogic::getMainMenuOptionMenuButtonCharSize(){
  return this -> mainMenu -> getOptionMenuButtonCharSize();
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
void GameLogic::setCompPaddleSpeed(int newSpeed){
  this -> compPaddle -> setSpeed(newSpeed);
}
