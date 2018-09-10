#ifndef USERVIEW_H
#define USERVIEW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameLogic.hpp"

class UserView{
private:
  sf::RenderWindow *game;

  public:
    UserView(sf::RenderWindow &game);

    void updateUserView(int deltaMs);

    void drawUserPaddle();
};

#endif
