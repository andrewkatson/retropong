#ifndef KEYPRESS_H
#define KEYPRESS_H

#include "GameLogic.hpp"
#include <SFML/Window.hpp>
#include <memory>


class KeyPress{

  public:
    KeyPress();
    void processInput(sf::Event event, GameLogic *gameLogic,
                      sf::RenderWindow &game, float deltaS);
};

#endif
