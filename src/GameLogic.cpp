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
  this -> topBorder = unique_ptr<Border>(new Border(0,0,windowX, windowY / 60,
                                          Border::top, sf::Color::Red));
  this -> bottomBorder = unique_ptr<Border>(new Border(0, windowY - (windowY / 60),
                                            windowX, windowY / 60, Border::bottom,
                                            sf::Color::Red));
  this -> leftBorder = unique_ptr<Border>(new Border(0,windowY/60,windowX / 160,
                                          windowY - 2 * (windowY/60), Border::left,
                                          sf::Color::Green));
  this -> rightBorder = unique_ptr<Border>(new Border(windowX - (windowX / 160),
                                           windowY / 60, windowX / 160,
                                           windowY - 2 * (windowY/60), Border::right,
                                           sf::Color::Green));
  this -> mainMenu = unique_ptr<MainMenu>(new MainMenu(windowX, windowY));

  this -> optionMenu = unique_ptr<OptionMenu>(new OptionMenu(windowX, windowY));

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
  this -> optionMenu -> setWindowSize(windowX, windowY);
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

//switch to a handler for the appropriate drop down selected
void GameLogic::handleClickedDropDown(vector<int> clickDropDown){

  //0 is game object selection
  //1 is game object color selection
  //2 is game computer difficulty selection
  switch(clickDropDown[0]){
    case 0:
      this -> handleClickedGameObjectSelect(clickDropDown[1]);
      break;
    case 1:
      this -> handleClickedColorSelect(clickDropDown[1]);
      break;
    case 2:
      this -> handleClickedDifficultySelect(clickDropDown[1]);
      break;
  };
}

//if game object select is chosen change whether the dropw down list is expanded
//and set the currently selected option as the clicked option
//and since the game object selected is switching then the color
//selection needs to change to reflect that
//fix outlines makes the outline of the chosen option prominent and a differnet
//color than the others
void GameLogic::handleClickedGameObjectSelect(int objectSelectedIndex){
  DropDown *gameObjectSelect = this -> optionMenu -> getSelectObjectDropDown();

  gameObjectSelect -> flipExpandList();
  gameObjectSelect -> selectOption(objectSelectedIndex);
  gameObjectSelect -> fixOutlines();

  DropDown *colorSelect = this -> optionMenu -> getSelectColorDropDown();
  int objectSelectedColorIndex = this -> getColorIndexOfCurrentlySelectedObject();
  colorSelect -> selectOption(objectSelectedColorIndex);
  colorSelect -> fixOutlines();

}
//if a color for a game object is selected change whether the drop down list
// is expanded and set the currently selected option as the clicked option
// then change the color of the selected object to the desired color
//fix outlines makes the outline of the chosen option prominent and a differnet
//color than the others
void GameLogic::handleClickedColorSelect(int objectSelectedIndex){
  DropDown *colorSelect = this -> optionMenu -> getSelectColorDropDown();

  colorSelect -> flipExpandList();
  colorSelect -> selectOption(objectSelectedIndex);
  colorSelect -> fixOutlines();

  string chosenColor = colorSelect -> getSelectedItemString();
  this -> switchColor(chosenColor);
}

//if a difficulty is selected for the computer change whether the drop down
// list is expanded and set the currently selected option as the clicked option
// then change the difficulty of the computer
//fix outlines makes the outline of the chosen option prominent and a differnet
//color than the others
void GameLogic::handleClickedDifficultySelect(int objectSelectedIndex){
  DropDown *difficultySelect = this -> optionMenu -> getSelectDifficultyDropDown();

  difficultySelect -> flipExpandList();
  difficultySelect -> selectOption(objectSelectedIndex);
  difficultySelect -> fixOutlines();

  Paddle::Difficulty difficulty = this -> getCurrentlySelectedDifficulty();

  this -> compPaddle -> setDifficulty(difficulty);
}

//switch the color of the currently selected game object
void GameLogic::switchColor(string chosenColor){
  DropDown *objectSelect = this -> optionMenu -> getSelectObjectDropDown();
  string objectName = objectSelect -> getSelectedItemString();
  sf::Color color = getCurrentlySelectedColor();

  if (objectName == "Computer Paddle")
      this -> compPaddle -> setColor(color);
  else if(objectName == "User Paddle")
      this -> userPaddle -> setColor(color);
  else if(objectName == "Ball")
      this -> ball -> setColor(color);
  else if(objectName == "Top Border")
      this -> topBorder -> setColor(color);
  else if(objectName == "Bottom Border")
      this -> bottomBorder -> setColor(color);
  else if(objectName == "User Goal")
      this -> leftBorder -> setColor(color);
  else if(objectName == "Computer Goal")
      this -> rightBorder -> setColor(color);

}

