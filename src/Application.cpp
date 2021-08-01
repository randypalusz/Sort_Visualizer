#include "Application.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <functional>
#include <iostream>

#include "AlgorithmEnums.hpp"
#include "AlgorithmFactory.hpp"
#include "GraphDisplay.hpp"
#include "SortAlgorithm.hpp"
#include "util/Utility.hpp"

void Application::run(int numElements) {
  m_window.create(sf::VideoMode(800, 600), "Sort Visualizer");
  m_window.setFramerateLimit(500);

  GraphDisplay g = GraphDisplay{m_window, 1};

  // TODO: convert to smart pointer to handle memory
  std::shared_ptr<SortAlgorithm> sorter =
      AlgorithmFactory::generateSorter(Algorithm::SELECTION);
  std::vector<int> v = VectorGenerator::generateGivenSize(numElements, true);

  while (m_window.isOpen()) {
    WindowEvent result = WindowManager::pollForEvents(m_window);
    // TODO: make an event handler class (non-static) that will handle the
    //       events that polling returns, replacing the switch below.
    //       GraphDisplay should hold an instance of this as well.
    switch (result) {
      case WindowEvent::CLOSE_WINDOW:
        m_window.close();
        break;
      case WindowEvent::NEXT_ALGORITHM:
        // HACK: just using different sort from above for now to demonstrate
        //       that event polling works
        sorter = AlgorithmFactory::generateSorter(Algorithm::QUICK);
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