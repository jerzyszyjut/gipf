#pragma once
#include <string>
#include <vector>

#define WHITE 'W'
#define BLACK 'B'
#define EMPTY ' '

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
  int correctRowLength(int row);
  void setField(std::string field, char piece);
  char getField(std::string field);

private:
  int size;
  std::vector<std::vector<char>> board;
  std::vector<std::vector<std::string>> fieldNames;
  void initBoard(std::string boardString);
};
