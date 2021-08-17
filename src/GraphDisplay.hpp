#pragma once

#include <SFML/Graphics.hpp>
#include <mutex>
#include <vector>
#include <unordered_set>
#include <unordered_map>

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
  inline void mark(int idx, sf::Color color = sf::Color::Red) {
    auto&& lock = makeLock();
    if (m_activeIndices.find(idx) != m_activeIndices.end()) {
      m_activeIndices.erase(idx);
    }
    m_activeIndices.insert({idx, color});
  }
  inline void unmark(int idx) {
    auto&& lock = makeLock();
    m_activeIndices.erase(idx);
  }
  inline void markSwap(int toRemove, int replacement,
                       sf::Color color = sf::Color::Red) {
    auto&& lock = makeLock();
    m_activeIndices.erase(toRemove);
    m_activeIndices.insert({replacement, color});
  }
  inline int& at(int idx) {
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
    this->onAccess();
    std::swap(m_sortVector.at(idx1), m_sortVector.at(idx2));
  }
  inline void watch(int* idxPointer, sf::Color color = sf::Color::Green) {
    auto&& lock = makeLock();
    m_watchedIndices.insert({idxPointer, color});
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
  inline bool isSorted() {
    return std::is_sorted(m_sortVector.begin(), m_sortVector.end());
  }
  inline void shuffleVector(std::mt19937& g) {
    std::shuffle(m_sortVector.begin(), m_sortVector.end(), g);
    this->onAccess();
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
  std::unordered_map<int, sf::Color> m_activeIndices;
  std::unordered_map<int*, sf::Color> m_watchedIndices;
  sf::Vector2u m_size;
  InputHandler* m_inputHandler;
  std::mutex m_setMutex;
  double m_delayInSeconds;
};