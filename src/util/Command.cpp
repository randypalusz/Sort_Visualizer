#include "Command.hpp"
#include "AlgorithmFactory.hpp"

#include <iostream>

bool EndApplicationCommand::execute(sf::RenderWindow& window,
                                    std::vector<int>* in,
                                    SortAlgorithm** sorter) {
  window.close();
  // cleaning up paused variable to true so the sort thread can end!
  // ... will hang in the handleAtomics() fn within the sorter class
  (*sorter)->terminateSort();
  return false;
}

// TODO: make sure this also restarts the sorting algorithm
bool RegenerateVectorCommand::execute(sf::RenderWindow& window,
                                      std::vector<int>* in,
                                      SortAlgorithm** sorter) {
  if (in) {
    if ((*sorter)->isThreadActive()) {
      return true;
    }
    std::vector<int> temp =
        VectorGenerator::generateGivenSize(in->size(), true);
    in->clear();
    in->insert(in->begin(), temp.begin(), temp.end());
  }
  return true;
}

bool ChooseNextAlgorithmCommand::execute(sf::RenderWindow& window,
                                         std::vector<int>* in,
                                         SortAlgorithm** sorter) {
  if (sorter) {
    Algorithm a = (*sorter)->getEnumType();
    a++;
    (*sorter)->terminateSort();
    AlgorithmFactory::generateSorter(a, sorter);

    // regenerate vector after sorter is generated
    std::vector<int> temp =
        VectorGenerator::generateGivenSize(in->size(), true);
    in->clear();
    in->insert(in->begin(), temp.begin(), temp.end());
  }
  return true;
}

bool PauseCommand::execute(sf::RenderWindow& window, std::vector<int>* in,
                           SortAlgorithm** sorter) {
  bool paused = (*sorter)->getPaused();
  (*sorter)->setPaused(!paused);
  return false;
}

bool SendStepCommand::execute(sf::RenderWindow& window, std::vector<int>* in,
                              SortAlgorithm** sorter) {
  (*sorter)->setStep();
}

bool DoNothingCommand::execute(sf::RenderWindow& window, std::vector<int>* in,
                               SortAlgorithm** sorter) {
  return true;
}