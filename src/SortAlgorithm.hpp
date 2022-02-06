#ifndef SORT_ALGORITHM_HPP
#define SORT_ALGORITHM_HPP

#include <atomic>
#include <iostream>
#include <thread>
#include <unordered_set>
#include <vector>

#include "AlgorithmEnums.hpp"
#include "GraphDisplay.hpp"

class GraphDisplay;

class SortAlgorithm {
 public:
  // Template pattern - preSortChecks will determine whether the thread should
  // run, and startSortThread must be overridden
  inline void run(GraphDisplay* display, std::vector<int>& in) {
    if (!init(display, in)) {
      return;
    }
    startSortThread(display);
  }
  virtual ~SortAlgorithm(){};
  virtual Algorithm getEnumType() = 0;
  // print for debugging purposes
  static void print(const std::vector<int>& in);
  inline bool isThreadActive() { return m_state == AlgorithmState::RUNNING; }
  inline void togglePaused() {
    switch (m_state.load()) {
      case AlgorithmState::RUNNING:
        setState(AlgorithmState::PAUSED);
        return;
      case AlgorithmState::PAUSED:
        setState(AlgorithmState::RUNNING);
        return;
      default:
        break;
    }
  }
  inline void setState(AlgorithmState state) { m_state.store(state); }
  inline void setStep() { m_step.store(true); }
  inline void terminateSort(bool preventRestart = true) {
    setState(AlgorithmState::SHOULD_END);
    if (m_thread.joinable()) {
      m_thread.join();
      setState(AlgorithmState::INACTIVE);
    }
    if (preventRestart) setState(AlgorithmState::KILLED);
    return;
  }

 protected:
  void tearDown(GraphDisplay* display);
  // functional intent is to start the sort thread and assign it to m_thread
  virtual void startSortThread(GraphDisplay* display) = 0;
  [[nodiscard]] bool init(GraphDisplay* display, std::vector<int>& in);
  // this will be the sort function that the top-level sort starts a thread on
  virtual void sort(GraphDisplay* display) = 0;
  // returns whether sort should continue based on m_paused + std::is_sorted
  bool sortShouldContinue(const std::vector<int>& in);
  // returns whether thread should end/resets display if it should
  void handleAtomics(GraphDisplay* display);
  std::atomic<AlgorithmState> m_state = AlgorithmState::INACTIVE;
  std::atomic<bool> m_step = false;
  std::thread m_thread;
};

class BubbleSort : public SortAlgorithm {
 public:
  void startSortThread(GraphDisplay* display) override;
  inline Algorithm getEnumType() override { return Algorithm::BUBBLE; }

 protected:
  void sort(GraphDisplay* display) override;
};

class BogoSort : public SortAlgorithm {
 public:
  void startSortThread(GraphDisplay* display) override;
  inline Algorithm getEnumType() override { return Algorithm::BOGO; }

 protected:
  void sort(GraphDisplay* display) override;
};

class QuickSort : public SortAlgorithm {
 public:
  void startSortThread(GraphDisplay* display) override;
  inline Algorithm getEnumType() override { return Algorithm::QUICK; }

 protected:
  void sort(GraphDisplay* display) override;
  bool quicksort(GraphDisplay* display, int lo, int hi);
  int partition(GraphDisplay* display, int lo, int hi);
};

class QuickSort_Iterative : public SortAlgorithm {
 public:
  void startSortThread(GraphDisplay* display) override;
  inline Algorithm getEnumType() override { return Algorithm::QUICK_ITERATIVE; }

 protected:
  void sort(GraphDisplay* display) override;
};

class SelectionSort : public SortAlgorithm {
 public:
  void startSortThread(GraphDisplay* display) override;
  inline Algorithm getEnumType() override { return Algorithm::SELECTION; }

 protected:
  void sort(GraphDisplay* display) override;
};

class CocktailSort : public SortAlgorithm {
 public:
  void startSortThread(GraphDisplay* display) override;
  inline Algorithm getEnumType() override { return Algorithm::COCKTAIL; }

 protected:
  void sort(GraphDisplay* display) override;
};

#endif