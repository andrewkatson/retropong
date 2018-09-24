#include "MousePress.hpp"



MousePress::MousePress(){}

void MousePress::processInput(sf::Event event, GameLogic *gameLogic, sf::RenderWindow &game){

  //if the game is on the main menu
  if(gameLogic -> isMainMenuOn()){
    if(this -> clickedPlayButton(event, gameLogic)){;
        gameLogic -> startPlaying();
    }
    else if(this -> clickedOptionsButton(event, gameLogic)){
        gameLogic -> startOptionsMenu();
    }
    else if(this -> clickedQuitButton(event, gameLogic)){
      gameLogic -> shutdownGame(game);
    }
  }
  //if the game is on the options menu
  else if( gameLogic -> isOptionsMenuOn()){
    //check if any of the drop down buttons have been clicked
    //return a 2d array where the first number is which drop down
    // was clicked and the second number is what option was selected
    vector<int> checkClickedDropDown = this -> checkClickedDropDown(event, gameLogic);

    //send the selected drop down number and the selected drop down to
    // the game logic to be handled
    if(checkClickedDropDown[0] != -1 && checkClickedDropDown[1] != -1){
      gameLogic -> handleClickedDropDown(checkClickedDropDown);
    }
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

bool MousePress::clickedQuitButton(sf::Event event, GameLogic *gameLogic){
  int mousePressX = event.mouseButton.x;
  int mousePressY = event.mouseButton.y;
  int boundXDim =  (gameLogic -> getMainMenuQuitButtonCharSize()) * 3;
  int boundYDim = (gameLogic -> getMainMenuQuitButtonCharSize()) * 2;

  sf::FloatRect quitButtonBoundingBox = gameLogic -> getMainMenuQuitButtonBoundBox();

  if(this -> mouseClickOnButton(mousePressX, mousePressY, boundXDim, boundYDim,
     quitButtonBoundingBox)){
    return true;
  }
  return false;
}

//check if the mouse click was on the button
bool MousePress::mouseClickOnButton(int mousePressX, int mousePressY, int boundXDim,
                                    int boundYDim, sf::FloatRect &boundingBox){
  int boundXPos = boundingBox.left;
  int boundYPos = boundingBox.top;


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

vector<int>  MousePress::checkClickedDropDown(sf::Event event, GameLogic *gameLogic){
  //get the drop down objects from the options menu
  DropDown *selectGameObject = gameLogic -> getOptionMenuObjectSelect();
  DropDown *selectColor = gameLogic -> getOptionMenuColorSelect();
  DropDown *selectDifficulty = gameLogic -> getOptionMenuDifficultySelect();

  //mouse press x
  int mousePressX = event.mouseButton.x;
  //mouse press y
  int mousePressY = event.mouseButton.y;

  //first number is the drop down selected and the second is the option chosen
  vector<int> selectedDropDown = {-1, -1};

  //integer to use as the return for each selected drop down
  int retSelected = 0;

  //check if the drop down is expanded so you cannot click
  // options that are not shown becuase the drop down is not expanded
  if(selectGameObject -> isExpanded()){
    retSelected = this -> checkClickedExpandedDropDown(mousePressX, mousePressY, selectGameObject);
    if(retSelected != -1){
      selectedDropDown[0] = 0;
      selectedDropDown[1] = retSelected;
    }
  }
  else{
    retSelected = this -> checkClickedSingleDropDown(mousePressX, mousePressY, selectGameObject);
    if(retSelected != -1){
      selectedDropDown[0] = 0;
      selectedDropDown[1] = retSelected;
    }
  }
  if(selectColor -> isExpanded()){
    retSelected = this -> checkClickedExpandedDropDown(mousePressX, mousePressY, selectColor);
    if(retSelected != -1){
      selectedDropDown[0] = 1;
      selectedDropDown[1] = retSelected;
    }
  }
  else{

    retSelected = this -> checkClickedSingleDropDown(mousePressX, mousePressY, selectColor);
    if(retSelected != -1){
      selectedDropDown[0] = 1;
      selectedDropDown[1] = retSelected;
    }
  }
  if(selectDifficulty -> isExpanded()){
    retSelected = this -> checkClickedExpandedDropDown(mousePressX, mousePressY, selectDifficulty);
    if(retSelected != -1){
      selectedDropDown[0] = 2;
      selectedDropDown[1] = retSelected;
    }
  }
  else{

    retSelected = this -> checkClickedSingleDropDown(mousePressX, mousePressY, selectDifficulty);
    if(retSelected != -1){
      selectedDropDown[0] = 2;
      selectedDropDown[1] = retSelected;
    }
  }
  return selectedDropDown;
}

int MousePress::checkClickedExpandedDropDown(int mousePressX, int mousePressY, DropDown *dropDown){
  int numOptions = dropDown -> getNumOptions();

  //check all the options in the drop down list and return the index of the selected option
  for(int i = 0; i < numOptions; i++){
    if(dropDown -> isSelected(mousePressX, mousePressY, i)){
      return i;
    }
  }
  //return -1 if no options were clicked
  return -1;
}
int MousePress::checkClickedSingleDropDown(int mousePressX, int mousePressY, DropDown *dropDown){
  //get the currently selected drop down item so that the right
  //box can be checked being clicked
  int selectedDropDownOption = dropDown -> getSelectedItemIndex();

  //return the index of the option if it was clicked
  if(dropDown -> isSelected(mousePressX, mousePressY, selectedDropDownOption)){
    return selectedDropDownOption;
  }
  //retrun -1 if no options were chosen
  return -1;
}
