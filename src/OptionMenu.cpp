#include "OptionMenu.hpp"

OptionMenu::OptionMenu(int windowX, int windowY){

  this -> selectGameObject = unique_ptr<DropDown>(new DropDown(7, &this -> gameObjectNames, windowX, windowY, 0));
  this -> selectColor = unique_ptr<DropDown>(new DropDown(7, &this -> colorNames, windowX, windowY, 1));
  this -> selectDifficulty = unique_ptr<DropDown>(new DropDown(3, &this -> difficultyNames, windowX, windowY, 2));
  this -> setWindowSize(windowX, windowY);

}

void OptionMenu::setWindowSize(int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> selectGameObject -> setWindowSize(windowX, windowY);
  this -> selectColor -> setWindowSize(windowX, windowY);
  this -> selectDifficulty -> setWindowSize(windowX, windowY);
}

DropDown * OptionMenu::getSelectObjectDropDown(){
  return (this -> selectGameObject).get();
}
DropDown * OptionMenu::getSelectColorDropDown(){
  return (this -> selectColor).get();
}
DropDown * OptionMenu::getSelectDifficultyDropDown(){
  return (this -> selectDifficulty).get();
}

int OptionMenu::getGameObjectSelected(){
  return this -> selectGameObject -> getSelectedItemIndex();
}
int OptionMenu::getSelectedDifficulty(){
  return this -> selectDifficulty -> getSelectedItemIndex();
}
int OptionMenu::getColorIndexOfColor(sf::Color color){
  if(color == sf::Color::White)
      return 0;
  else if(color == sf::Color::Red)
      return 1;
  else if(color == sf::Color::Green)
      return 2;
  else if(color == sf::Color::Blue)
      return 3;
  else if(color == sf::Color::Yellow)
      return 4;
  else if(color == sf::Color::Magenta)
      return 5;
  else if(color == sf::Color::Cyan)
      return 6;
}
