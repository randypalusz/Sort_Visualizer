#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "SortAlgorithm.hpp"
#include "util/Utility.hpp"

class SortAlgorithm;
class InputHandler;

// will take in a sf::renderwindow and a vector
class GraphDisplay {
  // allows update() to be wrapped by superclass updateDisplay()
  friend class SortAlgorithm;

 public:
  GraphDisplay(sf::RenderWindow& window, int waitTimeInMillis);
  ~GraphDisplay();

 private:
  bool update(std::vector<int>& in);

 private:
  // TODO: add EventHandler object here to handle events on update call
  sf::RenderWindow& m_window;
  sf::Vector2u m_size;
  InputHandler* m_inputHandler;

  int m_waitTimeInMillis;
};