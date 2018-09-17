#ifndef USERVIEW_H
#define USERVIEW_H

#include "Paddle.hpp"
#include "Ball.hpp"
#include "GameLogic.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

using std::shared_ptr;

class UserView{
private:
  GameLogic *gameLogic;
  public:
    UserView(GameLogic *gameLogic);

    void updateUserView(int deltaMs, sf::RenderWindow &game);
    void drawUserPaddle(sf::RenderWindow &game);
    void drawCompPaddle(sf::RenderWindow &game);
    void drawBall(sf::RenderWindow &game);
};

#endif
