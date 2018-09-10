#include "../include/KeyPress.hpp"
#include <iostream>

using std::cout;

KeyPress::KeyPress(){}

void KeyPress::processInput(){

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    cout << "s pressed";
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
    cout << "w pressed";
  }
}
