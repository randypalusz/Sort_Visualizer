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
                       std::unique_ptr<SortAlgorithm>& sorter) = 0;
};

class EndApplicationCommand : public Command {
  bool execute(sf::RenderWindow& window, std::vector<int>* in,
               std::unique_ptr<SortAlgorithm>& sorter) override;
};

class RegenerateVectorCommand : public Command {
  bool execute(sf::RenderWindow& window, std::vector<int>* in,
               std::unique_ptr<SortAlgorithm>& sorter) override;
};

class ChooseNextAlgorithmCommand : public Command {
  bool execute(sf::RenderWindow& window, std::vector<int>* in,
               std::unique_ptr<SortAlgorithm>& sorter) override;
};

class PauseCommand : public Command {
  bool execute(sf::RenderWindow& window, std::vector<int>* in,
               std::unique_ptr<SortAlgorithm>& sorter) override;
};

class SendStepCommand : public Command {
  bool execute(sf::RenderWindow& window, std::vector<int>* in,
               std::unique_ptr<SortAlgorithm>& sorter) override;
};

class DoNothingCommand : public Command {
  bool execute(sf::RenderWindow& window, std::vector<int>* in,
               std::unique_ptr<SortAlgorithm>& sorter) override;
};
