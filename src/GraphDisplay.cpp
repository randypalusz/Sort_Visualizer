#include "GraphDisplay.hpp"
#include <SFML/Graphics.hpp>

#include <iostream>

GraphDisplay::GraphDisplay(sf::RenderWindow& window) : m_window(window) {
  // possibly update window size parameters here
  // just an empty slate for now
  m_size = window.getSize();
}

void GraphDisplay::update(const std::vector<int>& in) {
  int numBars = in.size();
  int windowWidth = m_size.x;
  int widthPerBar = windowWidth / numBars;
  std::cout << widthPerBar << std::endl;
  int currentBarPosition = 0;
  for (int i = 0; i < numBars; i++) {
    sf::RectangleShape bar = sf::RectangleShape(sf::Vector2f(10, 30));
    bar.setPosition(sf::Vector2f(currentBarPosition, 0));
    m_window.draw(bar);
    currentBarPosition += widthPerBar;
  }
}