//return the a color object corresponding to the currently select color option
sf::Color GameLogic::getCurrentlySelectedColor(){
  DropDown *colorSelect = this -> optionMenu -> getSelectColorDropDown();
  string colorName = colorSelect -> getSelectedItemString();

  if(colorName == "White")
      return sf::Color::White;
  else if(colorName == "Red")
      return sf::Color::Red;
  else if(colorName == "Green")
      return sf::Color::Green;
  else if(colorName == "Blue")
      return sf::Color::Blue;
  else if(colorName == "Yellow")
      return sf::Color::Yellow;
  else if(colorName == "Magenta")
      return sf::Color::Magenta;
  else if(colorName == "Cyan")
      return sf::Color::Cyan;
}

//return a difficulty corresponding to the currently selected difficulty option
Paddle::Difficulty GameLogic::getCurrentlySelectedDifficulty(){
  DropDown *difficultySelect = this -> optionMenu -> getSelectDifficultyDropDown();

  string difficultyName = difficultySelect -> getSelectedItemString();

  if(difficultyName == "Easy")
      return Paddle::easy;
  if(difficultyName == "Medium")
      return Paddle::medium;
  if(difficultyName == "Hard")
      return Paddle::hard;

}

//return the index from the drop down list for the color
//of the currently selected object
int GameLogic::getColorIndexOfCurrentlySelectedObject(){
  DropDown *objectSelect = this -> optionMenu -> getSelectObjectDropDown();
  string objectName = objectSelect -> getSelectedItemString();
  sf::Color currColor = this -> getColorOfObject(objectName);

  return this -> optionMenu -> getColorIndexOfColor(currColor);

}

