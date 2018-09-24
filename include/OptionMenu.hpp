#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include "DropDown.hpp"
#include "Button.hpp"
#include <memory>

using std::unique_ptr;

class OptionMenu{
private:

  vector<string> gameObjectNames = {"Computer Paddle", "User Paddle", "Ball",
                                "Top Border", "Bottom Border", "User Goal",
                                "Computer Goal"};
  vector<string> colorNames = {"White", "Red", "Green", "Blue", "Yellow",
                              "Magenta", "Cyan"};

  vector<string> difficultyNames = {"Easy", "Medium", "Hard"};
  unique_ptr<DropDown> selectGameObject;
  unique_ptr<DropDown> selectColor;
  unique_ptr<DropDown> selectDifficulty;
  unique_ptr<Button> backButton;
  int windowX;
  int windowY;
public:

  OptionMenu(int windowX, int windowY);

  void setWindowSize(int windowX, int windowY);

  DropDown * getSelectObjectDropDown();
  DropDown * getSelectColorDropDown();
  DropDown * getSelectDifficultyDropDown();
  Button * getBackButton();

  int getGameObjectSelected();
  int getSelectedDifficulty();
  int getColorIndexOfColor(sf::Color color);

};

#endif
