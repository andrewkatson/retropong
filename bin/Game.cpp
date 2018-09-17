#include "Game.hpp"
#include "KeyPress.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
using std::cout;
int main(){

  //make a Game
  auto pongGame = unique_ptr<Game>(new Game());

  //start game clock
  sf::Clock gameClock;

  // create main window
  sf::RenderWindow game(sf::VideoMode(800,600,32), "Pong");

  pongGame -> initGame(game);

  // start main loop
  while(game.isOpen())
  {
    sf::Time timeDelta = gameClock.restart();
    int deltaMs = timeDelta.asMilliseconds();
    pongGame -> updateGame(deltaMs, game);

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
  this -> compView = unique_ptr<CompView>(new CompView((this -> gameLogic).get(), CompView::easy));
}


void Game::updateGame(int deltaMs, sf::RenderWindow  &game){
  this -> processEvents(game);
  this -> gameLogic -> updateLogic(deltaMs);
  this -> userView -> updateUserView(deltaMs, game);
  this -> compView -> updateCompView(deltaMs);

}

void Game::processEvents(sf::RenderWindow  &game){
  // process events
  sf::Event Event;
  while(game.pollEvent(Event))
  {
    // Exit
    if(Event.type == sf::Event::Closed)
      this -> shutdownGame(game);
    //Key Pressed
    else if(Event.type == sf::Event::KeyPressed){
      auto keyPress = unique_ptr<KeyPress>(new KeyPress());
      keyPress -> processInput(Event, (this -> gameLogic).get());

    }
  }
}

void Game::shutdownGame(sf::RenderWindow  &game){
  game.close();
}
