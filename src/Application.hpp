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

 private:
  SortAlgorithm* m_sorter = nullptr;
  std::vector<int> m_vec{};
};