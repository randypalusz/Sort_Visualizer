#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

#include <iostream>
#include <vector>
#include <thread>

void SelectionSort::sort(GraphDisplay* display, std::vector<int>& in) {
  if (!SortAlgorithm::sortShouldContinue(in)) {
    return;
  }
  if (m_thread.joinable()) {
    m_thread.join();
  }

  m_threadActive = true;
  m_thread =
      std::thread(&SelectionSort::internalSort, this, display, std::ref(in));
}

void SelectionSort::internalSort(GraphDisplay* display, std::vector<int>& in) {
  int minIndex = 0;
  for (int i = 0; i < (in.size() - 1); i++) {
    minIndex = i;
    display->m_activeIndices.insert(i);
    for (int j = i + 1; j < in.size(); j++) {
      display->m_activeIndices.insert(j);
      // TODO: sleep at each access of vector in GraphDisplay
      //       also ensure using sleep time passed into GraphDisplay
      Timing::preciseSleep(0.002);
      // TODO: checking for m_threadShouldEnd should be done at the spot most
      //       often checked in sorting, maybe check this at each access too
      if (m_threadShouldEnd) {
        m_threadActive = false;
        return;
      }
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