#include "KeyPress.hpp"
#include <iostream>

using std::cout;

KeyPress::KeyPress(){}

void KeyPress::processInput(sf::Event event, GameLogic *gameLogic, sf::RenderWindow &game){

  if(event.key.code == sf::Keyboard::S){
    gameLogic -> moveUserPaddleDown();
  }
  else if(event.key.code == sf::Keyboard::W){
    gameLogic -> moveUserPaddleUp();
  }
  else if(event.key.code == sf::Keyboard::Space){
    gameLogic -> unpauseBall();
    gameLogic -> unPauseGame();
  }
  else if(event.key.code == sf::Keyboard::R){
    if(gameLogic -> isGameEnded()){
      gameLogic -> restartGame();
    }
  }
  else if(event.key.code == sf::Keyboard::Q){
    game.close();
  }
}
