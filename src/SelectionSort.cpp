#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

#include <vector>

void SelectionSort::sort(GraphDisplay* display, std::vector<int>& in) {
  int minIndex = 0;
  for (int i = 0; i < (in.size() - 1); i++) {
    minIndex = in.at(i);
    for (int j = i + 1; j < in.size(); j++) {
      if (in.at(j) < in.at(minIndex)) {
        minIndex = j;
      }
      // TODO: uncomment after implementing area looked at
      // if (!updateDisplay(display, in)) {
      //   return;
      // }
    }
    std::swap(in.at(i), in.at(minIndex));
    if (!updateDisplay(display, in)) {
      return;
    }
  }
}