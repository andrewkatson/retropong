#include "ScoreBoard.hpp"


ScoreBoard::ScoreBoard(int winningScore){
  this -> winningScore = winningScore;
  this -> userScore = 0;
  this -> compScore = 0;
}

void ScoreBoard::incrementUserScore(){
  int userScore = this -> userScore + 1;

  this -> userScore = userScore;
}

void ScoreBoard::incrementCompScore(){
  int compScore = this -> compScore + 1;

  this -> compScore = compScore;
}

ScoreBoard::Side ScoreBoard::hasWon(){
  int winningScore = this -> winningScore;
  if(this -> userScore >= winningScore){
    return ScoreBoard::player;
  }
  else if(this -> compScore >= winningScore){
    return ScoreBoard::comp;
  }
  else{
    return ScoreBoard::neither;
  }
}

int ScoreBoard::getUserScore(){
  return this -> userScore;
}

int ScoreBoard::getCompScore(){
  return this -> compScore;
}
