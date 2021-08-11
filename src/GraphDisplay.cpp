#include "GraphDisplay.hpp"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <unordered_set>

#include "util/Utility.hpp"
#include "util/InputHandler.hpp"

GraphDisplay::GraphDisplay(sf::RenderWindow& window, std::vector<int>& in,
                           int waitTimeInMillis)
    : m_window(window), m_sortVector(in), m_waitTimeInMillis(waitTimeInMillis) {
  // updating here as it should be a one-time update - SFML handles stretching
  m_size = window.getSize();
  m_inputHandler = new InputHandler();
}
GraphDisplay::~GraphDisplay() { delete m_inputHandler; }

bool GraphDisplay::update() {
  // std::shared_ptr<Command> cmd = m_inputHandler->pollForEvents(m_window);
  // if (!cmd->execute(m_window, nullptr, nullptr, nullptr)) {
  //   return false;
  // }
  m_window.clear(sf::Color::Blue);
  int numBars = m_sortVector.size();
  float widthPerBar = (float)m_size.x / (float)numBars;
  float min = *(std::min_element(m_sortVector.begin(), m_sortVector.end()));
  float max = *(std::max_element(m_sortVector.begin(), m_sortVector.end()));
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
        normalize((float)m_sortVector.at(i), min, max, newMin, newMax);
    sf::RectangleShape bar = sf::RectangleShape(
        sf::Vector2f(widthPerBar - widthBuffer, normalizedHeight));
    if (m_activeIndices.find(i) != m_activeIndices.end()) {
      bar.setFillColor(sf::Color::Red);
    }
    bar.setPosition(sf::Vector2f(
        currentBarX, (m_size.y - normalizedHeight) - topBottomBorder));
    m_window.draw(bar);
    currentBarX += widthPerBar;
  }
  m_window.display();
  return true;
}