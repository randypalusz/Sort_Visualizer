#ifndef SORT_ALGORITHM_HPP
#define SORT_ALGORITHM_HPP

#include <atomic>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <thread>

#include "AlgorithmEnums.hpp"
#include "GraphDisplay.hpp"

class GraphDisplay;

class SortAlgorithm {
 public:
  // Template pattern - preSortChecks will determine whether the thread should
  // run, and startSortThread must be overridden
  inline void run(GraphDisplay* display, std::vector<int>& in) {
    if (!preSortChecks(display, in)) {
      return;
    }
    startSortThread(display, in);
  }
  virtual ~SortAlgorithm(){};
  virtual Algorithm getEnumType() = 0;
  // print for debugging purposes
  static void print(const std::vector<int>& in);
  inline void terminateSort() {
    m_threadShouldEnd = true;
    m_sortTerminated = true;
    if (m_thread.joinable()) {
      m_thread.join();
      m_threadActive = false;
    }
    return;
  }
  bool m_paused = false;

 protected:
  // functional intent is to start the sort thread and assign it to m_thread
  virtual void startSortThread(GraphDisplay* display, std::vector<int>& in) = 0;
  [[nodiscard]] bool preSortChecks(GraphDisplay* display, std::vector<int>& in);
  // this will be the sort function that the top-level sort starts a thread on
  virtual void sort(GraphDisplay* display) = 0;
  // returns whether sort should continue based on m_paused + std::is_sorted
  bool sortShouldContinue(const std::vector<int>& in);
  bool threadShouldStop();
  std::atomic<bool> m_threadShouldEnd = false;
  bool m_threadActive = false;
  // variable that prevents the SortAlgorithm instance from running
  // when set to true
  bool m_sortTerminated = false;
  std::thread m_thread;
};

class BubbleSort : public SortAlgorithm {
 public:
  void startSortThread(GraphDisplay* display, std::vector<int>& in) override;
  inline Algorithm getEnumType() override { return Algorithm::BUBBLE; }

 protected:
  void sort(GraphDisplay* display) override;
};

class BogoSort : public SortAlgorithm {
 public:
  void startSortThread(GraphDisplay* display, std::vector<int>& in) override;
  inline Algorithm getEnumType() override { return Algorithm::BOGO; }

 protected:
  void sort(GraphDisplay* display) override;
};

class QuickSort : public SortAlgorithm {
 public:
  void startSortThread(GraphDisplay* display, std::vector<int>& in) override;
  inline Algorithm getEnumType() override { return Algorithm::QUICK; }

 protected:
  void sort(GraphDisplay* display) override;
  bool quicksort(GraphDisplay* display, int lo, int hi);
  int partition(GraphDisplay* display, int lo, int hi);
};

class QuickSort_Iterative : public SortAlgorithm {
 public:
  void startSortThread(GraphDisplay* display, std::vector<int>& in) override;
  inline Algorithm getEnumType() override { return Algorithm::QUICK_ITERATIVE; }

 protected:
  void sort(GraphDisplay* display) override;
};

class SelectionSort : public SortAlgorithm {
 public:
  void startSortThread(GraphDisplay* display, std::vector<int>& in) override;
  inline Algorithm getEnumType() override { return Algorithm::SELECTION; }

 protected:
  void sort(GraphDisplay* display) override;
};

#endif