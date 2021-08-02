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
  m_window.setFramerateLimit(500);

  AlgorithmFactory::generateSorter(Algorithm::SELECTION, &m_sorter);
  m_vec = VectorGenerator::generateGivenSize(numElements, true);

  InputHandler inputHandler{};

  GraphDisplay g = GraphDisplay{m_window, 1};

  while (m_window.isOpen()) {
    std::shared_ptr<Command> result = inputHandler.pollForEvents(m_window);
    if (result) {
      result->execute(m_window, &m_vec, &m_sorter);
    }

    m_sorter->sort(&g, m_vec);
  }

  AlgorithmFactory::generateSorter(Algorithm::BOGO, &m_sorter);
  std::vector<int> v = VectorGenerator::generateGivenSize(6, false);
  m_sorter->sort(nullptr, v);
}