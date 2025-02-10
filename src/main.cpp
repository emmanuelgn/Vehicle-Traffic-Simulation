// Copyright 2025 <Emmanuel Notargiacomo>

#include <iostream>
#include "Car.h"

int main() {
    Car car1(1, 50.0f);      // Car with id 1 and speed of 50 units per time
    float deltaTime = 1.0f;  // Simulates time passing in units of time

    for (int i = 0; i < 10; ++i) {
        car1.move(deltaTime);
        std::cout << "Car " << car1.getId() << " position: " << car1.getPosition() << std::endl;
    }

    return 0;
}