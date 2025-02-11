#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "Car.h"

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Traffic Simulation");

    // Set up a simple rectangle shape to represent a car
    sf::RectangleShape carShape(sf::Vector2f(50.0f, 100.0f));
    carShape.setFillColor(sf::Color::Blue);
    carShape.setPosition(375.0f, 500.0f);  // Position the car at the bottom center

    // Set up the Car object
    Car car1(1, 50.0f);       // Car with id 1 and speed of 50 units per time
    float deltaTime = 0.01f;  // Simulates time passing in smaller units for smoother animation

    // Random number generator setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);  // Reduced random movement range

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Update car position with random movement
        float randomMoveX = dis(gen) * deltaTime * 50.0f;  // Adjusted for smoother movement
        float randomMoveY = dis(gen) * deltaTime * 50.0f;  // Adjusted for smoother movement
        carShape.move(randomMoveX, randomMoveY);

        // Print car position to console (optional)
        std::cout << "Car " << car1.getId() << " position: (" << carShape.getPosition().x << ", "
                  << carShape.getPosition().y << ")" << std::endl;

        // Clear the window with a black color
        window.clear(sf::Color::Black);

        // Draw the car
        window.draw(carShape);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
