#include "UserView.hpp"
#include <iostream>

using std::cout;

UserView::UserView(GameLogic *gameLogic){
  this -> gameLogic = gameLogic;
  this -> windowX = gameLogic -> getWindowX();
  this -> windowY = gameLogic -> getWindowY();
  this -> loadFont();
  this -> keyPress = unique_ptr<KeyPress>(new KeyPress());
  this -> mousePress = unique_ptr<MousePress>(new MousePress());
  this -> successFullTexture = (this -> ballTexture).loadFromFile("../image/ppeers2.png");
}

UserView::~UserView(){
  this -> gameLogic = nullptr;
}

void UserView::loadFont(){
  if (!(this -> mainFont).loadFromFile("../fonts/ARCADECLASSIC.TTF"))
  {
    cout << "Font does not exist " << std::endl;
  }
}

void UserView::updateUserView(sf::RenderWindow &game, float deltaS){
  game.clear();

  this -> processEvents(game, deltaS);

  if(this -> gameLogic -> isMainMenuOn()){
    this -> drawMainMenuTitle(game);
    this -> drawSelectPlayMessageText(game);
    this -> drawSelectOptionsMenuText(game);
    this -> drawSelectQuitText(game);
  }
  else if(this -> gameLogic -> isOptionsMenuOn()){

    this -> drawSelectObjectList(game);
    this -> drawSelectColorList(game);
    //index corresponding to the game object being modified
    //some objects do not have the same set of drop down for options
    int objectSelected = this -> gameLogic -> getGameObjectSelected();
    if(objectSelected == 0){
      this -> drawSelectDifficultyList(game);
    }

    this -> drawBackButton(game);

  }
  else if(!(this -> gameLogic -> isGameEnded())){
    this -> drawUserPaddle(game);
    this -> drawCompPaddle(game);
    this -> drawBall(game);
    this -> drawText(game);
    this -> drawSideBorders(game);
    this -> drawGoalBorders(game);
  }
  else{
    this -> drawEndGameMessage(game);
  }

  game.display();

}

void UserView::processEvents(sf::RenderWindow  &game, float deltaS){
  // process events
  sf::Event Event;
  while(game.pollEvent(Event))
  {
    // Exit
    if(Event.type == sf::Event::Closed)
      this -> gameLogic -> shutdownGame(game);
    //Key Pressed
    else if(Event.type == sf::Event::KeyPressed){
      //cout << "time of key press " << deltaS << std::endl;
      this ->  keyPressed(Event, game, deltaS);
    }
    //mouse button Pressed
    else if(Event.type == sf::Event::MouseButtonPressed){
      this ->  mousePressed(Event, game);
    }
    //if clicked another window on game window
    else if(Event.type == sf::Event::LostFocus){
      //only consider this when on the game window
      if(!(this -> gameLogic -> isMainMenuOn()) && !(this -> gameLogic -> isOptionsMenuOn())
        && !(this -> gameLogic -> isGameEnded())){
          this -> gameLogic -> pauseGame();
      }
    }
  }
}

void UserView::drawMainMenuTitle(sf::RenderWindow &game){
    (this -> mainMenuText).setFont(this -> mainFont);

    int xPos = this -> gameLogic -> getWindowX();
    int yPos = this -> gameLogic -> getWindowY();

    (this -> mainMenuText).setString("Pong");

    (this -> mainMenuText).setCharacterSize(xPos / 8);

    (this -> mainMenuText).setFillColor(sf::Color::White);

    (this -> mainMenuText).setStyle(sf::Text::Bold);

    (this -> mainMenuText).setPosition((xPos/4), (yPos / 6));

    game.draw((this -> mainMenuText));
}

void UserView::drawSelectPlayMessageText(sf::RenderWindow &game){
  (this -> playGameText).setFont(this -> mainFont);

  int xPos = this -> gameLogic -> getWindowX();
  int yPos = this -> gameLogic -> getWindowY();

  (this -> playGameText).setString("Play");

  (this -> playGameText).setCharacterSize(xPos / 16);

  (this -> playGameText).setFillColor(sf::Color::White);

  (this -> playGameText).setStyle(sf::Text::Bold);

  (this -> playGameText).setPosition((xPos/4), (yPos / 6)*2);

  game.draw((this -> playGameText));
}

