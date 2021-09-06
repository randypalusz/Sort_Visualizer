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
  return m_state.load() == AlgorithmState::INACTIVE &&
         !std::is_sorted(in.begin(), in.end());
}

// TODO: call this more often to mark pause points
bool SortAlgorithm::handleAtomics(GraphDisplay* display) {
  if (m_state.load() == AlgorithmState::SHOULD_END) {
    display->reset();
    return true;
  }
  // intentionally not returning m_threadShouldEnd - in the case where
  // terminateSort() is called, m_threadShouldEnd := true and
  // m_paused := false. If final return statement here returns
  // m_threadShouldEnd.load(), would bypass display->reset() from being called,
  // causing seg fault when display->update() accesses the watchedIndices map of
  // int* because the thread ends, and those values pointed to go out of scope
  // TODO: think about this class keeping a pointer/ref to the GraphDisplay to
  //       do the reset in the terminateSort() function
  while (m_state.load() == AlgorithmState::PAUSED) {
    if (m_step.load()) {
      m_step.store(false);
      break;
    }
  }
  return false;
}

bool SortAlgorithm::preSortChecks(GraphDisplay* display, std::vector<int>& in) {
  if (!SortAlgorithm::sortShouldContinue(in)) {
    return false;
  }

  // covers case where vector is regenerated before sort completes, although
  // RegenerateVectorCommand prevents this from being caught
  if (m_thread.joinable()) {
    setState(AlgorithmState::SHOULD_END);
    m_thread.join();
    setState(AlgorithmState::INACTIVE);
  }

  display->reset();

  m_state = AlgorithmState::RUNNING;
  return true;
}