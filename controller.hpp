#pragma once
#include <string>
#include "game.hpp"

class Controller
{
public:
  Controller();
  void run();

private:
  void executeCommand(std::string command);
  void loadGame();
  void printGame();
  Game game;
};