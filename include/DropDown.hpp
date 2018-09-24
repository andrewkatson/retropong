#ifndef DROPDOWN_H
#define DROPDOWN_H

#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::vector;
using std::string;

class DropDown{
private:
  int numOptions;
  int currSelectedOptionIndex;
  int windowX;
  int windowY;
  int col;
  int longestOptionText;
  bool expandList;
  vector<sf::RectangleShape> optionsRects;
  vector<sf::Text> optionsTexts;

public:
  DropDown(int numOptions, vector<string> *optionsText, int windowX,
          int windowY, int col);

  void initOptionsText(vector<string> *optionsText);
  void initOptionsRects(vector<sf::Text> &optionsText);

  void selectOption(int index);
  void flipExpandList();

  bool isExpanded();

  int setWindowSize(int windowX, int windowY);

  void scaleOptions();
  void fixOutlines();

  int getSelectedItemIndex();
  int getNumOptions();
  vector<sf::RectangleShape> & getOptionsRects();
  vector<sf::Text> & getOptionsTexts();
  sf::RectangleShape & getSelectedOptionRect(int index);
  sf::Text & getSelectedOptionText(int index);
  bool isSelected(int mousePressX, int mousePressY, int index);
  bool clickInRange(int xPos, int yPos, sf::RectangleShape &optionRect);

  int getCharSize();

  string getSelectedItemString();

  sf::FloatRect getGlobalBounds(int index);

};

#endif
