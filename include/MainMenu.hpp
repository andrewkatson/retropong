#ifndef MAINMENU_H
#define MAINMENU_H
#include <SFML/Graphics.hpp>
class MainMenu{
private:
  sf::Text playButton;
  sf::Text optionsMenuButton;
  sf::Text quitButton;
  int windowX;
  int windowY;

public:
  MainMenu(int windowX, int windowY);

  void setWindowSize(int windowX, int windowY);
  void initPlayButton();
  void initOptionsMenuButton();
  void initQuitButton();

  int getPlayButtonCharSize();
  int getOptionMenuButtonCharSize();
  int getQuitButtonCharSize();

  sf::FloatRect getPlayButtonGlobalBounds();
  sf::FloatRect getOptionsMenuButtonGlobalBounds();
  sf::FloatRect getQuitButtonGlobalBounds();
};

#endif
