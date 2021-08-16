#include <algorithm>
#include <random>

#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

void BogoSort::startSortThread(GraphDisplay* display, std::vector<int>& in) {
  m_thread = std::thread(BogoSort::sort, this, display);
}

void BogoSort::sort(GraphDisplay* display) {
  std::random_device rd;
  std::mt19937 g(rd());
  while (!display->isSorted()) {
    // std::shuffle(in.begin(), in.end(), g);
    display->shuffleVector(g);
    if (threadShouldStop()) return;
    // if (!this->updateDisplay(display, in, m_activeIndices)) return;
    // this->print(in);
  }
}