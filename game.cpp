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
    int wrongRows = validateRowsDoNotExceedTreshold();
    if (wrongRows)
    {
      std::cout << "ERROR_FOUND_" << wrongRows << "_ROW_OF_LENGTH_K" << std::endl;
    }
    else
    {
      return true;
    }
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
  return true;
}

void Game::doMove(std::string move)
{
  std::string from = move.substr(0, move.find("-"));
  std::string to = move.substr(move.find("-") + 1);
  std::vector<std::string> row = board.getRow(from, to);
  char currentPawn = currentPlayer;
  for (int i = 0; i < row.size() - 1; i++)
  {
    char removedPawn = board.getField(row[i]);
    board.setField(row[i], currentPawn);
    currentPawn = removedPawn;
    if (currentPawn == EMPTY)
    {
      break;
    }
  }
  std::cout << "MOVE_COMMITTED" << std::endl;
  if (currentPlayer == WHITE_PLAYER)
  {
    currentPlayer = BLACK_PLAYER;
    whitePiecesReserve--;
  }
  else
  {
    currentPlayer = WHITE_PLAYER;
    blackPiecesReserve--;
  }
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
  int index = std::stoi(field.substr(1)) - 1;

  int maxRow = board_size * 2 - 2;
  int maxIndex = board.correctRowLength(row);

  if (row < 0 || row > maxRow)
  {
    return false;
  }
  if (index <= 0 || index > maxIndex)
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

  int fromRow = from[0] - 'a';
  int fromIndex = std::stoi(from.substr(1)) - 1;
  int toRow = to[0] - 'a';
  int toIndex = std::stoi(to.substr(1)) - 1;

  if ((fromRow == 0 && fromIndex > 0) && (fromRow == (toRow - 1) && toIndex == fromIndex))
  {
    return true;
  }
  if ((fromRow == 0 && fromIndex == 0) && (fromRow == (toRow - 1) && toIndex == (fromIndex + 1)))
  {
    return true;
  }
  if (((fromRow > 0 && fromRow < (2 * board_size)) && fromIndex == 0) && (toRow == fromRow && toIndex == (fromIndex + 1)))
  {
    return true;
  }
  if ((fromRow == (2 * board_size) && fromIndex < board_size) && (toRow == (fromRow - 1) && toIndex == (fromIndex + 1)))
  {
    return true;
  }
  if ((fromRow == (2 * board_size) && fromIndex == board_size) && (toRow == (fromRow - 1) && toIndex == fromIndex))
  {
    return true;
  }
  if ((fromRow > 0 && fromRow < (2 * board_size)) && (fromIndex == (board.correctRowLength(fromRow - 1) + 1)) && (toRow == fromRow && toIndex == (fromIndex - 1)))
  {
    return true;
  }
  return false;
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
  std::vector<std::string> row = board.getRow(from, to);
  for (int i = 0; i < row.size(); i++)
  {
    if (board.getField(row[i]) == EMPTY)
    {
      return true;
    }
  }
  return false;
}

int Game::validateRowsDoNotExceedTreshold()
{
  std::vector<std::pair<std::string, std::string>> moves;
  std::string from, to;

  // Horizontal moves

  char firstRow = 'a';
  for (int i = 1; i <= board_size; i++)
  {
    from = std::string();
    to = std::string();
    from += firstRow;
    from += (i + '0');
    to += 'b';
    to += (i + 1 + '0');
    moves.push_back(std::make_pair(from, to));
  }
  char lastRow = 'a' + (board_size * 2);
  for (int i = 2; i <= board_size; i++)
  {
    from = std::string();
    to = std::string();
    from += lastRow;
    from += (i + '0');
    to += lastRow - 1;
    to += (i + '0');
    moves.push_back(std::make_pair(from, to));
  }

  // Diagonal moves leftbottom-righttop

  for (int i = 1; (firstRow + i) < lastRow; i++)
  {
    from = std::string();
    to = std::string();
    from += (firstRow + i);
    from += '1';
    to += (firstRow + i);
    to += ('2');
    moves.push_back(std::make_pair(from, to));
  }

  // Diagonal moves lefttop-rightbottom
  for (int i = 2; i <= board_size + 1; i++)
  {
    from = std::string();
    to = std::string();
    from += firstRow;
    from += (i + '0');
    to += (firstRow + 1);
    to += (i + '0');
    moves.push_back(std::make_pair(from, to));
  }
  for (int i = 2; i <= board_size; i++)
  {
    from = std::string();
    to = std::string();
    from += lastRow;
    from += (i + '0');
    to += (lastRow - 1);
    to += (i + 1 + '0');
    moves.push_back(std::make_pair(from, to));
  }

  int wrongRows = 0;
  for (int i = 0; i < moves.size(); i++)
  {
    std::pair<std::string, std::string> move = moves[i];
    std::vector<std::string> row = board.getRow(move.first, move.second);
    int blackCounter = 0, whiteCounter = 0;
    for (int j = 0; j < row.size(); j++)
    {
      if (board.getField(row[j]) == WHITE)
      {
        whiteCounter++;
        blackCounter = 0;
      }
      else if (board.getField(row[j]) == BLACK)
      {
        blackCounter++;
        whiteCounter = 0;
      }
      else
      {
        blackCounter = 0;
        whiteCounter = 0;
      }
    }
    if (whiteCounter >= triggerTreshold || blackCounter >= triggerTreshold)
    {
      wrongRows++;
    }
  }

  return wrongRows;
}
