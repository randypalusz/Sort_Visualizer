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

void Application::run(int numElements, double delay) {
  m_window.create(sf::VideoMode(800, 600), "Sort Visualizer");
  m_window.setFramerateLimit(0);

  m_sorter = AlgorithmFactory::generateSorter(Algorithm::SELECTION);
  m_vec = VectorGenerator::generateGivenSize(numElements, true);

  InputHandler inputHandler{};

  m_display = new GraphDisplay(m_window, m_vec, delay);

  while (m_window.isOpen()) {
    std::shared_ptr<Command> result = inputHandler.pollForEvents(m_window);
    result->execute(m_window, &m_vec, std::ref(m_sorter));
    m_sorter->run(m_display, m_vec);
    m_display->update();
  }
}