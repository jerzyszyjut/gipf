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
  currentPlayer = second_line[0];
}

void Game::printGame()
{
  if (board.empty())
  {
    std::cout << "EMPTY_BOARD" << std::endl;
    return;
  }
  std::cout << board_size << " " << triggerTreshold << " " << whitePieces << " " << blackPieces << std::endl;
  std::cout << whitePiecesReserve << " " << blackPiecesReserve << " " << currentPlayer << std::endl;
  board.printBoard();
}

bool Game::validateMove(std::string move)
{
  std::string from = move.substr(0, move.find("-"));
  std::string to = move.substr(move.find("-") + 1);
  if (!validateFieldIsInBounds(from))
  {
    std::cout << "BAD_MOVE_" << from << "_IS_WRONG_INDEX" << std::endl;
    return false;
  }
  if (!validateFieldIsInBounds(to))
  {
    std::cout << "BAD_MOVE_" << to << "_IS_WRONG_INDEX" << std::endl;
    return false;
  }
  if (!validateFieldIsCorrectStartingField(from))
  {
    std::cout << "BAD_MOVE_" << from << "_IS_WRONG_STARTING_FIELD" << std::endl;
    return false;
  }
  if (!validateFieldIsCorrectEndingField(to))
  {
    std::cout << "BAD_MOVE_" << to << "_IS_WRONG_DESTINATION_FIELD" << std::endl;
    return false;
  }
  if (!validateFieldsAreInOneDiagonal(from, to))
  {
    std::cout << "UNKNOWN_MOVE_DIRECTION" << std::endl;
    return false;
  }
  if (!validateMoveRowIsNotFull(from, to))
  {
    std::cout << "BAD_MOVE_ROW_IS_FULL" << std::endl;
    return false;
  }
  std::cout << "MOVE_COMMITED" << std::endl;
  return true;
}

bool Game::validateFieldIsInBounds(std::string field)
{
  int row = field[0] - 'a' - 1;
  int index = std::stoi(field.substr(1)) - 1;

  int maxRow = board_size * 2 - 1;
  int maxIndex = board.correctRowLength(row) + 1;

  if (row < -1 || row > maxRow)
  {
    return false;
  }
  if (index < -1 || index > maxIndex)
  {
    return false;
  }

  return true;
}

bool Game::validateFieldIsInGameBounds(std::string field)
{
  int row = field[0] - 'a' - 1;
  int index = std::stoi(field.substr(1)) - 2;

  int maxRow = board_size * 2 - 2;
  int maxIndex = board.correctRowLength(row) + 1;

  if (row < 0 || row > maxRow)
  {
    return false;
  }
  if (index < 0 || index > maxIndex)
  {
    return false;
  }
  return true;
}

bool Game::validateFieldsAreInOneDiagonal(std::string from, std::string to)
{
  if (!validateFieldIsInGameBounds(to))
  {
    return false;
  }

  int fromRow = from[0] - 'a' - 1;
  int fromIndex = std::stoi(from.substr(1)) - 1;
  int toRow = to[0] - 'a' - 1;
  int toIndex = std::stoi(to.substr(1)) - 1;

  int rowDiff = toRow - fromRow;
  int indexDiff = toIndex - fromIndex;
  int diff = abs(rowDiff) + abs(indexDiff);
  if (diff != 2 && diff != 0)
  {
    return false;
  }

  return true;
}

bool Game::validateFieldIsCorrectStartingField(std::string field)
{
  return validateFieldIsInBounds(field) && !validateFieldIsInGameBounds(field);
}

bool Game::validateFieldIsCorrectEndingField(std::string field)
{
  return validateFieldIsInGameBounds(field);
}

bool Game::validateMoveRowIsNotFull(std::string from, std::string to)
{
}
