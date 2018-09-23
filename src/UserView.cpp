#include "UserView.hpp"
#include <iostream>

using std::cout;

UserView::UserView(GameLogic *gameLogic){
  this -> gameLogic = gameLogic;
  this -> windowX = gameLogic -> getWindowX();
  this -> windowY = gameLogic -> getWindowY();
  this -> loadFont();
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

void UserView::updateUserView(int deltaS, sf::RenderWindow &game){
  game.clear();

  this -> processEvents(game);

  if(this -> gameLogic -> isMainMenuOn()){
    this -> drawMainMenuTitle(game);
    this -> drawSelectPlayMessageText(game);
    this -> drawSelectOptionsMenuText(game);
  }
  else if(this -> gameLogic -> isOptionsMenuOn()){

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

void UserView::processEvents(sf::RenderWindow  &game){
  // process events
  sf::Event Event;
  while(game.pollEvent(Event))
  {
    // Exit
    if(Event.type == sf::Event::Closed)
      this -> gameLogic -> shutdownGame(game);
    //Key Pressed
    else if(Event.type == sf::Event::KeyPressed){
      this ->  keyPressed(Event, game);
    }
    //mouse button Pressed
    else if(Event.type == sf::Event::MouseButtonPressed){
      this ->  mousePressed(Event, game);
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

  rectangle.setFillColor(sf::Color::Red);
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

  rectangle.setFillColor(sf::Color::Red);
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

  rectangle.setFillColor(sf::Color::Green);
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

  rectangle.setFillColor(sf::Color::Green);
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

string UserView::getWinnerString(){
  ScoreBoard::Side winner = this -> gameLogic -> getWinningSide();

  switch(winner){
    case ScoreBoard::player:
      return "player";
    case ScoreBoard::comp:
      return "comp";
  }
}

void UserView::keyPressed(sf::Event event, sf::RenderWindow &game){
  auto keyPress = unique_ptr<KeyPress>(new KeyPress());
  keyPress -> processInput(event, (this -> gameLogic), game);
}

void UserView::mousePressed(sf::Event event, sf::RenderWindow &game){
  auto mousePress = unique_ptr<MousePress>(new MousePress());
  mousePress -> processInput(event, (this -> gameLogic), game);
}
