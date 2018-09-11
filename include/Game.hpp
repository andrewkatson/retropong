#ifndef GAME_H
#define GAME_H
#include "../include/GameLogic.hpp"
#include "../include/UserView.hpp"
#include "../include/CompView.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>

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
  void updateGame(int deltaMs, sf::RenderWindow  &game);
  void processEvents(sf::RenderWindow  &game);
  void shutdownGame(sf::RenderWindow  &game);

};
#endif
