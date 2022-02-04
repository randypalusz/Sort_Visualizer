#include <vector>

#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

void BubbleSort::startSortThread(GraphDisplay* display, std::vector<int>& in) {
  m_thread = std::thread(&BubbleSort::sort, this, display);
}

void BubbleSort::sort(GraphDisplay* display) {
  try {
    bool swapOccurred = false;
    int maxIndex = display->getVecSize() - 1;
    do {
      swapOccurred = false;
      for (int i = 0; i < maxIndex; i++) {
        display->mark(i);
        if (display->at(i + 1) < display->at(i)) {
          display->mark(i + 1, sf::Color::Green);
          handleAtomics(display);
          display->swap(i, i + 1, true);
          handleAtomics(display);
          swapOccurred = true;
        }
        display->unmark(i);
        display->unmark(i + 1);
      }
      maxIndex--;
    } while (swapOccurred);
    display->reset();
    setState(AlgorithmState::INACTIVE);
  } catch (AlgorithmException) {
    return;
  }
}