#include <vector>
#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

void BubbleSort::sort(GraphDisplay* display, std::vector<int>& in) {
  bool swapOccurred = false;
  do {
    swapOccurred = false;
    for (int i = 0; i < in.size() - 1; i++) {
      if (in.at(i + 1) < in.at(i)) {
        std::swap(in.at(i), in.at(i + 1));
        if (display) {
          display->update(in);
        }
        swapOccurred = true;
      }
    }
  } while (swapOccurred);
}