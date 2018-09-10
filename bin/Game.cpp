#include "../include/Game.hpp"
#include "../include/KeyPress.hpp"
#include "../include/GameLogic.hpp"
#include "../include/UserView.hpp"
#include "../include/CompView.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>


int main(){

  //start game clock
  sf::Clock gameClock;

  // create main window
  sf::RenderWindow game(sf::VideoMode(800,600,32), "Pong");

  initGame(game);

  // start main loop
  while(game.isOpen())
  {
    processEvents(game);
    sf::Time timeDelta = gameClock.restart();
    int deltaMs = timeDelta.asMilliseconds();
    updateGame(deltaMs);

  }
  shutdownGame();
}


void initGame(sf::RenderWindow &game){
  // clear screen and fill with black
  game.clear(sf::Color::Black);

  // display
  game.display();
}

void processEvents(sf::RenderWindow &game){
  // process events
  sf::Event Event;
  while(game.pollEvent(Event))
  {
    // Exit
    if(Event.type == sf::Event::Closed)
      game.close();
    //Key Pressed
    else if(Event.type == sf::Event::KeyPressed){
      KeyPress *keyPress = new KeyPress();

      keyPress -> processInput();

    }
  }
}

void updateGame(int deltaMs){
  GameLogic *gameLogic = new GameLogic();
  UserView *userView = new UserView();
  CompView *compView = new CompView();


  gameLogic -> updateLogic(deltaMs);
  userView -> updateUserView(deltaMs);
  compView -> updateCompView(deltaMs);

}

void shutdownGame(){

}
