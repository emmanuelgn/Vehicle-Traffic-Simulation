// Copyright 2025 <Emmanuel Notargiacomo>

#include "TrafficLight.h"

TrafficLight::TrafficLight(float x, float y, float switchTime)
    : state(LightState::RED), timer(0.0f), switchTime(switchTime) {
    lightShape.setSize(sf::Vector2f(20.0f, 50.0f));
    lightShape.setPosition(x, y);
    lightShape.setFillColor(sf::Color::Red);
}

void TrafficLight::update(float deltaTime) {
    timer += deltaTime;
    if (timer >= switchTime) {
        state = (state == LightState::RED) ? LightState::GREEN : LightState::RED;
        lightShape.setFillColor((state == LightState::GREEN) ? sf::Color::Green : sf::Color::Red);
        timer = 0.0f;
    }
}

void TrafficLight::draw(sf::RenderWindow& window) {
    window.draw(lightShape);
}

bool TrafficLight::canProceed() const {
    return state == LightState::GREEN;
}
