#include "game.hpp"
#include <iostream>

Game::Game()
{
  triggerTreshold = 0;
  whitePieces = 0;
  whitePiecesReserve = 0;
  blackPieces = 0;
  blackPiecesReserve = 0;
}

Game::Game(const Game &orig)
{
  triggerTreshold = orig.triggerTreshold;
  whitePieces = orig.whitePieces;
  whitePiecesReserve = orig.whitePiecesReserve;
  blackPieces = orig.blackPieces;
  blackPiecesReserve = orig.blackPiecesReserve;
  board = orig.board;
}

Game::Game(std::string gameString)
{
  initGame(gameString);
  gameString = gameString.substr(gameString.find("\n") + 1);
  gameString = gameString.substr(gameString.find("\n") + 1);
  if (gameString[gameString.length() - 2] == '\n')
  {
    gameString = gameString.substr(0, gameString.length() - 1);
  }
  board = Board(gameString, board_size);
  bool isGameValid = validateGame();
  if (isGameValid)
  {
    std::cout << "BOARD_STATE_OK" << std::endl;
  }
  else
  {
    board = Board();
  }
}

bool Game::validateGame()
{
  int correctWhitePieces = whitePieces - whitePiecesReserve;
  int correctBlackPieces = blackPieces - blackPiecesReserve;
  if (!board.verifyRowsLengths())
  {
    std::cout << "WRONG_BOARD_ROW_LENGTH" << std::endl;
  }
  else if (correctWhitePieces < board.getWhitePiecesCount())
  {
    std::cout << "WRONG_WHITE_PAWNS_NUMBER" << std::endl;
  }
  else if (correctBlackPieces < board.getBlackPiecesCount())
  {
    std::cout << "WRONG_BLACK_PAWNS_NUMBER" << std::endl;
  }
  else
  {
    return true;
  }
  return false;
}

Game::~Game()
{
}

void Game::initGame(std::string gameString)
{
  std::string first_line = gameString.substr(0, gameString.find("\n"));
  std::string second_line = gameString.substr(gameString.find("\n") + 1, gameString.find("\n"));

  board_size = std::stoi(first_line.substr(0, first_line.find(" ")));
  first_line = first_line.substr(first_line.find(" ") + 1);
  triggerTreshold = std::stoi(first_line.substr(0, first_line.find(" ")));
  first_line = first_line.substr(first_line.find(" ") + 1);
  whitePieces = std::stoi(first_line.substr(0, first_line.find(" ")));
  first_line = first_line.substr(first_line.find(" ") + 1);
  blackPieces = std::stoi(first_line.substr(0, first_line.find(" ")));
  first_line = first_line.substr(first_line.find(" ") + 1);

  whitePiecesReserve = std::stoi(second_line.substr(0, second_line.find(" ")).c_str());
  second_line = second_line.substr(second_line.find(" ") + 1);
  blackPiecesReserve = std::stoi(second_line.substr(0, second_line.find(" ")).c_str());
  second_line = second_line.substr(second_line.find(" ") + 1);
  currentPlayer = second_line[second_line.find(" ") + 1];
}
