#ifndef KEYPRESS_H
#define KEYPRESS_H

#include "GameLogic.hpp"
#include <SFML/Window.hpp>
#include <memory>

using std::shared_ptr;

class KeyPress{

  public:
    KeyPress();
    void processInput(sf::Event event, GameLogic *gameLogic);
};

#endif
