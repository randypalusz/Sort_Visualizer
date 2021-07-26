#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <functional>
#include <iostream>

#include "AlgorithmEnums.hpp"
#include "AlgorithmFactory.hpp"
#include "GraphDisplay.hpp"
#include "SortAlgorithm.hpp"
#include "util/Utility.hpp"

int main(int argc, char** argv) {
  sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
  window.setFramerateLimit(0);

  GraphDisplay g = GraphDisplay{window, 1};

  SortAlgorithm* sorter = AlgorithmFactory::generateSorter(Algorithm::QUICK);
  const int numElements = atoi(argv[1]);
  std::vector<int> v = VectorGenerator::generateGivenSize(numElements);

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
    sorter->sort(&g, v);
  }

  sorter = AlgorithmFactory::generateSorter(Algorithm::BOGO);
  v = VectorGenerator::generateGivenSize(6);
  sorter->sort(nullptr, v);
}