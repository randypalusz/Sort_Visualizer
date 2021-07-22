#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

#include <algorithm>
#include <random>

void BogoSort::sort(GraphDisplay* display, std::vector<int>& in) {
  std::random_device rd;
  std::mt19937 g(rd());
  while (!std::is_sorted(in.begin(), in.end())) {
    std::shuffle(in.begin(), in.end(), g);
    if (display) {
      display->update(in);
    }
    this->print(in);
  }
}