void UserView::drawSelectOptionsMenuText(sf::RenderWindow &game){
  (this -> optionsMenuSelectText).setFont(this -> mainFont);

  int xPos = this -> gameLogic -> getWindowX();
  int yPos = this -> gameLogic -> getWindowY();

  (this -> optionsMenuSelectText).setString("Options");

  (this -> optionsMenuSelectText).setCharacterSize(xPos / 16);

  (this -> optionsMenuSelectText).setFillColor(sf::Color::White);

  (this -> optionsMenuSelectText).setStyle(sf::Text::Bold);

  (this -> optionsMenuSelectText).setPosition((xPos/4), (yPos / 6)*3);

  game.draw((this -> optionsMenuSelectText));
}

void UserView::drawSelectQuitText(sf::RenderWindow &game){
  (this -> quitGameText).setFont(this -> mainFont);

  int xPos = this -> gameLogic -> getWindowX();
  int yPos = this -> gameLogic -> getWindowY();

  (this -> quitGameText).setString("Quit");

  (this -> quitGameText).setCharacterSize(xPos / 16);

  (this -> quitGameText).setFillColor(sf::Color::White);

  (this -> quitGameText).setStyle(sf::Text::Bold);

  (this -> quitGameText).setPosition((xPos/4), (yPos / 6)*4);

  game.draw((this -> quitGameText));
}

void UserView::drawSelectObjectList(sf::RenderWindow &game){

  DropDown *selectObjectDropDown = (this -> gameLogic -> getOptionMenuObjectSelect());

  if(selectObjectDropDown -> isExpanded()){
    this -> drawDropDownExpanded(*selectObjectDropDown, game);
  }
  else{
    this -> drawDropDownSingleOption(*selectObjectDropDown, game);
  }

}

void UserView::drawSelectColorList(sf::RenderWindow &game){
  DropDown *selectColorDropDown = (this -> gameLogic -> getOptionMenuColorSelect());


  if(selectColorDropDown -> isExpanded()){
      this -> drawDropDownExpanded(*selectColorDropDown, game);
  }
  else{
      this -> drawDropDownSingleOption(*selectColorDropDown, game);
  }
}

void UserView::drawSelectDifficultyList(sf::RenderWindow &game){
  DropDown *selectDifficulty = (this -> gameLogic -> getOptionMenuDifficultySelect());


  if(selectDifficulty -> isExpanded()){
      this -> drawDropDownExpanded(*selectDifficulty, game);
  }
  else{
      this -> drawDropDownSingleOption(*selectDifficulty, game);
  }
}

void UserView::drawBackButton(sf::RenderWindow &game){
  Button *backButton = (this -> gameLogic -> getOptionMenuBackButton());
  sf::Text text = backButton -> getButtonText();
  sf::RectangleShape rect = backButton -> getButtonRect();

  text.setFont(this -> mainFont);

  game.draw(text);
  game.draw(rect);
}

void UserView::drawUserPaddle(sf::RenderWindow &game){
  sf::RectangleShape rectangle;

  int xPos = this -> gameLogic -> getUserXPos();
  int yPos = this -> gameLogic -> getUserYPos();
  int xDim = this -> gameLogic -> getUserXDim();
  int yDim = this -> gameLogic -> getUserYDim();
  sf::Color userPaddleColor = this -> gameLogic -> getUserPaddleColor();

  rectangle.setFillColor(userPaddleColor);
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
  sf::Color compPaddleColor = this -> gameLogic -> getCompPaddleColor();

  rectangle.setFillColor(compPaddleColor);
  rectangle.setSize(sf::Vector2f(xDim,yDim));
  rectangle.setPosition(xPos, yPos);

  game.draw(rectangle);
}

void UserView::drawBall(sf::RenderWindow &game){


  float xPos = (float) (this -> gameLogic -> getBallXPos());
  float yPos = (float) (this -> gameLogic -> getBallYPos());
  float angle = (float) (this -> gameLogic -> getBallAngle());
  float radius = (float) (this -> gameLogic -> getBallRadius());
  sf::Color ballColor = this -> gameLogic -> getBallColor();

  (this -> ball).setPosition(sf::Vector2f(xPos, yPos));
  (this -> ball).setRadius(radius);
  (this -> ball).setFillColor(ballColor);

  //try to load texture from file
  if(!(this -> gameLogic -> isKonamiCode()) || !(this -> successFullTexture)){
    (this -> ball).setFillColor(sf::Color::White);
    game.draw((this -> ball));
  }
  else{
    (this -> textureBall).setPosition(sf::Vector2f(xPos, yPos));
    (this -> textureBall).setRadius(radius);
    (this -> textureBall).setTextureRect(sf::IntRect(5,20,100,125));
    (this -> textureBall).setTexture(&(this -> ballTexture));
    game.draw((this -> textureBall));
  }

}

