#include <algorithm>
#include <random>

#include "GraphDisplay.hpp"
#include "SortAlgorithm.hpp"

void BogoSort::sort(GraphDisplay* display, std::vector<int>& in) {
  std::random_device rd;
  std::mt19937 g(rd());
  while (!std::is_sorted(in.begin(), in.end())) {
    std::shuffle(in.begin(), in.end(), g);
    if (display) {
      if (!(display->update(in))) {
        return;
      }
    }
    this->print(in);
  }
}