sf::Color GameLogic::getColorOfObject(string objectName){
  if (objectName == "Computer Paddle")
      return this -> compPaddle -> getColor();
  else if(objectName == "User Paddle")
      return this -> userPaddle -> getColor();
  else if(objectName == "Ball")
      return this -> ball -> getColor();
  else if(objectName == "Top Border")
      return this -> topBorder -> getColor();
  else if(objectName == "Bottom Border")
      return this -> bottomBorder -> getColor();
  else if(objectName == "User Goal")
      return this -> leftBorder -> getColor();
  else if(objectName == "Computer Goal")
      return this -> rightBorder -> getColor();
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

//check if there is any sort of normal collision (so non scoring)
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

//check if either goal was hit
bool GameLogic::ballHitsGoal(){

  if(this -> ballHitsUserGoal()){
    return true;
  }
  else if(this -> ballHitsCompGoal()){
    return true;
  }
  return false;
}

//check if the ball hit the user's goal (right side)
bool GameLogic::ballHitsUserGoal(){
  sf::FloatRect userGoalBox = (this -> leftBorder) -> getGlobalBounds();
  sf::FloatRect ballBox = (this -> ball) -> getGlobalBounds();

  if(userGoalBox.intersects(ballBox)){
    return true;
  }

  return false;
}

//check if the ball hit the computer's goal (left side)
bool GameLogic::ballHitsCompGoal(){
  sf::FloatRect compGoalBox = (this -> rightBorder) -> getGlobalBounds();
  sf::FloatRect ballBox = (this -> ball) -> getGlobalBounds();

  if(compGoalBox.intersects(ballBox)){
    return true;
  }

  return false;
}

//check if the ball hit either the top or bottom
bool GameLogic::ballHitsNonGoalSides(){

  if(this -> ballHitsTopSide()){
    return true;
  }
  else if(this -> ballHitsBottomSide()){
    return true;
  }
  return false;
}

//check if the ball hit the top side
bool GameLogic::ballHitsTopSide(){
  sf::FloatRect topSideBox = (this -> topBorder) -> getGlobalBounds();
  sf::FloatRect ballBox = (this -> ball) -> getGlobalBounds();

  if(topSideBox.intersects(ballBox)){
    return true;
  }
  return false;

}

//check if the ball hit the bottom border
bool GameLogic::ballHitsBottomSide(){
  sf::FloatRect bottomSideBox = (this -> bottomBorder) -> getGlobalBounds();
  sf::FloatRect ballBox = (this -> ball) -> getGlobalBounds();

  if(bottomSideBox.intersects(ballBox)){
    return true;
  }
  return false;


}

//check if the ball hit either paddle
bool GameLogic::ballHitsAPaddle(){

  if(this -> ballHitsUserPaddle()){
    return true;
  }
  else if(this -> ballHitsCompPaddle()){
    return true;
  }
  return false;
}

//check if the ball hit the user paddle
bool GameLogic::ballHitsUserPaddle(){
  sf::FloatRect userPaddleBox = (this -> userPaddle) -> getGlobalBounds();
  sf::FloatRect ballBox = (this -> ball) -> getGlobalBounds();

  if(userPaddleBox.intersects(ballBox)){
    return true;
  }
  return false;
}

//check if the ball hit the computer paddle
bool GameLogic::ballHitsCompPaddle(){
  sf::FloatRect compPaddleBox = (this -> compPaddle) -> getGlobalBounds();
  sf::FloatRect ballBox = (this -> ball) -> getGlobalBounds();

  if(compPaddleBox.intersects(ballBox)){
    return true;
  }
  return false;
}

//if there was a collision flip the ball around according to where it hit
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

//tell if there is a score
bool GameLogic::isScore(){
  float ballX = this -> getBallXPos();
  float ballY = this -> getBallYPos();
  int ballRadius = this -> getBallRadius();

  if(this -> ballHitsGoal()){
    return true;
  }
  return false;
}

//if there is a score update the score of the team that scoreBoard
//pause the game, reset the ball, and check if there is now a winner
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

//if there is a winner pause the game and switch to the game over screen
void GameLogic::handlePotentialWin(ScoreBoard::Side winner){
  if(winner != ScoreBoard::neither){
    this -> pauseGame();
    this -> isGameOver = true;
  }
}

//reset the ball to its original position
void GameLogic::resetBall(){
  float halfWindowX = (float) (this -> windowX)/2;
  float halfWindowY = (float) (this -> windowY)/2;

  this -> setBallXPos(halfWindowX);
  this -> setBallYPos(halfWindowY);
  this -> setBallAngle(180);
  this -> setBallSpeed(0);

}

//stop all moving objects and set pause to true
void GameLogic::pauseGame(){
  this -> isPaused = true;
  this -> setBallSpeed(0);
  this -> setUserPaddleSpeed(0);
  this -> setCompPaddleSpeed(0);
}

//make all objects move again
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
sf::Color GameLogic::getUserPaddleColor(){
  return this -> userPaddle -> getColor();
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
sf::Color GameLogic::getCompPaddleColor(){
  return this -> compPaddle -> getColor();
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
sf::Color GameLogic::getBallColor(){
  return this -> ball -> getColor();
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
sf::Color GameLogic::getTopBorderColor(){
  return this -> topBorder -> getColor();
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
sf::Color GameLogic::getBottomBorderColor(){
  return this -> bottomBorder -> getColor();
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
sf::Color GameLogic::getLeftBorderColor(){
  return this -> leftBorder -> getColor();
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
sf::Color GameLogic::getRightBorderColor(){
  return this -> rightBorder -> getColor();
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

sf::FloatRect GameLogic::getMainMenuQuitButtonBoundBox(){
  return this -> mainMenu -> getQuitButtonGlobalBounds();
}
int GameLogic::getMainMenuQuitButtonCharSize(){
  return this -> mainMenu -> getQuitButtonCharSize();
}

//Get the option menu data
DropDown * GameLogic::getOptionMenuObjectSelect(){
  return this -> optionMenu -> getSelectObjectDropDown();
}

DropDown * GameLogic::getOptionMenuColorSelect(){
  return this -> optionMenu -> getSelectColorDropDown();
}

DropDown * GameLogic::getOptionMenuDifficultySelect(){
  return this -> optionMenu -> getSelectDifficultyDropDown();
}

int GameLogic::getGameObjectSelected(){
  return this -> optionMenu -> getGameObjectSelected();
}
int GameLogic::getGameDifficultySelected(){
  return this -> optionMenu -> getSelectedDifficulty();
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
void GameLogic::setBallColor(sf::Color &color){
  this -> ball -> setColor(color);
}

//Change user paddle data
void GameLogic::setUserPaddleSpeed(int newSpeed){
  this -> userPaddle -> setSpeed(newSpeed);
}
void GameLogic::setUserPaddleColor(sf::Color &color){
  this -> userPaddle -> setColor(color);
}

//Change comp paddle data
void GameLogic::setCompPaddleSpeed(int newSpeed){
  this -> compPaddle -> setSpeed(newSpeed);
}
void GameLogic::setCompPaddleColor(sf::Color &color){
  this -> compPaddle -> setColor(color);
}


//change top border data
void GameLogic::setTopBorderColor(sf::Color &color){
  this -> topBorder -> setColor(color);
}

//change bottom border data
void GameLogic::setBottomBorderColor(sf::Color &color){
  this -> bottomBorder -> setColor(color);
}

//change left border data
void GameLogic::setLeftBorderColor(sf::Color &color){
  this -> leftBorder -> setColor(color);
}

//change right border data
void GameLogic::setRightBorderColor(sf::Color &color){
  this -> rightBorder -> setColor(color);
}
