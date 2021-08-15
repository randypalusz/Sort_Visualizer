#pragma once

#include <SFML/Graphics.hpp>
#include <mutex>
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
  inline void mark(int idx) {
    auto&& lock = makeLock();
    m_activeIndices.insert(idx);
  }
  inline void unmark(int idx) {
    auto&& lock = makeLock();
    m_activeIndices.erase(idx);
  }
  inline void markSwap(int toRemove, int replacement) {
    auto&& lock = makeLock();
    m_activeIndices.erase(toRemove);
    m_activeIndices.insert(replacement);
  }
  inline const int at(int idx) {
    auto&& lock = makeLock();
    if (m_lastAccessedIdx != idx) {
      // do delay if not a duplicate access
      this->onAccess();
    }
    m_lastAccessedIdx = idx;
    return m_sortVector.at(idx);
  }
  inline void swap(int idx1, int idx2) {
    auto&& lock = makeLock();
    std::swap(m_sortVector.at(idx1), m_sortVector.at(idx2));
  }
  inline void watch(int* idxPointer) {
    auto&& lock = makeLock();
    m_watchedIndices.insert(idxPointer);
  }
  inline void unwatchAll() {
    auto&& lock = makeLock();
    m_watchedIndices.clear();
  }
  inline int getVecSize() {
    auto&& lock = makeLock();
    return m_sortVector.size();
  }
  inline void reset() {
    auto&& lock = makeLock();
    m_lastAccessedIdx = -1;
    m_activeIndices.clear();
    m_watchedIndices.clear();
  }

 private:
  void onAccess();
  // Creates lock that is held by a move-constructed auto&&
  // seems to fix segmentation fault at high rate of accesses
  inline const std::lock_guard<std::mutex> makeLock() {
    return std::lock_guard<std::mutex>{m_setMutex};
  }

  int m_lastAccessedIdx = -1;
  sf::RenderWindow& m_window;
  std::vector<int>& m_sortVector;
  std::unordered_set<int> m_activeIndices;
  std::unordered_set<int*> m_watchedIndices;
  sf::Vector2u m_size;
  InputHandler* m_inputHandler;
  std::mutex m_setMutex;
  double m_delayInSeconds;
};