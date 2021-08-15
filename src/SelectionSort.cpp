#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

#include <iostream>
#include <vector>
#include <thread>

void SelectionSort::sort(GraphDisplay* display, std::vector<int>& in) {
  if (!SortAlgorithm::sortShouldContinue(in)) {
    return;
  }

  // if (m_thread.joinable()) {
  //   m_thread.join();
  //   return;
  // }

  m_threadActive = true;
  m_thread =
      std::thread(&SelectionSort::internalSort, this, display, std::ref(in));
}

void SelectionSort::internalSort(GraphDisplay* display, std::vector<int>& in) {
  int minIndex;
  display->watch(&minIndex);
  for (int i = 0; i < (display->getVecSize() - 1); i++) {
    minIndex = i;
    display->mark(i);
    for (int j = i + 1; j < display->getVecSize(); j++) {
      display->mark(j);
      // TODO: checking for m_threadShouldEnd should be done at the spot most
      //       often checked in sorting
      if (threadShouldStop()) return;
      if (display->at(j) < display->at(minIndex)) {
        minIndex = j;
      }
      display->unmark(j);
    }
    display->swap(i, minIndex);
    display->unmark(i);
  }
  display->unwatchAll();
  m_threadActive = false;
}