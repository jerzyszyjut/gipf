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
}

void Controller::loadGame()
{
  std::string gameString, line = "";
  std::getline(std::cin, line);
  do
  {
    std::getline(std::cin, line);
    gameString += line + "\n";
  } while (line.length() > 1);
  Game game = Game(gameString);
}