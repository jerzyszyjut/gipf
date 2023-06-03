#pragma once
#include <string>
#include <vector>

enum PieceType
{
  EMPTY = ' ',
  WHITE = 'W',
  BLACK = 'B'
};

class Board
{
public:
  Board();
  Board(const Board &orig);
  Board(std::string boardString, int size);
  ~Board();
  void printBoard();
  int getWhitePiecesCount();
  int getBlackPiecesCount();
  bool verifyRowsLengths();
  bool empty();

private:
  int size;
  std::vector<std::vector<char>> board;
  void initBoard(std::string boardString);
  int correctRowLength(int row);
};
