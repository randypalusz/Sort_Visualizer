#include "SortAlgorithm.hpp"

#include <vector>
#include <unordered_set>

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

bool SortAlgorithm::updateDisplay(GraphDisplay* display, std::vector<int>& in,
                                  std::unordered_set<int>& activeIndices) {
  if (display) {
    if (!display->update(in, activeIndices)) {
      return false;
    }
  }
  activeIndices.clear();
  return true;
}
