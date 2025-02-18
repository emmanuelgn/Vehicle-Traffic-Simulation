// Copyright 2025 <Emmanuel Notargiacomo>

#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

enum class LightState { RED, GREEN };

class TrafficLight {
 public:
    TrafficLight(float x, float y, float switchTime, bool isVertical);

    void update(float deltaTime);               // Update the traffic light state
    void draw(sf::RenderWindow &window) const;  // Draw the traffic light
    bool canProceed() const;                    // Check if the light is green
    sf::Vector2f getPosition() const;           // Get the position of the traffic light
    bool isVertical() const;                    // Check if this traffic light is for vertical lanes
    float getSwitchTime() const;                // Get the switch time of the traffic light

 private:
    sf::RectangleShape lightShape;
    LightState state;
    float timer;
    float switchTime;
    bool vertical;  // True if this traffic light controls vertical lanes, false for horizontal
};

#endif  // TRAFFIC_LIGHT_H