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
  this -> initQuitButton();
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

void MainMenu::initQuitButton(){
  (this -> quitButton).setString("Options");

  (this -> quitButton).setCharacterSize(this -> windowX / 16);

  (this -> quitButton).setPosition((this -> windowX/4), (this -> windowY / 6)*4);
}

int MainMenu::getPlayButtonCharSize(){
  return this -> windowX / 16;
}
int MainMenu::getOptionMenuButtonCharSize(){
  return this ->  windowX / 16;
}
int MainMenu::getQuitButtonCharSize(){
  return this -> windowX / 16;
}

sf::FloatRect MainMenu::getPlayButtonGlobalBounds(){
  return (this -> playButton).getGlobalBounds();
}

sf::FloatRect MainMenu::getOptionsMenuButtonGlobalBounds(){
  return (this -> optionsMenuButton).getGlobalBounds();
}
sf::FloatRect MainMenu::getQuitButtonGlobalBounds(){
  return (this -> quitButton).getGlobalBounds();
}
