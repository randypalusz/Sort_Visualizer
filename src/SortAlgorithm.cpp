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
  return (m_state.load() == AlgorithmState::INACTIVE) &&
         !std::is_sorted(in.begin(), in.end());
}

// TODO: call this more often to mark pause points
void SortAlgorithm::handleAtomics(GraphDisplay* display) {
  if (m_state.load() == AlgorithmState::SHOULD_END) {
    display->reset();
    throw AlgorithmException::END_SORT;
  }

  // need to call display->reset() here so that no seg fault
  // when display->update() accesses the watchedIndices<int*, sf::Color> map of
  // because the thread ends, and those values pointed to go out of scope
  // TODO: think about this class keeping a pointer/ref to the GraphDisplay to
  //       do the reset in the terminateSort() function
  while (m_paused.load()) {
    if (m_state.load() == AlgorithmState::SHOULD_END) {
      display->reset();
      throw AlgorithmException::END_SORT;
    }
    if (m_step.load()) {
      m_step.store(false);
      break;
    }
  }
}

// init returns false if the sort is already running, or if the vector is already sorted
// return true and resets the display parameters/sets state to RUNNING otherwise
bool SortAlgorithm::init(GraphDisplay* display, std::vector<int>& in) {
  if (!SortAlgorithm::sortShouldContinue(in)) {
    return false;
  }

  display->reset();
  m_state = AlgorithmState::RUNNING;

  return true;
}

void SortAlgorithm::tearDown(GraphDisplay* display) {
  display->reset();
  setState(AlgorithmState::INACTIVE);
}