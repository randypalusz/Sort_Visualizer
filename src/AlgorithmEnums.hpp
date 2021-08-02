#ifndef ALGORITHM_ENUMS
#define ALGORITHM_ENUMS
enum class Algorithm { BUBBLE, SELECTION, QUICK_ITERATIVE, BOGO, QUICK };
// enum class Command { CLOSE_WINDOW, REGENERATE_VECTOR, NEXT_ALGORITHM,
// NO_EVENT };

inline Algorithm& operator++(Algorithm& a, int) {
  switch (a) {
    case Algorithm::BUBBLE:
      a = Algorithm::SELECTION;
      break;
    case Algorithm::SELECTION:
      a = Algorithm::QUICK_ITERATIVE;
      break;
    case Algorithm::QUICK_ITERATIVE:
      a = Algorithm::BOGO;
      break;
    case Algorithm::BOGO:
      a = Algorithm::QUICK;
      break;
    case Algorithm::QUICK:
      a = Algorithm::BUBBLE;
      break;
  }
  return a;
}
#endif
