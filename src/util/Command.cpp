#include "Command.hpp"

#include <iostream>

#include "AlgorithmFactory.hpp"

bool EndApplicationCommand::execute(GraphDisplay* display,
                                    std::unique_ptr<SortAlgorithm>& sorter,
                                    std::vector<int>* in) {
  // window.close();
  display->closeWindow();
  // cleaning up paused variable to true so the sort thread can end!
  // ... will hang in the handleAtomics() fn within the sorter class
  sorter->terminateSort();
  return false;
}

bool RegenerateVectorCommand::execute(GraphDisplay* display,
                                      std::unique_ptr<SortAlgorithm>& sorter,
                                      std::vector<int>* in) {
  if (in) {
    if (sorter->isThreadActive()) {
      return true;
    }
    std::vector<int> temp =
        VectorGenerator::generateGivenSize(in->size(), true);
    in->clear();
    in->insert(in->begin(), temp.begin(), temp.end());
  }
  return true;
}

bool ChooseNextAlgorithmCommand::execute(GraphDisplay* display,
                                         std::unique_ptr<SortAlgorithm>& sorter,
                                         std::vector<int>* in) {
  if (sorter) {
    Algorithm a = sorter->getEnumType();
    a++;
    sorter->terminateSort();
    sorter = std::move(AlgorithmFactory::generateSorter(a));

    // regenerate vector after sorter is generated
    std::vector<int> temp =
        VectorGenerator::generateGivenSize(in->size(), true);
    in->clear();
    in->insert(in->begin(), temp.begin(), temp.end());
  }
  return true;
}

bool PauseCommand::execute(GraphDisplay* display,
                           std::unique_ptr<SortAlgorithm>& sorter,
                           std::vector<int>* in) {
  sorter->togglePaused();
  return false;
}

bool SendStepCommand::execute(GraphDisplay* display,
                              std::unique_ptr<SortAlgorithm>& sorter,
                              std::vector<int>* in) {
  sorter->setStep();
  return true;
}

bool DoNothingCommand::execute(GraphDisplay* display,
                               std::unique_ptr<SortAlgorithm>& sorter,
                               std::vector<int>* in) {
  return true;
}

bool ChangeDelayCommand::execute(GraphDisplay* display,
                                 std::unique_ptr<SortAlgorithm>& sorter,
                                 std::vector<int>* in) {
  double modValue = (m_increaseDelay) ? 0.002 : -0.002;
  display->changeDelay(modValue);

  return true;
}