#pragma once

#include "SortAlgorithm.hpp"

#include <vector>

class SortAlgorithm;

class Command {
 public:
  virtual ~Command() {}
  // bool here refers to if the current sort algorithm execution should
  // terminate and move to the next
  virtual bool execute(sf::RenderWindow& window, std::vector<int>* in,
                       SortAlgorithm** sorter) = 0;
};

class CloseWindowCommand : public Command {
  bool execute(sf::RenderWindow& window, std::vector<int>* in,
               SortAlgorithm** sorter) override;
};

class RegenerateVectorCommand : public Command {
  bool execute(sf::RenderWindow& window, std::vector<int>* in,
               SortAlgorithm** sorter) override;
};

class ChooseNextAlgorithmCommand : public Command {
  bool execute(sf::RenderWindow& window, std::vector<int>* in,
               SortAlgorithm** sorter) override;
};

class DoNothingCommand : public Command {
  bool execute(sf::RenderWindow& window, std::vector<int>* in,
               SortAlgorithm** sorter) override;
};
