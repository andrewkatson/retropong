#ifndef KEYPRESS_H
#define KEYPRESS_H

#include "GameLogic.hpp"
#include <SFML/Window.hpp>
#include <memory>


class KeyPress{
private:
  int currentKonamiKeyPress;
  int lastKonamiKeyPress;
  public:
    KeyPress();
    void processInput(sf::Event event, GameLogic *gameLogic,
                      sf::RenderWindow &game, float deltaS);

    bool checkKonamiCode(sf::Event event, GameLogic *gameLogic);
};

#endif
