// Copyright 2025 <Emmanuel Notargiacomo>

#include "Car.h"

Car::Car(int id, float speed)
    : id(id), speed(speed), position(0.0f) {}

void Car::move(float deltaTime) {
    position += speed * deltaTime;
}

int Car::getId() const {
    return id;
}

float Car::getPosition() const {
    return position;
}