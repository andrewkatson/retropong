#include "MousePress.hpp"



MousePress::MousePress(){}

void MousePress::processInput(sf::Event event, GameLogic *gameLogic, sf::RenderWindow &game){

  //cout << "Mouse Press";
  //if the game is on the main menu
  if(gameLogic -> isMainMenuOn()){
    //cout << "Main Menu";
    if(this -> clickedPlayButton(event, gameLogic)){
        cout << "PLAY";
        gameLogic -> startPlaying();
    }
    else if(this -> clickedOptionsButton(event, gameLogic)){
        gameLogic -> startOptionsMenu();
    }
  }
  //if the game is on the options menu
  else if( gameLogic -> isOptionsMenuOn()){

  }
}

bool MousePress::clickedPlayButton(sf::Event event, GameLogic *gameLogic){
  int mousePressX = event.mouseButton.x;
  int mousePressY = event.mouseButton.y;
  int boundXDim =  (gameLogic -> getMainMenuPlayButtonCharSize()) * 3;
  int boundYDim = (gameLogic -> getMainMenuOptionMenuButtonCharSize()) * 2;

  sf::FloatRect playSelectBoundingBox =  gameLogic -> getMainMenuPlayButtonBoundBox();

  if(this -> mouseClickOnButton(mousePressX, mousePressY, boundXDim, boundYDim,
     playSelectBoundingBox)){
    return true;
  }
  return false;
}

bool MousePress::clickedOptionsButton(sf::Event event, GameLogic *gameLogic){
  int mousePressX = event.mouseButton.x;
  int mousePressY = event.mouseButton.y;
  int boundXDim =  (gameLogic -> getMainMenuOptionMenuButtonCharSize()) * 3;
  int boundYDim = (gameLogic -> getMainMenuOptionMenuButtonCharSize()) * 2;

  sf::FloatRect optionMenuSelectBoundingBox = gameLogic -> getMainMenuOptionMenuButtonBoundBox();

  if(this -> mouseClickOnButton(mousePressX, mousePressY, boundXDim, boundYDim,
     optionMenuSelectBoundingBox)){
    return true;
  }
  return false;
}

//check if the mouse click was on the button
bool MousePress::mouseClickOnButton(int mousePressX, int mousePressY, int boundXDim,
                                    int boundYDim, sf::FloatRect boundingBox){
  int boundXPos = boundingBox.left;
  int boundYPos = boundingBox.top;

  //cout << "We click x " << this -> clickInRange(mousePressX, boundXPos, boundXDim);
  //cout << "We click y " << this -> clickInRange(mousePressY, boundYPos, boundYDim);

  cout << "Bound x " << boundXPos;
  cout << "Bound y " << boundYPos;
  cout << "Bound x dim " << boundXDim;
  cout << "Bound y dim " << boundYDim;
  cout << "Mouse Press x " << mousePressX;
  cout << "Mouse Press y " << mousePressY;

  if(this -> clickInRange(mousePressX, boundXPos, boundXDim) &&
    this -> clickInRange(mousePressY, boundYPos, boundYDim)) {
      return true;
  }
  return false;
}

//check if the mouse press was on the line defined by the position and dimension
bool MousePress::clickInRange(int mousePressPos, int boundPos, int boundDim){
  if(mousePressPos >= boundPos && mousePressPos <= boundPos + boundDim){
    return true;
  }
  return false;
}
