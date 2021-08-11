#ifndef SORT_ALGORITHM_HPP
#define SORT_ALGORITHM_HPP

#include <iostream>
#include <unordered_set>
#include <vector>
#include <thread>

#include "AlgorithmEnums.hpp"
#include "GraphDisplay.hpp"

class GraphDisplay;

class SortAlgorithm {
 public:
  // display is passed as a pointer to allow for no display update when nullptr
  virtual void sort(GraphDisplay* display, std::vector<int>& in) = 0;
  virtual ~SortAlgorithm(){};
  virtual Algorithm getEnumType() = 0;
  // print for debugging purposes
  static void print(const std::vector<int>& in);
  inline void waitForThreadToFinish() {
    if (m_threadActive) {
      m_thread.join();
    }
    return;
  }
  bool m_paused = false;

 protected:
  // updates the display if display is not nullptr
  // returns false is update is interrupted by window close/keypress
  // returns true if display is nullptr or update is uninterrupted
  // TODO: remove this
  bool updateDisplay(GraphDisplay* display, std::vector<int>& in,
                     std::unordered_set<int>& activeIndices);
  // this will be the sort function that the top-level sort starts a thread on
  // TODO: make this pure virtual after ready to implement in all child classes
  virtual void internalSort(GraphDisplay* display, std::vector<int>& in){};
  // returns whether sort should continue based on m_paused + std::is_sorted
  bool sortShouldContinue(const std::vector<int>& in);
  bool m_threadActive = false;
  std::thread m_thread;
};

class BubbleSort : public SortAlgorithm {
 public:
  void sort(GraphDisplay* display, std::vector<int>& in) override;
  inline Algorithm getEnumType() override { return Algorithm::BUBBLE; }

 private:
  std::unordered_set<int> m_activeIndices;
};

class BogoSort : public SortAlgorithm {
 public:
  void sort(GraphDisplay* display, std::vector<int>& in) override;
  inline Algorithm getEnumType() override { return Algorithm::BOGO; }

 private:
  std::unordered_set<int> m_activeIndices;
};

class QuickSort : public SortAlgorithm {
 public:
  void sort(GraphDisplay* display, std::vector<int>& in) override;
  inline Algorithm getEnumType() override { return Algorithm::QUICK; }

 private:
  bool quicksort(GraphDisplay* display, std::vector<int>& in, int lo, int hi);
  int partition(GraphDisplay* display, std::vector<int>& in, int lo, int hi);
  std::unordered_set<int> m_activeIndices;
};

class QuickSort_Iterative : public SortAlgorithm {
 public:
  void sort(GraphDisplay* display, std::vector<int>& in) override;
  inline Algorithm getEnumType() override { return Algorithm::QUICK_ITERATIVE; }

 private:
  std::unordered_set<int> m_activeIndices;
};

class SelectionSort : public SortAlgorithm {
 public:
  void sort(GraphDisplay* display, std::vector<int>& in) override;
  inline Algorithm getEnumType() override { return Algorithm::SELECTION; }

 protected:
  void internalSort(GraphDisplay* display, std::vector<int>& in) override;

 private:
  std::unordered_set<int> m_activeIndices;
};

#endif