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
  void printGame();
  bool validateMove(std::string move);
  void doMove(std::string move);
  ~Game();

private:
  int triggerTreshold, whitePiecesReserve, whitePieces, blackPiecesReserve, blackPieces, board_size;
  char currentPlayer;
  Board board;
  void initGame(std::string gameString);
  bool validateFieldIsInBounds(std::string field);
  bool validateFieldIsInGameBounds(std::string field);
  bool validateFieldsAreInOneDiagonal(std::string from, std::string to);
  bool validateFieldIsCorrectStartingField(std::string field);
  bool validateFieldIsCorrectEndingField(std::string field);
  bool validateMoveRowIsNotFull(std::string from, std::string to);
};
