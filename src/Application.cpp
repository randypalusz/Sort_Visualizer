#include "Application.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <functional>
#include <iostream>
#include <memory>

#include "AlgorithmEnums.hpp"
#include "AlgorithmFactory.hpp"
#include "ApplicationProperties.hpp"
#include "GraphDisplay.hpp"
#include "SortAlgorithm.hpp"
#include "util/InputHandler.hpp"
#include "util/Utility.hpp"

void Application::run() {
  init();

  while (m_window.isOpen()) {
    std::shared_ptr<Command> result = m_inputHandler->pollForEvents(m_window);
    result->execute(m_display, std::ref(m_sorter), &m_vec);
    m_sorter->run(m_display, m_vec);
    m_display->update();
  }
}

void Application::init() {
  auto vm = sf::VideoMode::getDesktopMode();

  m_window.create(sf::VideoMode(vm.width / 2.0f, vm.height / 2.0f), "Sort Visualizer");
  m_window.setFramerateLimit(0);

  m_sorter = AlgorithmFactory::generateSorter(Algorithm::SELECTION);
  m_vec = VectorGenerator::generateGivenSize(ApplicationProperties::numElements, true);
  m_display = new GraphDisplay(m_window, m_vec, ApplicationProperties::delay);
  m_inputHandler = new InputHandler();

  m_display->setTitle(m_sorter->getName());
}