#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Car.h"

int main() {
    // Criar a janela
    sf::RenderWindow window(sf::VideoMode(800, 600), "Traffic Simulation");

    // Largura da faixa da estrada
    float laneWidth = 50.0f;

    // Definir posições das faixas
    std::vector<float> lanePositions = {100.0f, 200.0f, 300.0f, 400.0f, 500.0f};

    // Criar múltiplos carros
    std::vector<Car> cars;
    std::vector<sf::RectangleShape> carShapes;

    for (size_t i = 0; i < lanePositions.size(); ++i) {
        Car car(i + 1, 50.0f);
        cars.push_back(car);

        sf::RectangleShape carShape(sf::Vector2f(30.0f, 100.0f));
        carShape.setFillColor(sf::Color::Blue);

        // Centralizar o carro na faixa
        carShape.setPosition(lanePositions[i] - carShape.getSize().x / 2, 600.0f);
        carShapes.push_back(carShape);
    }

    float carSpeed = 5.0f;
    float deltaTime = 0.01f;

    // Loop principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Atualizar posição dos carros
        for (size_t i = 0; i < cars.size(); ++i) {
            carShapes[i].move(0, -carSpeed * deltaTime);

            if (carShapes[i].getPosition().y + carShapes[i].getSize().y < 0) {
                carShapes[i].setPosition(carShapes[i].getPosition().x, 600.0f);
            }
        }

        // Limpar tela com um fundo preto
        window.clear(sf::Color::Black);

        // Desenhar as faixas da estrada
        for (const auto &lanePos : lanePositions) {
            sf::RectangleShape lane(sf::Vector2f(laneWidth, 600.0f));
            lane.setFillColor(sf::Color(100, 100, 100));  // Cinza para asfalto
            lane.setPosition(lanePos - laneWidth / 2, 0);
            window.draw(lane);
        }

        // Desenhar os carros
        for (const auto &carShape : carShapes) {
            window.draw(carShape);
        }

        // Exibir o conteúdo atualizado
        window.display();
    }

    return 0;
}
