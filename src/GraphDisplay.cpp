#include "GraphDisplay.hpp"
#include "util/Utility.hpp"
#include <SFML/Graphics.hpp>

#include <algorithm>
#include <iostream>

GraphDisplay::GraphDisplay(sf::RenderWindow& window) : m_window(window) {
  // updating here as it should be a one-time update - SFML handles stretching
  m_size = window.getSize();
}

void GraphDisplay::update(const std::vector<int>& in) {
  int numBars = in.size();
  int widthPerBar = m_size.x / numBars;
  float min = *(std::min_element(in.begin(), in.end()));
  float max = *(std::max_element(in.begin(), in.end()));
  float topBottomBorder = 25.0f;
  // ensure the height of the bar doesn't reach the top of the window
  float newMax = m_size.y - (2.0f * topBottomBorder);
  // ensure the lowest value in the list is still visible
  float newMin = 10.0f;
  // x coordinate of the current bar
  float currentBarX = 0.0f;
  for (int i = 0; i < numBars; i++) {
    float normalizedHeight =
        normalize((float)in.at(i), min, max, newMin, newMax);
    // TODO: modulate width of the bar based on how many elements there are
    sf::RectangleShape bar =
        sf::RectangleShape(sf::Vector2f(10, normalizedHeight));
    bar.setPosition(sf::Vector2f(
        currentBarX, (m_size.y - normalizedHeight) - topBottomBorder));
    m_window.draw(bar);
    currentBarX += widthPerBar;
  }
}