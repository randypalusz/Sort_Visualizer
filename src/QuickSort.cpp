#include "SortAlgorithm.hpp"
#include "GraphDisplay.hpp"

void QuickSort_Iterative::sort(GraphDisplay* display, std::vector<int>& in) {
#define MAX_LEVELS 300
  if (std::is_sorted(in.begin(), in.end())) {
    return;
  }

  int piv, beg[MAX_LEVELS], end[MAX_LEVELS], i = 0, L, R, swap;

  beg[0] = 0;
  end[0] = in.size();
  while (i >= 0) {
    L = beg[i];
    R = end[i] - 1;
    if (L < R) {
      piv = in.at(L);
      while (L < R) {
        while (in.at(R) >= piv && L < R) R--;
        if (L < R) {
          m_activeIndices.insert({L, R});
          in.at(L++) = in.at(R);
          if (!this->updateDisplay(display, in, m_activeIndices)) return;
        }
        while (in.at(L) <= piv && L < R) L++;
        if (L < R) {
          m_activeIndices.insert({L, R});
          in.at(R--) = in.at(L);
          if (!this->updateDisplay(display, in, m_activeIndices)) return;
        }
      }
      in.at(L) = piv;
      m_activeIndices.insert({L, R});
      if (!this->updateDisplay(display, in, m_activeIndices)) return;
      beg[i + 1] = L + 1;
      end[i + 1] = end[i];
      end[i++] = L;
      if (end[i] - beg[i] > end[i - 1] - beg[i - 1]) {
        swap = beg[i];
        beg[i] = beg[i - 1];
        beg[i - 1] = swap;
        swap = end[i];
        end[i] = end[i - 1];
        end[i - 1] = swap;
      }
    } else {
      i--;
    }
  }
}

void QuickSort::sort(GraphDisplay* display, std::vector<int>& in) {
  if (!std::is_sorted(in.begin(), in.end())) {
    this->quicksort(display, in, 0, in.size() - 1);
  }
}

bool QuickSort::quicksort(GraphDisplay* display, std::vector<int>& in, int lo,
                          int hi) {
  if (lo < hi) {
    int partitionIndex = this->partition(display, in, lo, hi);
    // if updateDisplay returns false (close event found), keep returning false
    // up the tree until back in main
    if (partitionIndex == -1) return false;
    if (!this->quicksort(display, in, lo, partitionIndex - 1)) return false;
    if (!this->quicksort(display, in, partitionIndex + 1, hi)) return false;
  }
  return true;
}

int QuickSort::partition(GraphDisplay* display, std::vector<int>& in, int lo,
                         int hi) {
  int pivot = in.at(hi);
  int leftPtr = lo;
  for (int rightPtr = lo; rightPtr <= hi; rightPtr++) {
    if (in.at(rightPtr) < pivot) {
      std::swap(in.at(leftPtr), in.at(rightPtr));
      m_activeIndices.insert({leftPtr, rightPtr});
      if (!this->updateDisplay(display, in, m_activeIndices)) return -1;
      leftPtr++;
    }
  }
  std::swap(in.at(leftPtr), in.at(hi));
  m_activeIndices.insert({leftPtr, hi});
  if (!this->updateDisplay(display, in, m_activeIndices)) return -1;
  return leftPtr;
}