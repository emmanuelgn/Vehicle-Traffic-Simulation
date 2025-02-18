#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "Car.h"

int main() {
    // Initialize the random seed
    srand(static_cast<unsigned>(time(0)));

    // Create the window with increased size
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Traffic Simulation");

    // Lane width - thinner roads
    float laneWidth = 30.0f;

    // Define vertical and horizontal lane positions
    std::vector<float> verticalLanes = {150.0f, 300.0f, 450.0f, 600.0f, 750.0f};
    std::vector<float> horizontalLanes = {150.0f, 300.0f, 450.0f, 600.0f};

    // Create multiple cars
    std::vector<Car> cars;
    std::vector<sf::RectangleShape> carShapes;
    std::vector<float> carSpeeds;

    for (size_t i = 0; i < verticalLanes.size(); ++i) {
        Car car(i + 1, 50.0f);
        cars.push_back(car);

        sf::RectangleShape carShape(sf::Vector2f(20.0f, 20.0f));
        carShape.setFillColor(sf::Color::Blue);

        carShape.setPosition(verticalLanes[i] - carShape.getSize().x / 2, 800.0f);
        carShapes.push_back(carShape);

        float carSpeed = 2.0f + static_cast<float>(rand()) / (RAND_MAX / 9.0f);
        carSpeeds.push_back(carSpeed);
    }

    for (size_t i = 0; i < horizontalLanes.size(); ++i) {
        Car car(i + verticalLanes.size() + 1, 50.0f);
        cars.push_back(car);

        sf::RectangleShape carShape(sf::Vector2f(20.0f, 20.0f));
        carShape.setFillColor(sf::Color::Red);

        carShape.setPosition(0, horizontalLanes[i] - carShape.getSize().y / 2);
        carShapes.push_back(carShape);

        float carSpeed = 2.0f + static_cast<float>(rand()) / (RAND_MAX / 9.0f);
        carSpeeds.push_back(carSpeed);
    }

    float deltaTime = 0.01f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        for (size_t i = 0; i < verticalLanes.size(); ++i) {
            carShapes[i].move(0, -carSpeeds[i] * deltaTime);
            if (carShapes[i].getPosition().y + carShapes[i].getSize().y < 0) {
                carShapes[i].setPosition(carShapes[i].getPosition().x, 800.0f);
                carSpeeds[i] = 2.0f + static_cast<float>(rand()) / (RAND_MAX / 9.0f);
            }
        }

        for (size_t i = verticalLanes.size(); i < cars.size(); ++i) {
            carShapes[i].move(carSpeeds[i] * deltaTime, 0);
            if (carShapes[i].getPosition().x > 1000.0f) {
                carShapes[i].setPosition(0, carShapes[i].getPosition().y);
                carSpeeds[i] = 2.0f + static_cast<float>(rand()) / (RAND_MAX / 9.0f);
            }
        }

        window.clear(sf::Color::Black);

        for (const auto &lanePos : verticalLanes) {
            sf::RectangleShape lane(sf::Vector2f(laneWidth, 800.0f));
            lane.setFillColor(sf::Color(100, 100, 100));
            lane.setPosition(lanePos - laneWidth / 2, 0);
            window.draw(lane);
        }
        for (const auto &lanePos : horizontalLanes) {
            sf::RectangleShape lane(sf::Vector2f(1000.0f, laneWidth));
            lane.setFillColor(sf::Color(100, 100, 100));
            lane.setPosition(0, lanePos - laneWidth / 2);
            window.draw(lane);
        }

        for (const auto &carShape : carShapes) {
            window.draw(carShape);
        }

        window.display();
    }

    return 0;
}
