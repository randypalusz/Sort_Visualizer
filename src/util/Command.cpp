#include "Command.hpp"
#include "AlgorithmFactory.hpp"

#include <iostream>

bool CloseWindowCommand::execute(sf::RenderWindow& window, std::vector<int>* in,
                                 SortAlgorithm** sorter, bool* paused) {
  window.close();
  return false;
}

bool RegenerateVectorCommand::execute(sf::RenderWindow& window,
                                      std::vector<int>* in,
                                      SortAlgorithm** sorter, bool* paused) {
  if (in) {
    std::vector<int> temp =
        VectorGenerator::generateGivenSize(in->size(), true);
    in->clear();
    in->insert(in->begin(), temp.begin(), temp.end());
  }
  return true;
}

bool ChooseNextAlgorithmCommand::execute(sf::RenderWindow& window,
                                         std::vector<int>* in,
                                         SortAlgorithm** sorter, bool* paused) {
  if (sorter) {
    Algorithm a = (*sorter)->getEnumType();
    a++;
    AlgorithmFactory::generateSorter(a, sorter);
  }
  return true;
}

bool PauseCommand::execute(sf::RenderWindow& window, std::vector<int>* in,
                           SortAlgorithm** sorter, bool* paused) {
  if (paused) {
    *paused = !(*paused);
  }
  return false;
}

bool DoNothingCommand::execute(sf::RenderWindow& window, std::vector<int>* in,
                               SortAlgorithm** sorter, bool* paused) {
  return true;
}