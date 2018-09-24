#include "DropDown.hpp"


DropDown::DropDown(int numOptions, vector<string> *optionsText, int windowX,
                  int windowY, int col) : optionsRects(15), optionsTexts(15){

  this -> numOptions = numOptions;
  this -> currSelectedOptionIndex = 0;
  //the column these will be placed in to allow more drop downs
  this -> col = col;
  this -> expandList = false;
  this -> longestOptionText = 0;
  this -> initOptionsText(optionsText);
  this -> initOptionsRects(this -> optionsTexts);
  this -> setWindowSize(windowX, windowY);

}

//make a sf::Text object for each string for the options
void DropDown::initOptionsText(vector<string> *optionsText){

  for (int i = 0; i < this -> numOptions; i++){

    if((optionsText -> at(i)).length() > this -> longestOptionText){
      this -> longestOptionText = (optionsText -> at(i)).length();
    }
    (this -> optionsTexts)[i].setString(optionsText -> at(i));
  }
}

//make sf::RectangleShape for each of the options
void DropDown::initOptionsRects(vector<sf::Text> &optionsText){
  for(int i = 0; i < this -> numOptions; i++){
    (this -> optionsRects)[i].setFillColor(sf::Color::Transparent);
    if(i == this -> currSelectedOptionIndex){
      (this -> optionsRects)[i].setOutlineColor(sf::Color::Green);
      (this -> optionsRects)[i].setOutlineThickness(5.0);
    }
    else{
      (this -> optionsRects)[i].setOutlineColor(sf::Color::White);
      (this -> optionsRects)[i].setOutlineThickness(2.0);
    }
  }
  //all size and position setup handled in scale function
  this -> scaleOptions();
}

void DropDown::selectOption(int index){
  this -> currSelectedOptionIndex = index;
}

//change whether the list is expanded or not
void DropDown::flipExpandList(){
  this -> expandList = (this -> expandList) ? false : true;
}

bool DropDown::isExpanded(){
  return this -> expandList;
}

int DropDown::setWindowSize(int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> scaleOptions();
}

//scale the sf::Text for each option and the associated rectangle surrounding it
void DropDown::scaleOptions(){

  for(int i = 0; i < this -> numOptions; i++){
    (this -> optionsTexts)[i].setCharacterSize(this -> windowX / 30);

    (this -> optionsTexts)[i].setPosition((this -> windowX/3)*this->col + (this -> windowX / 12) * this -> col + 25,
                                          (this -> windowY / this -> numOptions)*i);

    //the amount of characters for the longest option in this drop down is the basis
    // for all the rectangles
    int charNums = this -> longestOptionText;


    //shift the dimensions and position of the surrounding recntangle to the left
    // and above the text for the option
    int xPos = (this -> windowX/3)*this->col + (this -> windowX / 12) * this -> col + 10;
    int yPos = (this -> windowY / this -> numOptions)*i;
    int xDim =  (this -> windowX / 30) * charNums / 1.25;
    int yDim =  (this -> windowY / 30) * 2;

    (this -> optionsRects)[i].setPosition(xPos, yPos);
    (this -> optionsRects)[i].setSize(sf::Vector2f(xDim, yDim));

  }
}

//we only want the selected option to have a thicker
//outline with green color
void DropDown::fixOutlines(){
  int selectedOption = this -> currSelectedOptionIndex;
  for(int i = 0; i < this -> numOptions; i++){
    if(i != selectedOption){
      (this -> optionsRects)[i].setOutlineColor(sf::Color::White);
      (this -> optionsRects)[i].setOutlineThickness(2);
    }
    else{
      (this -> optionsRects)[i].setOutlineColor(sf::Color::Green);
      (this -> optionsRects)[i].setOutlineThickness(5);
    }
  }
}

int DropDown::getSelectedItemIndex(){
  return this -> currSelectedOptionIndex;
}

int DropDown::getNumOptions(){
  return this -> numOptions;
}

vector<sf::RectangleShape> & DropDown::getOptionsRects(){
  return (this -> optionsRects);
}
vector<sf::Text> & DropDown::getOptionsTexts(){
  return (this -> optionsTexts);
}

sf::RectangleShape & DropDown::getSelectedOptionRect(int index){
  return (this -> optionsRects)[index];
}
sf::Text & DropDown::getSelectedOptionText(int index){
  return (this -> optionsTexts)[index];
}

bool DropDown::isSelected(int mousePressX, int mousePressY, int index){

  if(this -> clickInRange(mousePressX, mousePressY, (this -> optionsRects)[index])){
       return true;
  }
  return false;
}

bool DropDown::clickInRange(int xPos, int yPos, sf::RectangleShape &optionRect){
  sf::Vector2f positionOfRect = optionRect.getPosition();
  sf::Vector2f sizeOfRect = optionRect.getSize();

  int yPosRect;
  //if the current option being selected is at
  //the top of a list and the list is not expanded
  //we should check at the top for it being selected
  //we know that no other options get checked
  if(!expandList){
    yPosRect  = 0;
  }
  else{
    yPosRect  = positionOfRect.y;
  }
  int xPosRect  = positionOfRect.x;
  int xDimRect  = sizeOfRect.x;
  int yDimRect  = sizeOfRect.y;

  if(xPos >= xPosRect && xPos <= xPosRect + xDimRect){
    if(yPos >= yPosRect && yPos <= yPosRect + yDimRect){
      return true;
    }
  }
  return false;
}

int DropDown::getCharSize(){
  return this -> windowX / 30;
}

string DropDown::getSelectedItemString(){
  sf::Text text = this -> optionsTexts[this -> currSelectedOptionIndex];
  string textString = text.getString();
  return textString;
}

sf::FloatRect DropDown::getGlobalBounds(int index){
  return ((this -> optionsTexts)[index]).getGlobalBounds();
}
