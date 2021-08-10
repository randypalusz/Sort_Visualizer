#pragma once

#include <SFML/Graphics.hpp>
#include <atomic>
#include <chrono>
#include <vector>
#include <unordered_set>
#include <thread>

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
  bool update(std::vector<int>& in,
              const std::unordered_set<int>& activeIndices, bool* paused);
  inline void threadTest(const std::string& in) {
    while (!m_stopThread) {
      std::cout << in << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  }

 private:
  sf::RenderWindow& m_window;
  sf::Vector2u m_size;
  InputHandler* m_inputHandler;
  // TODO: pass update function + parameters to this instead of test print
  // function above
  std::thread m_displayThread;
  std::atomic<bool> m_stopThread = false;

  int m_waitTimeInMillis;
};