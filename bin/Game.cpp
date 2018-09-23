#include "Game.hpp"

int main(){

  //make a Game
  auto pongGame = unique_ptr<Game>(new Game());

  //start game clock
  sf::Clock gameClock;

  // create main window
  sf::RenderWindow game(sf::VideoMode(800,600,32), "Pong", sf::Style::Close);

  pongGame -> initGame(game);

  // start main loop
  while(game.isOpen())
  {
    sf::Time timeDelta = gameClock.restart();
    int deltaS = timeDelta.asMilliseconds();
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
  int winngScore = 1;

  //initialize the Game Logic
  this -> gameLogic = unique_ptr<GameLogic>(new GameLogic(windowX, windowY,
                                            winngScore));
  //initialize the User View
  this -> userView = unique_ptr<UserView>(new UserView((this -> gameLogic).get()));
  //initlaize the Computer View
  this -> compView = unique_ptr<CompView>(new CompView((this -> gameLogic).get(),
                                          CompView::easy));
}


void Game::updateGame(int deltaS, sf::RenderWindow  &game){

  this -> gameLogic -> updateLogic(deltaS);
  this -> userView -> updateUserView(deltaS, game);
  this -> compView -> updateCompView(deltaS);

}
