#include "board.hpp"
#include <string>
#include <iostream>
#include <cmath>

Board::Board()
{
  size = 2;
}

Board::Board(const Board &orig)
{
  size = orig.size;
  board = orig.board;
}

Board::Board(std::string boardString, int size) : size(size)
{
  initBoard(boardString);
}

void Board::printBoard()
{
  for (int i = 0; i < (size * 2 - 1); i++)
  {
    std::vector<char> row = board[i];
    int spaces = abs(size - (i + 1));
    for (int j = 0; j < spaces; j++)
    {
      std::cout << " ";
    }
    for (int j = 0; j < row.size(); j++)
    {
      std::cout << row[j] << " ";
    }
    std::cout << std::endl;
  }
}

void Board::initBoard(std::string boardString)
{

  // Board is hexagonal, so the number of rows is 2 * size - 1
  /* Example:
   W _ _ B
  _ _ _ _ _
 _ _ W _ _ _
B _ _ _ _ _ W
 _ W _ W _ _
  _ _ _ _ _
   W _ _ B
  */
  do
  {
    std::string line = boardString.substr(0, boardString.find("\n"));
    boardString = boardString.substr(boardString.find("\n") + 1);
    std::vector<char> row;
    for (int i = 0; i < line.length(); i++)
    {
      if (line[i] > ' ')
      {
        row.push_back(line[i]);
      }
    }
    board.push_back(row);
  } while (boardString.length() > 1);
}

Board::~Board()
{
}
