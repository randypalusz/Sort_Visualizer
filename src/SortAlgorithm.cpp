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
  // if (display) {
  //   if (!display->update(in, activeIndices, &m_paused)) {
  //     return false;
  //   }
  // }
  // activeIndices.clear();
  // return true;
  return true;
}

bool SortAlgorithm::checkPreSort(const std::vector<int>& in) {
  // m_paused - is_sorted
  // t - t -> false
  // t - f -> false
  // f - t -> false
  // f - f -> true
  // return !(m_paused || std::is_sorted(in.begin(), in.end()));
  return !(m_threadActive || std::is_sorted(in.begin(), in.end()));
}
