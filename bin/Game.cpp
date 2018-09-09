#include "Game.hpp"
#include <SFML/System.hpp>

int main(){

  //start game clock
  sf::Clock gameClock;

  // create main window
  sf::RenderWindow game(sf::VideoMode(800,600,32), "Pong");

  initGame(game);

  // start main loop
  while(game.isOpen())
  {
    // process events
    sf::Event Event;
    while(game.pollEvent(Event))
    {
      // Exit
      if(Event.type == sf::Event::Closed)
        game.close();
    }

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

void updateGame(int deltaMs){



}

void shutdownGame(){

}
