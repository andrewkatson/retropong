#ifndef USERVIEW_H
#define USERVIEW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Paddle.hpp"
#include <memory>

using std::shared_ptr;

class UserView{
private:
  Paddle *userPaddle;
  Paddle *compPaddle;
  public:
    UserView(Paddle *userPaddle, Paddle *compPaddle);

    void updateUserView(int deltaMs, sf::RenderWindow &game);
    void drawUserPaddle(sf::RenderWindow &game);
    void drawCompPaddle(sf::RenderWindow &game);
};

#endif
