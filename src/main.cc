#include <iostream>
#include <SFML/Window.hpp>

#include "AlgorithmEnums.hpp"
#include "AlgorithmFactory.hpp"
#include "SortAlgorithm.hpp"

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
  std::vector<int> v{1, 6, 5, 3, 8, 0};
  sorter->sort(nullptr, v);
}