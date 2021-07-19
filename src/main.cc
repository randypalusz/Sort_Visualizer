#include <iostream>
#include <SFML/Window.hpp>

#include "AlgorithmEnums.hpp"
#include "AlgorithmFactory.hpp"
#include "SortAlgorithm.hpp"
#include "util/Utility.hpp"

int main() {
  sf::Window window(sf::VideoMode(800, 600), "My window");

  // run the program as long as the window is open
  while (window.isOpen()) {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    sf::Event event;
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::KeyPressed) window.close();
      if (event.type == sf::Event::Closed) window.close();
    }
  }

  SortAlgorithm* sorter = AlgorithmFactory::generateSorter(Algorithm::BUBBLE);
  std::vector<int> v = VectorGenerator::generateGivenSize(20);
  sorter->sort(nullptr, v);

  sorter = AlgorithmFactory::generateSorter(Algorithm::BOGO);
  v = VectorGenerator::generateGivenSize(6);
  sorter->sort(nullptr, v);
}