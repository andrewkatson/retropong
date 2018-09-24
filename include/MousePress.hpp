#ifndef MOUSEPRESS_H
#define MOUSEPRESS_H
#include "GameLogic.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using std::cout;
using std::vector;

class MousePress{
public:
  MousePress();
  void processInput(sf::Event event, GameLogic *gameLogic, sf::RenderWindow &game);
  bool clickedPlayButton(sf::Event event, GameLogic *gameLogic);
  bool clickedOptionsButton(sf::Event event, GameLogic *gameLogic);
  bool clickedQuitButton(sf::Event event, GameLogic *gameLogic);
  bool clickedBackButton(sf::Event event, GameLogic *gameLogic);


  bool mouseClickOnButton(int mousePressX, int mousePressY, int boundXDim,
                          int boundYDim, sf::FloatRect &SboundingBox);

  bool clickInRange(int mousePressPos, int boundPos, int boundDim);

  vector<int> checkClickedDropDown(sf::Event event, GameLogic *gameLogic);
  int checkClickedExpandedDropDown(int mousePressX, int mousePressY, DropDown *dropDown);
  int checkClickedSingleDropDown(int mousePressX, int mousePressY, DropDown *dropDown);
};
#endif
