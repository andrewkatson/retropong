#ifndef COMPVIEW_H
#define COMPVIEW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameLogic.hpp"

class CompView{
private:
sf::RenderWindow *game;

public:
  CompView(sf::RenderWindow &game);

  void updateCompView(int deltaMs);

};

#endif
