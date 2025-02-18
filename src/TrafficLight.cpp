// Copyright 2025 <Emmanuel Notargiacomo>

#include "TrafficLight.h"

TrafficLight::TrafficLight(float x, float y, float switchTime, bool isVertical)
        : state(LightState::RED), timer(0.0f), switchTime(switchTime), vertical(isVertical) {
    // Configure the traffic light shape
    lightShape.setSize(sf::Vector2f(20.0f, 50.0f));
    lightShape.setPosition(x, y);
    lightShape.setFillColor(sf::Color::Red);
}

void TrafficLight::update(float deltaTime) {
    timer += deltaTime;  // Increment the timer
    if (timer >= switchTime) {
        // Toggle the traffic light state
        state = (state == LightState::RED) ? LightState::GREEN : LightState::RED;
        lightShape.setFillColor((state == LightState::GREEN) ? sf::Color::Green : sf::Color::Red);
        timer = 0.0f;  // Reset the timer
    }
}

void TrafficLight::draw(sf::RenderWindow &window) const {
    window.draw(lightShape);
}

bool TrafficLight::canProceed() const {
    return state == LightState::GREEN;
}

sf::Vector2f TrafficLight::getPosition() const {
    return lightShape.getPosition();
}

bool TrafficLight::isVertical() const {
    return vertical;
}

float TrafficLight::getSwitchTime() const {
    return switchTime;
}
