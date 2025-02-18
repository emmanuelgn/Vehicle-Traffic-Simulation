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
    std::uniform_real_distribution<> dis(-1.0, 1.0);  // Reduced random movement range

    // Create multiple cars
    for (int i = 0; i < 5; ++i) {  // Create 5 cars for example
        Car car(i + 1, 50.0f);     // Car with id and speed
        cars.push_back(car);

        sf::RectangleShape carShape(sf::Vector2f(50.0f, 100.0f));
        carShape.setFillColor(sf::Color::Blue);
        carShape.setPosition(100.0f * i + 50.0f, 500.0f);  // Position cars with some spacing
        carShapes.push_back(carShape);
    }

    float deltaTime = 0.01f;  // Simulates time passing in smaller units for smoother animation

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Update car positions with random movement
        for (size_t i = 0; i < cars.size(); ++i) {
            float randomMoveX = dis(gen) * deltaTime * 50.0f;  // Adjusted for smoother movement
            float randomMoveY = dis(gen) * deltaTime * 50.0f;  // Adjusted for smoother movement

            carShapes[i].move(randomMoveX, randomMoveY);

            // Print car position to console (optional)
            std::cout << "Car " << cars[i].getId() << " position: (" << carShapes[i].getPosition().x
                      << ", " << carShapes[i].getPosition().y << ")" << std::endl;
        }

        // Clear the window with a black color
        window.clear(sf::Color::Black);

        // Draw all cars
        for (const auto &carShape : carShapes) {
            window.draw(carShape);
        }

        // Display the contents of the window
        window.display();
    }

    return 0;
}