#include "KeyPress.hpp"
#include <iostream>

using std::cout;

KeyPress::KeyPress(){
  this -> currentKonamiKeyPress = 0;
  this -> lastKonamiKeyPress = 9;
}

void KeyPress::processInput(sf::Event event, GameLogic *gameLogic,
                            sf::RenderWindow &game, float deltaS){

  if(event.key.code == sf::Keyboard::S){
    gameLogic -> moveUserPaddleDown(deltaS);
  }
  else if(event.key.code == sf::Keyboard::W){
    gameLogic -> moveUserPaddleUp(deltaS);
  }
  else if(event.key.code == sf::Keyboard::Space){
    if(!(gameLogic -> isGameEnded())){
      gameLogic -> unpauseBall();
      gameLogic -> unPauseGame();
    }
  }
  else if(event.key.code == sf::Keyboard::R){
    if(gameLogic -> isGameEnded()){
      gameLogic -> restartGame();
    }
  }
  else if(event.key.code == sf::Keyboard::Q){
    if(gameLogic -> isGameEnded()){
      game.close();
    }
  }
  //if you enter in a non standard key on the main menu
  //it checks for the konami code
  else{
    if(gameLogic -> isMainMenuOn()){
      //if we have already typed in the konami code leave
      if(this -> currentKonamiKeyPress > this -> lastKonamiKeyPress){
        return;
      }

      bool konamiSwitch = this -> checkKonamiCode(event, gameLogic);
      if(konamiSwitch){
        this -> currentKonamiKeyPress++;
        //only enable if we have pressed the final key in the sequence
        if(this -> currentKonamiKeyPress == this -> lastKonamiKeyPress){
          gameLogic -> enableKonamiCode();
        }
      }
      else{
        gameLogic -> disableKonamiCode();
        //if you did not enter it then you reset the sequence
        //of keys needed to complete the code
        this -> currentKonamiKeyPress = 0;
      }
    }
  }
}
//return whether the konami code has been entereds
bool KeyPress::checkKonamiCode(sf::Event event, GameLogic *gameLogic){

  switch(this -> currentKonamiKeyPress){
    case 0:
      if(event.key.code == sf::Keyboard::Up){
        return true;
      }
      else{
        return false;
      }
    case 1:
      if(event.key.code == sf::Keyboard::Up){
        return true;
      }
      else{
        return false;
      }
    case 2:
      if(event.key.code == sf::Keyboard::Down){
        return true;
      }
      else{
        return false;
      }
    case 3:
      if(event.key.code == sf::Keyboard::Down){
        return true;
      }
      else{
        return false;
      }
    case 4:
      if(event.key.code == sf::Keyboard::Left){
        return true;
      }
      else{
        return false;
      }
    case 5:
      if(event.key.code == sf::Keyboard::Right){
        return true;
      }
      else{
        return false;
      }
    case 6:
      if(event.key.code == sf::Keyboard::Left){
        return true;
      }
      else{
        return false;
      }
    case 7:
      if(event.key.code == sf::Keyboard::Right){
        return true;
      }
      else{
        return false;
      }
    case 8:
      if(event.key.code == sf::Keyboard::B){
        return true;
      }
      else{
        return false;
      }
    case 9:
      if(event.key.code == sf::Keyboard::A){
        return true;
      }
      else{
        return false;
      }
  }
}
