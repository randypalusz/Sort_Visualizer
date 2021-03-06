#include <algorithm>
#include <random>

#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

void BogoSort::startSortThread(GraphDisplay* display) {
  m_thread = std::thread(&BogoSort::sort, this, display);
}

void BogoSort::sort(GraphDisplay* display) {
  try {
    std::random_device rd;
    std::mt19937 g(rd());
    while (!display->isSorted()) {
      display->shuffleVector(g);
      handleAtomics(display);
    }
    tearDown(display);
  } catch (AlgorithmException) {
    return;
  }
}
