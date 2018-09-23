#ifndef USERVIEW_H
#define USERVIEW_H

#include "Paddle.hpp"
#include "Ball.hpp"
#include "GameLogic.hpp"
#include "KeyPress.hpp"
#include "MousePress.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <thread>

using std::string;
using std::to_string;
using std::shared_ptr;
using std::thread;

class UserView{
private:
  GameLogic *gameLogic;
  int windowX;
  int windowY;
  sf::Font mainFont;
  sf::Text userScoreText;
  sf::Text compScoreText;
  sf::Text pauseText;
  sf::Text restartText;
  sf::Text mainMenuText;
  sf::Text playGameText;
  sf::Text optionsMenuSelectText;

public:
    UserView(GameLogic *gameLogic);
    ~UserView();
    void loadFont();

    void updateUserView(int deltaS, sf::RenderWindow &game);
    void processEvents(sf::RenderWindow &game);

    void drawMainMenuTitle(sf::RenderWindow &game);
    void drawSelectPlayMessageText(sf::RenderWindow &game);
    void drawSelectOptionsMenuText(sf::RenderWindow &game);
    void drawUserPaddle(sf::RenderWindow &game);
    void drawCompPaddle(sf::RenderWindow &game);
    void drawBall(sf::RenderWindow &game);
    void drawText(sf::RenderWindow &game);
    void drawPauseMessage(sf::RenderWindow &game);
    void drawScoreBoard(sf::RenderWindow &game);
    void drawComputerScore(sf::RenderWindow &game);
    void drawUserScore(sf::RenderWindow &game);
    void drawSideBorders(sf::RenderWindow &game);
    void drawTopBorder(sf::RenderWindow &game);
    void drawBottomBorder(sf::RenderWindow &game);
    void drawGoalBorders(sf::RenderWindow &game);
    void drawUserGoal(sf::RenderWindow &game);
    void drawCompGoal(sf::RenderWindow &game);
    void drawEndGameMessage(sf::RenderWindow &game);

    string getWinnerString();

    void keyPressed(sf::Event event, sf::RenderWindow &game);
    void mousePressed(sf::Event event, sf::RenderWindow &game);
};

#endif
