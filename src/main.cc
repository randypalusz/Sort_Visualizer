#include <stdlib.h>
#include <iostream>

#include "Application.hpp"
int main(int argc, char** argv) {
  const int numElements = atoi(argv[1]);
  Application app{};
  app.run(numElements);
}