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
    // TODO: performance shouldn't really be impacted with this, but eval later
    // update all watched indices with default color
    for (auto& entry : m_watchedIndices) {
      sf::Color resetColor = m_watchedIndicesResetColor.at(entry.first);
      entry.second = resetColor;
    }
    m_lastAccessedIdx = idx;
    return m_sortVector.at(idx);
  }
  inline void swap(int idx1, int idx2) {
    auto&& lock = makeLock();
    this->onAccess();
    std::swap(m_sortVector.at(idx1), m_sortVector.at(idx2));
  }
  // TODO: test if this really works as intended...
  inline void swap(int idx1, int idx2, bool swapColor) {
    if (swapColor) {
      auto&& lock = makeLock();
      sf::Color* colorPtrOne = nullptr;
      sf::Color* colorPtrTwo = nullptr;
      this->onAccess();
      std::swap(m_sortVector.at(idx1), m_sortVector.at(idx2));
      for (auto& entry : m_watchedIndices) {
        int currentIdx = *(entry.first);
        if ((currentIdx == idx1) || (currentIdx == idx2)) {
          if (colorPtrOne == nullptr) {
            colorPtrOne = &entry.second;
          } else {
            colorPtrTwo = &entry.second;
          }
        }
      }
      for (auto& entry : m_activeIndices) {
        int currentIdx = entry.first;
        if ((currentIdx == idx1) || (currentIdx == idx2)) {
          if (colorPtrOne == nullptr) {
            colorPtrOne = &entry.second;
          } else {
            colorPtrTwo = &entry.second;
          }
        }
      }
      sf::Color temp = *colorPtrOne;
      *colorPtrOne = *colorPtrTwo;
      *colorPtrTwo = temp;

    } else {
      this->swap(idx1, idx2);
    }
  }
  inline void watch(int* idxPointer, sf::Color color = sf::Color::Green) {
    auto&& lock = makeLock();
    m_watchedIndices.insert({idxPointer, color});
    m_watchedIndicesResetColor.insert({idxPointer, color});
  }
  inline void unwatchAll() {
    auto&& lock = makeLock();
    m_watchedIndices.clear();
    m_watchedIndicesResetColor.clear();
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
    m_watchedIndicesResetColor.clear();
  }
  inline bool isSorted() {
    return std::is_sorted(m_sortVector.begin(), m_sortVector.end());
  }
  inline void shuffleVector(std::mt19937& g) {
    std::shuffle(m_sortVector.begin(), m_sortVector.end(), g);
    this->onAccess();
  }
  inline void closeWindow() { return m_window.close(); }
  inline void changeDelay(double modification) {
    m_delayInSeconds += modification;
    m_delayInSeconds = std::clamp(m_delayInSeconds, 0.0001, 1.0);
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
  std::unordered_map<int*, sf::Color> m_watchedIndicesResetColor;
  sf::Vector2u m_size;
  std::mutex m_setMutex;
  sf::Color m_watchResetColor;
  double m_delayInSeconds;
};