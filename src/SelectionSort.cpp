#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

#include <iostream>
#include <vector>
#include <thread>

void SelectionSort::startSortThread(GraphDisplay* display) {
  m_thread = std::thread(&SelectionSort::sort, this, display);
}

void SelectionSort::sort(GraphDisplay* display) {
  try {
    int minIndex;
    display->watch(&minIndex);
    for (int i = 0; i < (display->getVecSize() - 1); i++) {
      minIndex = i;
      display->mark(i);
      for (int j = i + 1; j < display->getVecSize(); j++) {
        display->mark(j);
        // handleAtomics() should be called where code will be run most
        // frequently within internalSort
        handleAtomics(display);
        if (display->at(j) < display->at(minIndex)) {
          minIndex = j;
        }
        display->unmark(j);
      }
      display->swap(i, minIndex);
      display->unmark(i);
    }
    tearDown(display);
  } catch (AlgorithmException) {
    return;
  }
}