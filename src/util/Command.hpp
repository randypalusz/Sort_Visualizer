#pragma once

#include "SortAlgorithm.hpp"

#include <vector>

class SortAlgorithm;

class Command {
 public:
  virtual ~Command() {}
  // bool here refers to if the current sort algorithm execution should
  // terminate and return to main application run loop
  virtual bool execute(sf::RenderWindow& window, std::vector<int>* in,
                       SortAlgorithm** sorter, bool* paused) = 0;
};

class CloseWindowCommand : public Command {
  bool execute(sf::RenderWindow& window, std::vector<int>* in,
               SortAlgorithm** sorter, bool* paused) override;
};

class RegenerateVectorCommand : public Command {
  bool execute(sf::RenderWindow& window, std::vector<int>* in,
               SortAlgorithm** sorter, bool* paused) override;
};

class ChooseNextAlgorithmCommand : public Command {
  bool execute(sf::RenderWindow& window, std::vector<int>* in,
               SortAlgorithm** sorter, bool* paused) override;
};

class PauseCommand : public Command {
  bool execute(sf::RenderWindow& window, std::vector<int>* in,
               SortAlgorithm** sorter, bool* paused) override;
};

class DoNothingCommand : public Command {
  bool execute(sf::RenderWindow& window, std::vector<int>* in,
               SortAlgorithm** sorter, bool* paused) override;
};
