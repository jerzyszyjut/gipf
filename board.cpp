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
    for (int j = 0; j < row.size(); j++)
    {
      if (j < spaces ||
          j >= (row.size() - spaces))
      {
        std::cout << " ";
      }
      else
      {
        if (row[j] == NULL)
        {
          std::cout << "_";
        }
        else
        {
          std::cout << row[j];
        }
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
}

int Board::getWhitePiecesCount()
{
  int counter = 0;
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[i].size(); j++)
    {
      if (board[i][j] == WHITE)
        counter++;
    }
  }
  return counter;
}

int Board::getBlackPiecesCount()
{
  int counter = 0;
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[i].size(); j++)
    {
      if (board[i][j] == BLACK)
        counter++;
    }
  }
  return counter;
}

bool Board::verifyRowsLengths()
{
  int correctLength = size * 2 - 1;
  if (board.size() != correctLength)
  {
    return false;
  }
  for (int i = 0; i < board.size(); i++)
  {
    if (board[i].size() != correctLength)
    {
      return false;
    }
  }
  return true;
}

void Board::initBoard(std::string boardString)
{
  int lineCount = 0;
  do
  {
    std::string line = boardString.substr(0, boardString.find("\n"));
    boardString = boardString.substr(boardString.find("\n") + 1);
    if (line[0] == '\r')
    {
      break;
    }

    std::vector<char> row;

    int spaces = abs(size - (lineCount + 1));
    for (int j = 0; j < spaces; j++)
    {
      row.push_back(NULL);
    }

    for (int i = 0; i < line.length(); i++)
    {
      if (line[i] > ' ')
      {
        if (line[i] == '_')
        {
          row.push_back(NULL);
        }
        else
        {
          row.push_back(line[i]);
        }
      }
    }
    board.push_back(row);
    lineCount++;
  } while (boardString.length() > 1);
}

Board::~Board()
{
}
