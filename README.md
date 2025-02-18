# Vehicle-Traffic-Simulation

This project is a traffic simulation in a city, featuring cars, traffic lights, and roads. It simulates the movement of cars along roads with synchronized traffic lights at intersections, ensuring realistic traffic flow and interactions.

## Features

- **Car Movement**: Simulates the movement of cars with adjustable speed.
- **Traffic Lights**: Implements synchronized traffic lights at intersections, ensuring opposite states (green/red) for vertical and horizontal lanes.
- **Realistic Behavior**: Cars stop at red lights and proceed at green lights, mimicking real-world traffic behavior.
- **Project Structure**: Organized with separate directories for source and header files.
- **CMake Build System**: Easily compile and manage the project with CMake.

## How to Compile

To compile the project, ensure you have CMake and a C++ compiler installed. Then follow these steps:

```bash
mkdir build
cd build
cmake ..
make

## How to Run

After compilation, run the program with:

```bash
./TrafficSimulation
```

## Future Enhancements
* Add multiple roads and intersections.
* Simulate more complex traffic patterns and interactions.
* Implement pedestrian crossings and other real-world traffic elements.
* Improve graphics and user interface for better visualization.

Feel free to expand the README with more detailed instructions or project descriptions as you develop additional features.