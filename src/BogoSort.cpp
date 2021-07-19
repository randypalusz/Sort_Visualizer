#include "SortAlgorithm.hpp"

#include <algorithm>
#include <random>

void BogoSort::sort(void* sfml_context, std::vector<int>& in) {
  std::random_device rd;
  std::mt19937 g(rd());
  while (!std::is_sorted(in.begin(), in.end())) {
    std::shuffle(in.begin(), in.end(), g);
    this->print(in);
  }
}