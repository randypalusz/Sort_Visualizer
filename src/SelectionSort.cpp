#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

#include <iostream>
#include <vector>
#include <thread>

void SelectionSort::sort(GraphDisplay* display, std::vector<int>& in) {
  if (!SortAlgorithm::sortShouldContinue(in)) {
    return;
  }
  m_threadActive = true;
  m_thread =
      std::thread(&SelectionSort::internalSort, this, display, std::ref(in));
}

// TODO: terminate if window destroyed
void SelectionSort::internalSort(GraphDisplay* display, std::vector<int>& in) {
  int minIndex = 0;
  for (int i = 0; i < (in.size() - 1); i++) {
    minIndex = i;
    display->m_activeIndices.insert(i);
    for (int j = i + 1; j < in.size(); j++) {
      display->m_activeIndices.insert(j);
      Timing::preciseSleep(0.010);
      if (in.at(j) < in.at(minIndex)) {
        if (minIndex != i) {
          display->m_activeIndices.erase(minIndex);
        }
        minIndex = j;
      } else {
        display->m_activeIndices.erase(j);
      }
    }
    std::swap(in.at(i), in.at(minIndex));
    display->m_activeIndices.erase(i);
    display->m_activeIndices.erase(minIndex);
  }
  m_threadActive = false;
}