void UserView::drawText(sf::RenderWindow &game){
  this -> drawPauseMessage(game);
  this -> drawScoreBoard(game);
}

void UserView::drawPauseMessage(sf::RenderWindow &game){
  if (this -> gameLogic -> isGamePaused()){
    (this -> pauseText).setFont(this -> mainFont);

    int xPos = this -> gameLogic -> getWindowX();
    int yPos = this -> gameLogic -> getWindowY();

    (this -> pauseText).setString("Press Spacebar When Ready.");

    (this -> pauseText).setCharacterSize(xPos / 32);

    (this -> pauseText).setFillColor(sf::Color::White);

    (this -> pauseText).setStyle(sf::Text::Bold);

    (this -> pauseText).setPosition(xPos/6, (yPos / 2) + this -> gameLogic -> getBallRadius());

    game.draw((this -> pauseText));

  }
}

void UserView::drawScoreBoard(sf::RenderWindow &game) {
  this -> drawComputerScore(game);
  this -> drawUserScore(game);
}

void UserView::drawComputerScore(sf::RenderWindow &game){
  if (!(this -> gameLogic -> isGameEnded())){
    (this -> compScoreText).setFont(this -> mainFont);

    int xPos = this -> windowX;
    int yPos = this -> windowY;

    int compScore = this -> gameLogic -> getCompScore();

    string scoreText = to_string(compScore);

    (this -> compScoreText).setString(scoreText);

    (this -> compScoreText).setCharacterSize(xPos / 40);

    (this -> compScoreText).setFillColor(sf::Color::White);

    (this -> compScoreText).setStyle(sf::Text::Bold);

    (this -> compScoreText).setPosition((xPos/6) * 5, 10);

    game.draw((this -> compScoreText));
  }
}

void UserView::drawUserScore(sf::RenderWindow &game){
  if (!(this -> gameLogic -> isGameEnded())){
    (this -> userScoreText).setFont(this -> mainFont);

    int xPos = this -> windowX;
    int yPos = this -> windowY;

    int userScore = this -> gameLogic -> getUserScore();

    string scoreText = to_string(userScore);

    (this -> userScoreText).setString(scoreText);

    (this -> userScoreText).setCharacterSize(xPos / 40);

    (this -> userScoreText).setFillColor(sf::Color::White);

    (this -> userScoreText).setStyle(sf::Text::Bold);

    (this -> userScoreText).setPosition(xPos/6,  10);

    game.draw((this -> userScoreText));

  }
}

void UserView::drawSideBorders(sf::RenderWindow &game){
  this -> drawTopBorder(game);
  this -> drawBottomBorder(game);
}

void UserView::drawTopBorder(sf::RenderWindow &game){
  sf::RectangleShape rectangle;

  int topBorderYDim = this -> gameLogic -> getTopBorderYDim();
  int topBorderXDim = this -> gameLogic -> getTopBorderXDim();
  int topBorderXPos = this -> gameLogic -> getTopBorderXPos();
  int topBorderYPos = this -> gameLogic -> getTopBorderYPos();
  sf::Color topBorderColor = this -> gameLogic -> getTopBorderColor();

  rectangle.setFillColor(topBorderColor);
  rectangle.setSize(sf::Vector2f(topBorderXDim,topBorderYDim));
  rectangle.setPosition(topBorderXPos, topBorderYPos);

  game.draw(rectangle);
}

void UserView::drawBottomBorder(sf::RenderWindow &game){
  sf::RectangleShape rectangle;

  int bottomBorderYDim = this -> gameLogic -> getBottomBorderYDim();
  int bottomBorderXDim = this -> gameLogic -> getBottomBorderXDim();
  int bottomBorderXPos = this -> gameLogic -> getBottomBorderXPos();
  int bottomBorderYPos = this -> gameLogic -> getBottomBorderYPos();
  sf::Color bottomBorderColor = this -> gameLogic -> getBottomBorderColor();

  rectangle.setFillColor(bottomBorderColor);
  rectangle.setSize(sf::Vector2f(bottomBorderXDim, bottomBorderYDim));
  rectangle.setPosition(bottomBorderXPos, bottomBorderYPos);

  game.draw(rectangle);
}

void UserView::drawGoalBorders(sf::RenderWindow &game){
  this -> drawUserGoal(game);
  this -> drawCompGoal(game);
}

