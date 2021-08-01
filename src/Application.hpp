#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Application {
 public:
  Application() {}
  void run(int numElements);

 private:
  sf::RenderWindow m_window;
};