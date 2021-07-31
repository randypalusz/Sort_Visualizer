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
  window.setFramerateLimit(10);

  GraphDisplay g = GraphDisplay{window, 1};

  SortAlgorithm* sorter =
      AlgorithmFactory::generateSorter(Algorithm::SELECTION);
  const int numElements = atoi(argv[1]);
  std::vector<int> v = VectorGenerator::generateGivenSize(numElements, true);

  while (window.isOpen()) {
    WindowEvent result = WindowManager::pollForEvents(window);
    // TODO: make an event handler class (non-static) that will handle the
    //       events that polling returns, replacing the switch below.
    //       GraphDisplay should hold an instance of this as well.
    switch (result) {
      case WindowEvent::CLOSE_WINDOW:
        window.close();
        break;
      case WindowEvent::NEXT_ALGORITHM:
        sorter = AlgorithmFactory::generateSorter(Algorithm::BUBBLE);
        break;
      case WindowEvent::REGENERATE_VECTOR:
        v = VectorGenerator::generateGivenSize(numElements, true);
        break;
      case WindowEvent::NO_EVENT:
      default:
        break;
    }
    sorter->sort(&g, v);
  }

  sorter = AlgorithmFactory::generateSorter(Algorithm::BOGO);
  v = VectorGenerator::generateGivenSize(6, false);
  sorter->sort(nullptr, v);
}