void UserView::drawUserGoal(sf::RenderWindow &game){
  sf::RectangleShape rectangle;

  int leftBorderYDim = this -> gameLogic -> getLeftBorderYDim();
  int leftBorderXDim = this -> gameLogic -> getLeftBorderXDim();
  int leftBorderXPos = this -> gameLogic -> getLeftBorderXPos();
  int leftBorderYPos = this -> gameLogic -> getLeftBorderYPos();
  sf::Color leftBorderColor = this -> gameLogic -> getLeftBorderColor();

  rectangle.setFillColor(leftBorderColor);
  rectangle.setSize(sf::Vector2f(leftBorderXDim, leftBorderYDim));
  rectangle.setPosition(leftBorderXPos, leftBorderYPos);

  game.draw(rectangle);
}

void UserView::drawCompGoal(sf::RenderWindow &game){
  sf::RectangleShape rectangle;

  int rightBorderYDim = this -> gameLogic -> getRightBorderYDim();
  int rightBorderXDim = this -> gameLogic -> getRightBorderXDim();
  int rightBorderXPos = this -> gameLogic -> getRightBorderXPos();
  int rightBorderYPos = this -> gameLogic -> getRightBorderYPos();
  sf::Color rightBorderColor = this -> gameLogic -> getRightBorderColor();

  rectangle.setFillColor(rightBorderColor);
  rectangle.setSize(sf::Vector2f(rightBorderXDim, rightBorderYDim));
  rectangle.setPosition(rightBorderXPos, rightBorderYPos);

  game.draw(rectangle);
}

void UserView::drawEndGameMessage(sf::RenderWindow &game){
    (this -> restartText).setFont(this -> mainFont);

    int xPos = this -> gameLogic -> getWindowX();
    int yPos = this -> gameLogic -> getWindowY();

    string winnerString = this -> getWinnerString();

    string restartString = winnerString + " won! \n Press R to restart and Q to quit";

    (this -> restartText).setString(restartString);

    (this -> restartText).setCharacterSize(xPos / 32);

    (this -> restartText).setFillColor(sf::Color::White);

    (this -> restartText).setStyle(sf::Text::Bold);

    (this -> restartText).setPosition(xPos/6, (yPos / 2) + this -> gameLogic -> getBallRadius());

    game.draw((this -> restartText));

}

void UserView::drawDropDownExpanded(DropDown &dropDown, sf::RenderWindow &game){
  vector<sf::RectangleShape> optionsRects = dropDown.getOptionsRects();
  vector<sf::Text> optionsTexts = dropDown.getOptionsTexts();
  int numOptions = dropDown.getNumOptions();

  for(int i = 0; i < numOptions; i++){
    game.draw(optionsRects[i]);
    (optionsTexts[i].setFont(this -> mainFont));
    game.draw(optionsTexts[i]);
  }
}
void UserView::drawDropDownSingleOption(DropDown &dropDown, sf::RenderWindow &game){
  int selectedItemIndex = dropDown.getSelectedItemIndex();
  sf::Text chosenText = dropDown.getSelectedOptionText(selectedItemIndex);
  sf::RectangleShape chosenRect = dropDown.getSelectedOptionRect(selectedItemIndex);

  //we keep track of the original y position it should be in
  //becuase we want it to appear at the top of the page when it is selected
  //and the drop down list is not extended. when the list is extended we
  //want it to appear in its proper y positon
  sf::Vector2f pos = chosenRect.getPosition();
  int originalYPos = pos.y;
  int originalXpos = pos.x;

  //same reposition of the text
  sf::Vector2f textPos = chosenText.getPosition();
  int originalTextXPos = textPos.x;
  int originalTextYPos = textPos.y;

  //temporarily make the y position at the top for the rect
  chosenRect.setPosition(originalXpos, 0);
  //change y position of the text temporarily as well
  chosenText.setPosition(originalTextXPos, 0);

  (chosenText.setFont(this -> mainFont));
  game.draw(chosenText);
  game.draw(chosenRect);

  //then reset the position
  chosenRect.setPosition(originalXpos, originalYPos);
  //reset the text position too
  chosenText.setPosition(originalTextXPos, originalTextYPos);
}

string UserView::getWinnerString(){
  ScoreBoard::Side winner = this -> gameLogic -> getWinningSide();

  switch(winner){
    case ScoreBoard::player:
      return "player";
    case ScoreBoard::comp:
      return "comp";
  }
}

void UserView::keyPressed(sf::Event event, sf::RenderWindow &game,float deltaS){
  this -> keyPress -> processInput(event, (this -> gameLogic), game, deltaS);
}

void UserView::mousePressed(sf::Event event, sf::RenderWindow &game){
  this -> mousePress -> processInput(event, (this -> gameLogic), game);
}
