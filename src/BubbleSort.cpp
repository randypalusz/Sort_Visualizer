#include "BubbleSort.hpp"
#include <vector>

void BubbleSort::sort(void* sfml_context, std::vector<int>& in) {
  bool swapOccurred = false;
  // original vector
  this->print(in);
  do {
    swapOccurred = false;
    for (int i = 0; i < in.size() - 1; i++) {
      if (in.at(i + 1) < in.at(i)) {
        std::swap(in.at(i), in.at(i + 1));
        this->print(in);
        // sfml_context->update(in)
        swapOccurred = true;
      }
    }
  } while (swapOccurred);
}