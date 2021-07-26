#include "SortAlgorithm.hpp"

void QuickSort::sort(GraphDisplay* display, std::vector<int>& in) {
#define MAX_LEVELS 300

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
          in.at(L++) = in.at(R);
          if (!this->updateDisplay(display, in)) return;
        }
        while (in.at(L) <= piv && L < R) L++;
        if (L < R) {
          in.at(R--) = in.at(L);
          if (!this->updateDisplay(display, in)) return;
        }
      }
      in.at(L) = piv;
      if (!this->updateDisplay(display, in)) return;
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