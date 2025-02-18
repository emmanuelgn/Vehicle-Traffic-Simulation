// Copyright 2025 <Emmanuel Notargiacomo>

#ifndef INCLUDE_TRAFFICLIGHT_H_
#define INCLUDE_TRAFFICLIGHT_H_

#include <ctime>
#include <SFML/Graphics.hpp>

enum class LightState { RED, GREEN };

class TrafficLight {
 private:
    sf::RectangleShape lightShape;
    LightState state;
    float timer;
    float switchTime;

 public:
    TrafficLight(float x, float y, float switchTime);

    void draw(sf::RenderWindow &window) const;
    void draw(sf::RenderWindow &window);
    bool canProceed() const;
};

#endif  // INCLUDE_TRAFFICLIGHT_H_

