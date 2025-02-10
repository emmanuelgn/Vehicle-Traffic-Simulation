// Copyright 2025 <Emmanuel Notargiacomo>

#ifndef INCLUDE_CAR_H_
#define INCLUDE_CAR_H_

class Car {
 public:
    Car(int id, float speed);

    void move(float deltaTime);
    int getId() const;
    float getPosition() const;

 private:
    int id;
    float speed;
    float position;
};

#endif  // INCLUDE_CAR_H_
