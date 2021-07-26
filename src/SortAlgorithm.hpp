#ifndef SORT_ALGORITHM_HPP
#define SORT_ALGORITHM_HPP

#include "AlgorithmEnums.hpp"
#include "AlgorithmFactory.hpp"
#include "GraphDisplay.hpp"
#include <vector>
#include <iostream>

class SortAlgorithm {
 public:
  // display is passed as a pointer to allow for no display update when nullptr
  virtual void sort(GraphDisplay* display, std::vector<int>& in) = 0;

 protected:
  // print for debugging purposes
  void print(const std::vector<int>& in);
  // updates the display if display is not nullptr
  // returns false is update is interrupted by window close/keypress
  // returns true if display is nullptr or update is uninterrupted
  bool updateDisplay(GraphDisplay* display, const std::vector<int>& in);
};

class BubbleSort : public SortAlgorithm {
 public:
  void sort(GraphDisplay* display, std::vector<int>& in) override;
};

class BogoSort : public SortAlgorithm {
 public:
  void sort(GraphDisplay* display, std::vector<int>& in) override;
};

class QuickSort : public SortAlgorithm {
 public:
  void sort(GraphDisplay* display, std::vector<int>& in) override;
};

#endif