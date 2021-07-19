#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

#include "SortAlgorithm.hpp"
#include <vector>

class BubbleSort : public SortAlgorithm {
 public:
  void sort(void* sfml_context, std::vector<int>& in) override;
};

#endif