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
      if (row[j] == EMPTY)
      {
        std::cout << "_";
      }
      else
      {
        std::cout << row[j];
      }
      std::cout << " ";
    }
    for (int j = 0; j < spaces; j++)
    {
      std::cout << " ";
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
    if (board[i].size() != correctRowLength(i))
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

    for (int i = 0; i < line.length(); i++)
    {
      if (line[i] > ' ')
      {
        if (line[i] == '_')
        {
          row.push_back(EMPTY);
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

  char startingRow = 'b';
  int startingIndex = size + 1;

  for (int i = 0; i < board.size(); i++)
  {
    std::vector<std::string> row;
    for (int j = 0; j < board[i].size(); j++)
    {
      std::string field = "";
      field += startingRow + j;

      int maxAdd = size - 1;
      if (i > size - 1)
      {
        maxAdd = (size - 1) - (i - size + 1);
      }
      int add = j;
      if (add >= maxAdd)
      {
        add = maxAdd;
      }
      field += std::to_string(startingIndex + add);
      row.push_back(field);
    }
    fieldNames.push_back(row);
    if (i >= size - 1)
    {
      startingRow++;
    }
    if (i < size - 1)
    {
      startingIndex--;
    }
  }
}

bool Board::empty()
{
  return board.size() == 0;
}

Board::~Board()
{
}

int Board::correctRowLength(int row)
{
  return (2 * size - 1) - abs(size - (row + 1));
}

std::pair<int, int> Board::getFieldIndexes(std::string field)
{
  for (int i = 0; i < fieldNames.size(); i++)
  {
    for (int j = 0; j < fieldNames[i].size(); j++)
    {
      if (fieldNames[i][j] == field)
      {
        return std::make_pair(i, j);
      }
    }
  }
  return std::make_pair(-1, -1);
}

char Board::getField(std::string field)
{
  std::pair<int, int> indexes = getFieldIndexes(field);
  if (indexes.first == -1)
  {
    return NULL;
  }
  return board[indexes.first][indexes.second];
}

void Board::setField(std::string field, char piece)
{
  std::pair<int, int> indexes = getFieldIndexes(field);
  if (indexes.first == -1)
  {
    return;
  }
  board[indexes.first][indexes.second] = piece;
}

void Board::setField(char key, int index, char piece)
{
  std::string field = "";
  field += key;
  field += std::to_string(index);
  setField(field, piece);
}

std::vector<std::string> Board::getRow(std::string from, std::string to)
{
  char fromRow = from[0];
  int fromIndex = std::stoi(from.substr(1));
  char toRow = to[0];
  int toIndex = std::stoi(to.substr(1));

  std::vector<std::string> fields;

  int middleRow = size - 1;

  if (toRow == (fromRow + 1) && fromIndex == (toIndex - 1))
  {
    std::pair<int, int> indexes = getFieldIndexes(to);
    int x = indexes.first;
    for (int i = 0; i < board[x].size(); i++)
    {
      fields.push_back(fieldNames[x][i]);
    }
  }
  else if (fromRow == (toRow + 1) && fromIndex == toIndex)
  {
    std::pair<int, int> indexes = getFieldIndexes(to);
    int x = indexes.first;
    for (int i = board[x].size() - 1; i >= 0; i--)
    {
      fields.push_back(fieldNames[x][i]);
    }
  }
  else if (fromRow == (toRow - 1) && fromIndex == toIndex)
  {
    std::pair<int, int> indexes = getFieldIndexes(to);
    int x = indexes.first, y = indexes.second;
    for (int i = x; i < board.size(); i++)
    {
      fields.push_back(fieldNames[i][y]);
      if (i < middleRow)
      {
        y++;
      }
    }
  }
  else if (fromRow == (toRow + 1) && fromIndex == (toIndex - 1))
  {
    std::pair<int, int> indexes = getFieldIndexes(to);
    int x = indexes.first, y = indexes.second;
    for (int i = x; i >= 0; i--)
    {
      if (i < middleRow)
      {
        y--;
      }
      fields.push_back(fieldNames[i][y]);
    }
  }
  else if (fromRow == toRow && fromIndex == (toIndex - 1))
  {
    std::pair<int, int> indexes = getFieldIndexes(to);
    int x = indexes.first, y = indexes.second;
    for (int i = x; i >= 0; i--)
    {
      if (fieldNames[i].size() - 1 < y)
      {
        break;
      }
      fields.push_back(fieldNames[i][y]);
      if (i > middleRow)
      {
        y++;
      }
    }
  }
  else if (fromRow == toRow && fromIndex == (toIndex + 1))
  {
    std::pair<int, int> indexes = getFieldIndexes(to);
    int x = indexes.first, y = indexes.second;
    for (int i = x; i < board.size(); i++)
    {
      if (i > middleRow)
      {
        y--;
      }
      fields.push_back(fieldNames[i][y]);
    }
  }

  return fields;
}