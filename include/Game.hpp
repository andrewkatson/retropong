#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void initGame(sf::RenderWindow &game);
void updateGame(int deltaMs);
void shutdownGame();

#endif
