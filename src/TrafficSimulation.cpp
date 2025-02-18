#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "Car.h"
#include "TrafficLight.h"

int main() {
    // Initialize random seed
    srand(static_cast<unsigned>(time(0)));

    // Create a larger window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Traffic Simulation");

    // Lane width
    float laneWidth = 30.0f;

    // Define positions for vertical and horizontal lanes
    std::vector<float> verticalLanes = {150.0f, 300.0f, 450.0f, 600.0f, 750.0f};
    std::vector<float> horizontalLanes = {150.0f, 300.0f, 450.0f, 600.0f};

    // Create multiple cars
    std::vector<Car> cars;
    std::vector<sf::RectangleShape> carShapes;
    std::vector<float> carSpeeds;

    // Create cars for vertical lanes
    for (size_t i = 0; i < verticalLanes.size(); ++i) {
        Car car(i + 1, 50.0f);
        cars.push_back(car);

        sf::RectangleShape carShape(sf::Vector2f(20.0f, 20.0f));
        carShape.setFillColor(sf::Color::Blue);

        carShape.setPosition(verticalLanes[i] - carShape.getSize().x / 2, 800.0f);
        carShapes.push_back(carShape);

        // Assign random speed to the car
        float carSpeed = 2.0f + static_cast<float>(rand()) / (RAND_MAX / 9.0f);
        carSpeeds.push_back(carSpeed);
    }

    // Create cars for horizontal lanes
    for (size_t i = 0; i < horizontalLanes.size(); ++i) {
        Car car(i + verticalLanes.size() + 1, 50.0f);
        cars.push_back(car);

        sf::RectangleShape carShape(sf::Vector2f(20.0f, 20.0f));
        carShape.setFillColor(sf::Color::Red);

        carShape.setPosition(0, horizontalLanes[i] - carShape.getSize().y / 2);
        carShapes.push_back(carShape);

        // Assign random speed to the car
        float carSpeed = 2.0f + static_cast<float>(rand()) / (RAND_MAX / 9.0f);
        carSpeeds.push_back(carSpeed);
    }

    // Create traffic lights at intersections
    std::vector<TrafficLight> trafficLights;
    for (size_t i = 0; i < verticalLanes.size(); ++i) {
        for (size_t j = 0; j < horizontalLanes.size(); ++j) {
            // Create a traffic light for vertical lanes
            trafficLights.emplace_back(verticalLanes[i], horizontalLanes[j], 10.0f,
                                       true);  // 10 seconds switch time
            // Create a traffic light for horizontal lanes (opposite state)
            trafficLights.emplace_back(verticalLanes[i], horizontalLanes[j], 10.0f, false);

            // Ensure opposite states for vertical and horizontal lights
            trafficLights[trafficLights.size() - 2].update(0);  // Force update to set initial state
            trafficLights[trafficLights.size() - 1].update(0);  // Force update to set initial state
            if (trafficLights[trafficLights.size() - 2].canProceed()) {
                trafficLights[trafficLights.size() - 1].update(
                        trafficLights[trafficLights.size() - 1].getSwitchTime());
            } else {
                trafficLights[trafficLights.size() - 2].update(
                        trafficLights[trafficLights.size() - 2].getSwitchTime());
            }
        }
    }

    float deltaTime = 0.01f;  // Fixed time step for simulation
    sf::Clock clock;

    // Main simulation loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Calculate real delta time
        float deltaTime2 = clock.restart().asSeconds();

        // Update traffic lights
        for (auto &trafficLight : trafficLights) {
            trafficLight.update(deltaTime2);
        }

        // Update cars in vertical lanes
        for (size_t i = 0; i < verticalLanes.size(); ++i) {
            // Check if the car is near a red traffic light for vertical lanes
            bool canMove = true;
            for (const auto &trafficLight : trafficLights) {
                if (trafficLight.isVertical() && !trafficLight.canProceed() &&
                    carShapes[i].getPosition().y < trafficLight.getPosition().y + 50.0f &&
                    carShapes[i].getPosition().y > trafficLight.getPosition().y - 50.0f) {
                    canMove = false;
                    break;
                }
            }

            // Move the car if allowed
            if (canMove) {
                carShapes[i].move(0, -carSpeeds[i] * deltaTime);
            }

            // Reset car position if it goes off-screen
            if (carShapes[i].getPosition().y + carShapes[i].getSize().y < 0) {
                carShapes[i].setPosition(carShapes[i].getPosition().x, 800.0f);
                carSpeeds[i] = 2.0f + static_cast<float>(rand()) / (RAND_MAX / 9.0f);
            }
        }

        // Update cars in horizontal lanes
        for (size_t i = verticalLanes.size(); i < cars.size(); ++i) {
            // Check if the car is near a red traffic light for horizontal lanes
            bool canMove = true;
            for (const auto &trafficLight : trafficLights) {
                if (!trafficLight.isVertical() && !trafficLight.canProceed() &&
                    carShapes[i].getPosition().x < trafficLight.getPosition().x + 50.0f &&
                    carShapes[i].getPosition().x > trafficLight.getPosition().x - 50.0f) {
                    canMove = false;
                    break;
                }
            }

            // Move the car if allowed
            if (canMove) {
                carShapes[i].move(carSpeeds[i] * deltaTime, 0);
            }

            // Reset car position if it goes off-screen
            if (carShapes[i].getPosition().x > 1000.0f) {
                carShapes[i].setPosition(0, carShapes[i].getPosition().y);
                carSpeeds[i] = 2.0f + static_cast<float>(rand()) / (RAND_MAX / 9.0f);
            }
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw vertical lanes
        for (const auto &lanePos : verticalLanes) {
            sf::RectangleShape lane(sf::Vector2f(laneWidth, 800.0f));
            lane.setFillColor(sf::Color(100, 100, 100));
            lane.setPosition(lanePos - laneWidth / 2, 0);
            window.draw(lane);
        }

        // Draw horizontal lanes
        for (const auto &lanePos : horizontalLanes) {
            sf::RectangleShape lane(sf::Vector2f(1000.0f, laneWidth));
            lane.setFillColor(sf::Color(100, 100, 100));
            lane.setPosition(0, lanePos - laneWidth / 2);
            window.draw(lane);
        }

        // Draw cars
        for (const auto &carShape : carShapes) {
            window.draw(carShape);
        }

        // Draw traffic lights
        for (const auto &trafficLight : trafficLights) {
            trafficLight.draw(window);
        }

        // Display the window
        window.display();
    }

    return 0;
}