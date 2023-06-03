#include <iostream>
#include "controller.hpp"
#include "game.hpp"

Controller::Controller()
{
}

void Controller::run()
{
  while (!std::cin.eof())
  {
    std::string command;
    std::cin >> command;
    executeCommand(command);
  }
}

void Controller::executeCommand(std::string command)
{
  if (command == "LOAD_GAME_BOARD")
  {
    loadGame();
  }
  else if (command == "PRINT_GAME_BOARD")
  {
    printGame();
  }
  else if (command == "DO_MOVE")
  {
    std::string move;
    std::cin >> move;
    if (game.validateMove(move))
    {
      game.doMove(move);
    }
  }
  std::cout << std::endl;
}

void Controller::loadGame()
{
  std::string gameString, line = "";
  std::getline(std::cin, line);
  do
  {
    std::getline(std::cin, line);
    gameString += line + "\n";
  } while (line.length() > 1 && !std::cin.eof());
  game = Game(gameString);
}

void Controller::printGame()
{
  game.printGame();
}
