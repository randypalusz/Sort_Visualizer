#include "Command.hpp"

#include <iostream>

#include "AlgorithmFactory.hpp"

bool EndApplicationCommand::execute(sf::RenderWindow& window, std::vector<int>* in,
                                    std::unique_ptr<SortAlgorithm>& sorter) {
  window.close();
  // cleaning up paused variable to true so the sort thread can end!
  // ... will hang in the handleAtomics() fn within the sorter class
  sorter->terminateSort();
  return false;
}

bool RegenerateVectorCommand::execute(sf::RenderWindow& window, std::vector<int>* in,
                                      std::unique_ptr<SortAlgorithm>& sorter) {
  if (in) {
    if (sorter->isThreadActive()) {
      return true;
    }
    std::vector<int> temp = VectorGenerator::generateGivenSize(in->size(), true);
    in->clear();
    in->insert(in->begin(), temp.begin(), temp.end());
  }
  return true;
}

bool ChooseNextAlgorithmCommand::execute(sf::RenderWindow& window, std::vector<int>* in,
                                         std::unique_ptr<SortAlgorithm>& sorter) {
  if (sorter) {
    Algorithm a = sorter->getEnumType();
    a++;
    sorter->terminateSort();
    sorter = std::move(AlgorithmFactory::generateSorter(a));

    // regenerate vector after sorter is generated
    std::vector<int> temp = VectorGenerator::generateGivenSize(in->size(), true);
    in->clear();
    in->insert(in->begin(), temp.begin(), temp.end());
  }
  return true;
}

bool PauseCommand::execute(sf::RenderWindow& window, std::vector<int>* in,
                           std::unique_ptr<SortAlgorithm>& sorter) {
  sorter->togglePaused();
  return false;
}

bool SendStepCommand::execute(sf::RenderWindow& window, std::vector<int>* in,
                              std::unique_ptr<SortAlgorithm>& sorter) {
  sorter->setStep();
  return true;
}

bool DoNothingCommand::execute(sf::RenderWindow& window, std::vector<int>* in,
                               std::unique_ptr<SortAlgorithm>& sorter) {
  return true;
}