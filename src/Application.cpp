#include "Application.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <functional>
#include <iostream>
#include <memory>

#include "AlgorithmEnums.hpp"
#include "AlgorithmFactory.hpp"
#include "GraphDisplay.hpp"
#include "SortAlgorithm.hpp"
#include "util/InputHandler.hpp"
#include "util/Utility.hpp"

void Application::run(int numElements) {
  m_window.create(sf::VideoMode(800, 600), "Sort Visualizer");
  m_window.setFramerateLimit(60);

  AlgorithmFactory::generateSorter(Algorithm::SELECTION, &m_sorter);
  m_vec = VectorGenerator::generateGivenSize(numElements, true);

  InputHandler inputHandler{};

  GraphDisplay g = GraphDisplay{m_window, m_vec, 1};

  while (m_window.isOpen()) {
    std::shared_ptr<Command> result = inputHandler.pollForEvents(m_window);
    result->execute(m_window, &m_vec, &m_sorter, &(m_sorter->m_paused));
    m_sorter->sort(&g, m_vec);
    g.update();
  }

  // TODO: segmentation fault sometimes depending on when window is closed
  //      need to terminate child sort thread before leaving main
  //      just waiting for thread to end for now
  m_sorter->waitForThreadToFinish();
}