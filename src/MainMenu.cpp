#include "MainMenu.hpp"


MainMenu::MainMenu(int windowX,  int windowY){
  this -> setWindowSize(windowX, windowY);

}

void MainMenu::setWindowSize(int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  //when window resizes we want to update the dimensions of the buttons
  this -> initPlayButton();
  this -> initOptionsMenuButton();
}

void MainMenu::initPlayButton(){
  (this -> playButton).setString("Play");

  (this -> playButton).setCharacterSize(this -> windowX / 16);

  (this -> playButton).setPosition((this -> windowX/4), (this -> windowY / 6)*2);
}

void MainMenu::initOptionsMenuButton(){
  (this -> optionsMenuButton).setString("Options");

  (this -> optionsMenuButton).setCharacterSize(this -> windowX / 16);

  (this -> optionsMenuButton).setPosition((this -> windowX/4), (this -> windowY / 6)*3);
}

int MainMenu::getPlayButtonCharSize(){
  return this -> windowX / 16;
}
int MainMenu::getOptionMenuButtonCharSize(){
  return this ->  windowX / 16;
}

sf::FloatRect MainMenu::getPlayButtonGlobalBounds(){
  return (this -> playButton).getGlobalBounds();
}

sf::FloatRect MainMenu::getOptionsMenuButtonGlobalBounds(){
  return (this -> optionsMenuButton).getGlobalBounds();
}
