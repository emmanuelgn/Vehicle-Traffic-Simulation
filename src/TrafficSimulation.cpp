#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>

#include "Car.h"

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Traffic Simulation");

    // Set up multiple cars
    std::vector<Car> cars;
    std::vector<sf::RectangleShape> carShapes;

    // Random number generator setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.1, 0.1); // Reduced random movement range

    // Create multiple cars
    for (int i = 0; i < 5; ++i) { // Create 5 cars for example
        Car car(i + 1, 50.0f); // Car with id and speed
        cars.push_back(car);

        sf::RectangleShape carShape(sf::Vector2f(50.0f, 100.0f));
        carShape.setFillColor(sf::Color::Blue);
        carShape.setPosition(100.0f * i + 50.0f, 500.0f); // Position cars with some spacing
        carShapes.push_back(carShape);
    }

    float deltaTime = 0.01f; // Simulates time passing in smaller units for smoother animation

    // Define lane positions
    std::vector<float> lanePositions = {100.0f, 200.0f, 300.0f, 400.0f, 500.0f};

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Update car positions with constrained movement within lanes
        for (size_t i = 0; i < cars.size(); ++i) {
            float randomMoveY = dis(gen) * deltaTime * 50.0f; // Adjusted for smoother movement
            carShapes[i].move(0, randomMoveY); // Move only vertically

            // Constrain car to its lane
            carShapes[i].setPosition(lanePositions[i], carShapes[i].getPosition().y);

            // Print car position to console (optional)
            std::cout << "Car " << cars[i].getId() << " position: ("
                      << carShapes[i].getPosition().x << ", "
                      << carShapes[i].getPosition().y << ")" << std::endl;
        }

        // Clear the window with a black color
        window.clear(sf::Color::Black);

        // Draw lanes
        for (const auto& lanePos : lanePositions) {
            sf::RectangleShape lane(sf::Vector2f(10.0f, 600.0f));
            lane.setFillColor(sf::Color::White);
            lane.setPosition(lanePos, 0);
            window.draw(lane);
        }

        // Draw all cars
        for (const auto& carShape : carShapes) {
            window.draw(carShape);
        }

        // Display the contents of the window
        window.display();
    }

    return 0;
}