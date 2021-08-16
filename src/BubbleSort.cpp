#include <vector>

#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

void BubbleSort::startSortThread(GraphDisplay* display, std::vector<int>& in) {
  m_thread = std::thread(&BubbleSort::sort, this, display);
}

void BubbleSort::sort(GraphDisplay* display) {
  bool swapOccurred = false;
  do {
    swapOccurred = false;
    for (int i = 0; i < display->getVecSize() - 1; i++) {
      display->mark(i);
      if (display->at(i + 1) < display->at(i)) {
        display->mark(i + 1, sf::Color::Green);
        display->swap(i, i + 1);
        if (threadShouldStop()) {
          display->unwatchAll();
          return;
        }
        swapOccurred = true;
      }
      display->unmark(i);
      display->unmark(i + 1);
    }
  } while (swapOccurred);
}