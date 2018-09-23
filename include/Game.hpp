#ifndef GAME_H
#define GAME_H
#include "../include/GameLogic.hpp"
#include "../include/UserView.hpp"
#include "../include/CompView.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <memory>

using std::cout;
using std::shared_ptr;
using std::unique_ptr;

class Game{
private:
  unique_ptr<GameLogic> gameLogic;
  unique_ptr<UserView> userView;
  unique_ptr<CompView> compView;
public:
  Game();

  void initGame(sf::RenderWindow &game);
  void updateGame(int deltaS, sf::RenderWindow  &game);


};
#endif
