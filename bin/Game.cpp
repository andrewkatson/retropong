#include "Game.hpp"
#include <iostream>

int main(){
  //make a Game
  auto pongGame = unique_ptr<Game>(new Game());
;
  //start game clock
  sf::Clock gameClock;

  // create main window
  sf::RenderWindow game(sf::VideoMode(800,600,32), "Pong", sf::Style::Close);

  pongGame -> initGame(game);

  // start main loop
  while(game.isOpen())
  {
    sf::Time timeDelta = gameClock.restart();
    float deltaS = timeDelta.asSeconds() * 2000;
    //cout << "time " << deltaS << std::endl;
    pongGame -> updateGame(deltaS, game);

  }
}

Game::Game(){}


void Game::initGame(sf::RenderWindow  &game){
  // clear screen and fill with black
  game.clear(sf::Color::Black);

  // display
  game.display();

  //get the size of the render window
  sf::Vector2u windowSize = game.getSize();

  //dimensions of the window
  unsigned int windowX = windowSize.x;
  unsigned int windowY = windowSize.y;

  //The score to window
  int winngScore = 11;

  //initialize the Game Logic
  this -> gameLogic = unique_ptr<GameLogic>(new GameLogic(windowX, windowY,
                                            winngScore));
  //initialize the User View
  this -> userView = unique_ptr<UserView>(new UserView((this -> gameLogic).get()));
  //initlaize the Computer View
  this -> compView = unique_ptr<CompView>(new CompView((this -> gameLogic).get()));
}


void Game::updateGame(float deltaS, sf::RenderWindow  &game){
  //cout << "time in update " << deltaS << std::endl;
  this -> gameLogic -> updateLogic(deltaS);
  this -> userView -> updateUserView(game, deltaS);
  this -> compView -> updateCompView(deltaS);

}
