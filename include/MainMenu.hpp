#ifndef MAINMENU_H
#define MAINMENU_H
#include <SFML/Graphics.hpp>
class MainMenu{
private:
  sf::Text playButton;
  sf::Text optionsMenuButton;
  int windowX;
  int windowY;

public:
  MainMenu(int windowX, int windowY);

  void setWindowSize(int windowX, int windowY);
  void initPlayButton();
  void initOptionsMenuButton();

  int getPlayButtonCharSize();
  int getOptionMenuButtonCharSize();

  sf::FloatRect getPlayButtonGlobalBounds();
  sf::FloatRect getOptionsMenuButtonGlobalBounds();
};

#endif
