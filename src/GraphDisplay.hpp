#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

// will take in a sf::renderwindow and a vector
// display vertical bars based on the window size/number of elements/min and max
// element
class GraphDisplay {
 public:
  GraphDisplay(sf::RenderWindow& window, int waitTimeInMillis);
  bool update(const std::vector<int>& in);

 private:
  sf::RenderWindow& m_window;
  sf::Vector2u m_size;
  int m_waitTimeInMillis;
};