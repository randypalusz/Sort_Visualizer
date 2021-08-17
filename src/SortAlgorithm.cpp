#include "SortAlgorithm.hpp"

#include <iostream>
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

bool SortAlgorithm::sortShouldContinue(const std::vector<int>& in) {
  // m_paused - is_sorted
  // t - t -> false
  // t - f -> false
  // f - t -> false
  // f - f -> true
  // return !(m_paused || std::is_sorted(in.begin(), in.end()));
  return !(m_threadActive || std::is_sorted(in.begin(), in.end())) &&
         !m_sortTerminated;
}

bool SortAlgorithm::handleAtomics(GraphDisplay* display) {
  if (m_threadShouldEnd.load()) {
    display->reset();
    return true;
  }
  while (m_paused.load()) {
    ;
  }
  return false;
}

bool SortAlgorithm::preSortChecks(GraphDisplay* display, std::vector<int>& in) {
  if (!SortAlgorithm::sortShouldContinue(in)) {
    return false;
  }

  // covers case where vector is regenerated before sort completes
  if (m_thread.joinable()) {
    m_threadShouldEnd.store(false);
    m_thread.join();
    m_threadActive = false;
  }

  display->reset();

  m_threadActive = true;
  return true;
}