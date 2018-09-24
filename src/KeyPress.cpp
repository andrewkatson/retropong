#include "KeyPress.hpp"
#include <iostream>

using std::cout;

KeyPress::KeyPress(){}

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
}
