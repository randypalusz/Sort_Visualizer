#pragma once

#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

#include <vector>

class GraphDisplay;
class SortAlgorithm;

class Command {
 public:
  virtual ~Command() {}
  // bool here refers to if the current sort algorithm execution should
  // terminate and return to main application run loop
  virtual bool execute(GraphDisplay* display,
                       std::unique_ptr<SortAlgorithm>& sorter,
                       std::vector<int>* in) = 0;
};

class EndApplicationCommand : public Command {
  bool execute(GraphDisplay* display, std::unique_ptr<SortAlgorithm>& sorter,
               std::vector<int>* in) override;
};

class RegenerateVectorCommand : public Command {
  bool execute(GraphDisplay* display, std::unique_ptr<SortAlgorithm>& sorter,
               std::vector<int>* in) override;
};

class ChooseNextAlgorithmCommand : public Command {
  bool execute(GraphDisplay* display, std::unique_ptr<SortAlgorithm>& sorter,
               std::vector<int>* in) override;
};

class PauseCommand : public Command {
  bool execute(GraphDisplay* display, std::unique_ptr<SortAlgorithm>& sorter,
               std::vector<int>* in) override;
};

class SendStepCommand : public Command {
  bool execute(GraphDisplay* display, std::unique_ptr<SortAlgorithm>& sorter,
               std::vector<int>* in) override;
};

class DoNothingCommand : public Command {
  bool execute(GraphDisplay* display, std::unique_ptr<SortAlgorithm>& sorter,
               std::vector<int>* in) override;
};

class ChangeDelayCommand : public Command {
 public:
  ChangeDelayCommand(bool increaseDelay) : m_increaseDelay{increaseDelay} {}
  bool execute(GraphDisplay* display, std::unique_ptr<SortAlgorithm>& sorter,
               std::vector<int>* in) override;

 private:
  bool m_increaseDelay;
};
