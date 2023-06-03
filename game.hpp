#pragma once
#include <string>
#include "board.hpp"
#define WHITE_PLAYER 'W'
#define BLACK_PLAYER 'B'

class Game
{
public:
  Game();
  Game(const Game &orig);
  Game(std::string gameString);
  bool validateGame();
  ~Game();

private:
  int triggerTreshold, whitePiecesReserve, whitePieces, blackPiecesReserve, blackPieces, board_size;
  char currentPlayer;
  Board board;
  void initGame(std::string gameString);
};
