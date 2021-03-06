#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class ScoreBoard {
private:
  int userScore;
  int compScore;
  int winningScore;
public:
  enum Side{
    player, comp, neither
  };

  ScoreBoard(int winningScore);

  void reset();
  void incrementUserScore();
  void incrementCompScore();
  Side hasWon();

  int getUserScore();
  int getCompScore();
};

#endif
