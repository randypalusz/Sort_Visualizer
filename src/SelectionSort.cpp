#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

#include <vector>
#include <chrono>
#include <iostream>

void SelectionSort::sort(GraphDisplay* display, std::vector<int>& in) {
  if (!SortAlgorithm::checkPreSort(in)) {
    return;
  }
  display->startDisplayThread(in, m_activeIndices);
  int minIndex = 0;
  for (int i = 0; i < (in.size() - 1); i++) {
    minIndex = in.at(i);
    // TODO: move all these inserts/swaps to the display itself
    //      maybe display should contain the vector
    //      would just call display->mark(idx) / display->unmark(idx)
    //      maye display->swap(idx1, idx2)
    //      and display would hold list of elements to mark,
    //      would also implement delay whenever an access is made
    m_activeIndices.insert({i, minIndex});
    for (int j = i + 1; j < in.size(); j++) {
      m_activeIndices.insert(j);
      if (in.at(j) < in.at(minIndex)) {
        m_activeIndices.erase(minIndex);
        minIndex = j;
        m_activeIndices.insert(minIndex);
      }
      // m_activeIndices.insert({i, j, minIndex});
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      m_activeIndices.erase(j);
      // TODO: uncomment after implementing area looked at
      // if (!updateDisplay(display, in, m_activeIndices)) {
      //   return;
      // }
    }
    std::swap(in.at(i), in.at(minIndex));
    m_activeIndices.erase(i);
    m_activeIndices.erase(minIndex);
    // if (!updateDisplay(display, in, m_activeIndices)) {
    //   return;
    // }
  }
}