#pragma once
#include <string>

class Controller
{
public:
  Controller();
  void run();

private:
  void executeCommand(std::string command);
  void loadGame();
};