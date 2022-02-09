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
  inline const Algorithm getEnumType() { return m_enumType; }
  inline const std::string getName() { return m_name; }
  // print for debugging purposes
  static void print(const std::vector<int>& in);
  inline bool isThreadActive() { return m_state == AlgorithmState::RUNNING; }
  inline void togglePaused() { m_paused.store(!m_paused.load()); }
  inline AlgorithmState getState() const { return m_state.load(); }
  inline bool isPaused() const { return m_paused.load(); }
  inline void setPaused(bool val) { m_paused.store(val); }
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
  // Having a constructor here forces the subclasses to implement
  SortAlgorithm(const std::string& name, const Algorithm& algorithm)
      : m_name(name), m_enumType(algorithm) {}
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
  std::atomic<bool> m_paused = false;
  std::atomic<bool> m_step = false;
  std::thread m_thread;
  std::string m_name;
  Algorithm m_enumType;
};

class BubbleSort : public SortAlgorithm {
 public:
  BubbleSort() : SortAlgorithm("BubbleSort", Algorithm::BUBBLE) {}
  void startSortThread(GraphDisplay* display) override;

 protected:
  void sort(GraphDisplay* display) override;
};

class BogoSort : public SortAlgorithm {
 public:
  BogoSort() : SortAlgorithm("BogoSort", Algorithm::BOGO) {}
  void startSortThread(GraphDisplay* display) override;

 protected:
  void sort(GraphDisplay* display) override;
};

class QuickSort : public SortAlgorithm {
 public:
  QuickSort() : SortAlgorithm("QuickSort", Algorithm::QUICK) {}
  void startSortThread(GraphDisplay* display) override;

 protected:
  void sort(GraphDisplay* display) override;
  bool quicksort(GraphDisplay* display, int lo, int hi);
  int partition(GraphDisplay* display, int lo, int hi);
};

class QuickSort_Iterative : public SortAlgorithm {
 public:
  QuickSort_Iterative()
      : SortAlgorithm("QuickSort_Iterative", Algorithm::QUICK_ITERATIVE) {}
  void startSortThread(GraphDisplay* display) override;

 protected:
  void sort(GraphDisplay* display) override;
};

class SelectionSort : public SortAlgorithm {
 public:
  SelectionSort() : SortAlgorithm("SelectionSort", Algorithm::SELECTION) {}
  void startSortThread(GraphDisplay* display) override;

 protected:
  void sort(GraphDisplay* display) override;
};

class CocktailSort : public SortAlgorithm {
 public:
  CocktailSort() : SortAlgorithm("CocktailSort", Algorithm::COCKTAIL) {}
  void startSortThread(GraphDisplay* display) override;

 protected:
  void sort(GraphDisplay* display) override;
};

#endif