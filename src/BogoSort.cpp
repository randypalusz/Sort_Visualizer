#include <algorithm>
#include <random>

#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

void BogoSort::sort(GraphDisplay* display, std::vector<int>& in) {
  if (!SortAlgorithm::sortShouldContinue(in)) {
    return;
  }
  std::random_device rd;
  std::mt19937 g(rd());
  while (!std::is_sorted(in.begin(), in.end())) {
    std::shuffle(in.begin(), in.end(), g);
    if (!this->updateDisplay(display, in, m_activeIndices)) return;
    // this->print(in);
  }
}