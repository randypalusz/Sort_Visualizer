#include "GraphDisplay.hpp"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

#include "util/Utility.hpp"

GraphDisplay::GraphDisplay(sf::RenderWindow& window, int waitTimeInMillis)
    : m_window(window), m_waitTimeInMillis(waitTimeInMillis) {
  // updating here as it should be a one-time update - SFML handles stretching
  m_size = window.getSize();
}

bool GraphDisplay::update(const std::vector<int>& in) {
  sf::Event event;
  // TODO: change return value of update() + pollForEvents() -> return status
  //       based on key pressed
  //       (e.g. if "R" is pressed, regenerate the vector and run the sort again
  //       but if window is closed, return something different to reflect that)
  //       ... So maybe something like <enum class WindowEventStatus>
  if (WindowManager::pollForEvents(m_window) == WindowEvent::CLOSE_WINDOW) {
    m_window.close();
    return false;
  }

  m_window.clear(sf::Color::Blue);
  int numBars = in.size();
  float widthPerBar = (float)m_size.x / (float)numBars;
  float min = *(std::min_element(in.begin(), in.end()));
  float max = *(std::max_element(in.begin(), in.end()));
  float topBottomBorder = 25.0f;
  float widthBuffer = 1.0f;
  // ensure the height of the bar doesn't reach the top of the window
  float newMax = m_size.y - (2.0f * topBottomBorder);
  // ensure the lowest value in the list is still visible
  float newMin = 10.0f;
  // x coordinate of the current bar
  float currentBarX = 0.0f;
  for (int i = 0; i < numBars; i++) {
    float normalizedHeight =
        normalize((float)in.at(i), min, max, newMin, newMax);
    sf::RectangleShape bar = sf::RectangleShape(
        sf::Vector2f(widthPerBar - widthBuffer, normalizedHeight));
    bar.setPosition(sf::Vector2f(
        currentBarX, (m_size.y - normalizedHeight) - topBottomBorder));
    m_window.draw(bar);
    currentBarX += widthPerBar;
  }
  m_window.display();
  return true;
}