#ifndef SORT_ALGORITHM_HPP
#define SORT_ALGORITHM_HPP

#include "AlgorithmEnums.hpp"
#include "AlgorithmFactory.hpp"
#include "GraphDisplay.hpp"
#include <vector>
#include <iostream>

class SortAlgorithm {
 public:
  // sfml_context will be used to update the sfml window
  virtual void sort(GraphDisplay* display, std::vector<int>& in) = 0;
  // print for debugging purposes
  void print(const std::vector<int>& in);
};

class BubbleSort : public SortAlgorithm {
 public:
  void sort(GraphDisplay* display, std::vector<int>& in) override;
};

class BogoSort : public SortAlgorithm {
 public:
  void sort(GraphDisplay* display, std::vector<int>& in) override;
};

#endif