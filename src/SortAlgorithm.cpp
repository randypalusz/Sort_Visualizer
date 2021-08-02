#include "SortAlgorithm.hpp"

#include <vector>

void SortAlgorithm::print(const std::vector<int>& in) {
  bool first = true;
  std::cout << "{";
  for (auto& val : in) {
    if (!first) {
      std::cout << ", ";
    }
    first = false;
    std::cout << val;
  }
  std::cout << "}" << std::endl;
}

bool SortAlgorithm::updateDisplay(GraphDisplay* display, std::vector<int>& in) {
  if (display) {
    if (!display->update(in)) {
      return false;
    }
  }
  return true;
}
