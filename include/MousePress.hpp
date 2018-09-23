#ifndef MOUSEPRESS_H
#define MOUSEPRESS_H
#include "GameLogic.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;

class MousePress{
public:
  MousePress();
  void processInput(sf::Event event, GameLogic *gameLogic, sf::RenderWindow &game);
  bool clickedPlayButton(sf::Event event, GameLogic *gameLogic);
  bool clickedOptionsButton(sf::Event event, GameLogic *gameLogic);

  bool mouseClickOnButton(int mousePressX, int mousePressY, int boundXDim,
                          int boundYDim, sf::FloatRect boundingBox);

  bool clickInRange(int mousePressPos, int boundPos, int boundDim);
};
#endif
