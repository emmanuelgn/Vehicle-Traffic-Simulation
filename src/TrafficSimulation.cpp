#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "Car.h"

int main() {
    // Initialize the random seed
    srand(static_cast<unsigned>(time(0)));

    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Traffic Simulation");

    // Lane width
    float laneWidth = 50.0f;

    // Define lane positions
    std::vector<float> lanePositions = {100.0f, 200.0f, 300.0f, 400.0f, 500.0f};

    // Create multiple cars
    std::vector<Car> cars;
    std::vector<sf::RectangleShape> carShapes;
    std::vector<float> carSpeeds;  // Stores the individual speed of each car

    for (size_t i = 0; i < lanePositions.size(); ++i) {
        Car car(i + 1, 50.0f);
        cars.push_back(car);

        sf::RectangleShape carShape(sf::Vector2f(30.0f, 100.0f));
        carShape.setFillColor(sf::Color::Blue);

        // Center the car in the lane
        carShape.setPosition(lanePositions[i] - carShape.getSize().x / 2, 600.0f);
        carShapes.push_back(carShape);

        // Generate random speed between 2.0f and 10.0f
        float carSpeed = 2.0f + static_cast<float>(rand()) / (RAND_MAX / 9.0f);
        carSpeeds.push_back(carSpeed);
    }

    float deltaTime = 0.01f;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Update car positions with their individual speeds
        for (size_t i = 0; i < cars.size(); ++i) {
            carShapes[i].move(0, -carSpeeds[i] * deltaTime);

            if (carShapes[i].getPosition().y + carShapes[i].getSize().y < 0) {
                // Reposition the car at the bottom of the screen
                carShapes[i].setPosition(carShapes[i].getPosition().x, 600.0f);

                // Assign a new random speed between 2.0f and 10.0f
                carSpeeds[i] = 2.0f + static_cast<float>(rand()) / (RAND_MAX / 9.0f);
            }
        }

        // Clear the window with a black background
        window.clear(sf::Color::Black);

        // Draw the road lanes
        for (const auto &lanePos : lanePositions) {
            sf::RectangleShape lane(sf::Vector2f(laneWidth, 600.0f));
            lane.setFillColor(sf::Color(100, 100, 100));  // Gray for asphalt
            lane.setPosition(lanePos - laneWidth / 2, 0);
            window.draw(lane);
        }

        // Draw the cars
        for (const auto &carShape : carShapes) {
            window.draw(carShape);
        }

        // Display the updated content
        window.display();
    }

    return 0;
}
