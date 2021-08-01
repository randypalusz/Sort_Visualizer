#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <memory>

#include "SortAlgorithm.hpp"

class Application {
 public:
  Application() {}
  void run(int numElements);

 private:
  sf::RenderWindow m_window;
  std::shared_ptr<SortAlgorithm> m_sorter = nullptr;
};