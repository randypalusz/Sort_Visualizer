#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_set>

#include "SortAlgorithm.hpp"
#include "util/Utility.hpp"

class SortAlgorithm;
class InputHandler;
class Timing;

class GraphDisplay {
  // allows update() to be wrapped by superclass updateDisplay()
  friend class SortAlgorithm;

 public:
  GraphDisplay(sf::RenderWindow& window, std::vector<int>& in,
               double delayInSeconds);
  ~GraphDisplay();
  bool update();
  inline void mark(int idx) { m_activeIndices.insert(idx); }
  inline void unmark(int idx) { m_activeIndices.erase(idx); }
  inline int getVecSize() { return m_sortVector.size(); }

 private:
  void onAccess();
  sf::RenderWindow& m_window;
  std::vector<int>& m_sortVector;
  std::unordered_set<int> m_activeIndices;
  sf::Vector2u m_size;
  InputHandler* m_inputHandler;

  double m_delayInSeconds;
};