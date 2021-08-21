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
  void run(int numElements, double delay);

 private:
  void init(int numElements, double delay);
  sf::RenderWindow m_window;
  std::unique_ptr<SortAlgorithm> m_sorter = nullptr;
  GraphDisplay* m_display = nullptr;
  InputHandler* m_inputHandler = nullptr;
  std::vector<int> m_vec{};
};