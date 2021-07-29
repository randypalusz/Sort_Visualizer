#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "SortAlgorithm.hpp"

class SortAlgorithm;

// will take in a sf::renderwindow and a vector
class GraphDisplay {
  // allows update() to be wrapped by superclass updateDisplay()
  friend class SortAlgorithm;

 public:
  GraphDisplay(sf::RenderWindow& window, int waitTimeInMillis);

 private:
  bool update(const std::vector<int>& in);

 private:
  sf::RenderWindow& m_window;
  sf::Vector2u m_size;
  int m_waitTimeInMillis;
};