#include "Command.hpp"
#include "AlgorithmFactory.hpp"

#include <iostream>

bool CloseWindowCommand::execute(sf::RenderWindow& window, std::vector<int>* in,
                                 SortAlgorithm** sorter) {
  window.close();
  return false;
}

bool RegenerateVectorCommand::execute(sf::RenderWindow& window,
                                      std::vector<int>* in,
                                      SortAlgorithm** sorter) {
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
                                         SortAlgorithm** sorter) {
  if (sorter) {
    Algorithm a = (*sorter)->getEnumType();
    a++;
    AlgorithmFactory::generateSorter(a, sorter);
  }
  return true;
}

bool DoNothingCommand::execute(sf::RenderWindow& window, std::vector<int>* in,
                               SortAlgorithm** sorter) {
  return true;
}