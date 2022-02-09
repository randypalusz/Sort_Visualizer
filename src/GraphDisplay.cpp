#include "GraphDisplay.hpp"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <unordered_set>

#include "util/Utility.hpp"

GraphDisplay::GraphDisplay(sf::RenderWindow& window, std::vector<int>& in,
                           double startingDelayInSeconds)
    : m_window(window), m_sortVector(in), m_delayInSeconds(startingDelayInSeconds) {
  // updating here as it should be a one-time update - SFML handles stretching
  m_windowSize = window.getSize();
  // ensure the height of the bar doesn't reach the top of the window
  m_adjustedMax = m_windowSize.y - (2.0f * m_topBottomBorder);
  regenerateDisplayValues();
}
GraphDisplay::~GraphDisplay() {}

bool GraphDisplay::update() {
  m_window.clear(sf::Color::Blue);
  // x coordinate of the current bar
  float currentBarX = 0.0f;
  for (int i = 0; i < m_numBars; i++) {
    float normalizedHeight = normalize((float)m_sortVector.at(i), m_currentMinValue,
                                       m_currentMaxValue, m_adjustedMin, m_adjustedMax);
    sf::RectangleShape bar =
        sf::RectangleShape(sf::Vector2f(m_widthPerBar - m_widthBuffer, normalizedHeight));
    // using range-based for loop here instead of find - with std::find,
    // value could've been erased from map between find and access
    for (auto it = m_activeIndices.begin(); it != m_activeIndices.end(); it++) {
      if (it->first == i) {
        bar.setFillColor(it->second);
      }
    }
    for (auto it = m_watchedIndices.begin(); it != m_watchedIndices.end(); it++) {
      if (*(it->first) == i) {
        bar.setFillColor(it->second);
      }
    }
    bar.setPosition(sf::Vector2f(
        currentBarX, (m_windowSize.y - normalizedHeight) - m_topBottomBorder));
    m_window.draw(bar);
    currentBarX += m_widthPerBar;
  }
  m_window.display();
  return true;
}

void GraphDisplay::regenerateDisplayValues() {
  m_numBars = m_sortVector.size();
  m_widthPerBar = (float)m_windowSize.x / (float)m_numBars;
  m_currentMinValue = *(std::min_element(m_sortVector.begin(), m_sortVector.end()));
  m_currentMaxValue = *(std::max_element(m_sortVector.begin(), m_sortVector.end()));
}

void GraphDisplay::onAccess() { Timing::preciseSleep(m_delayInSeconds); }
