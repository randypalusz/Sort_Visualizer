#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <memory>
#include <vector>

#include "SortAlgorithm.hpp"
#include "util/Command.hpp"

class SortAlgorithm;

class Application {
 public:
  Application() {}
  void run(int numElements);
  // HACK: public for now for InputHandler
  sf::RenderWindow m_window;
  SortAlgorithm* m_sorter;
  std::vector<int> m_vec{};

 private:
};