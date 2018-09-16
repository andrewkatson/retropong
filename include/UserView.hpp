#ifndef USERVIEW_H
#define USERVIEW_H

#include "Paddle.hpp"
#include "Ball.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

using std::shared_ptr;

class UserView{
private:
  Paddle *userPaddle;
  Paddle *compPaddle;
  Ball *ball;
  public:
    UserView(Paddle *userPaddle, Paddle *compPaddle, Ball *ball);

    void updateUserView(int deltaMs, sf::RenderWindow &game);
    void drawUserPaddle(sf::RenderWindow &game);
    void drawCompPaddle(sf::RenderWindow &game);
    void drawBall(sf::RenderWindow &game);
};

#endif
