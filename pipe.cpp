#include "pipe.hpp"

Pipe::Pipe(float x, float gap, float gapSize, float width, float velocity) : speed(speed) {

    upperPipe.setSize(sf::Vector2f(width, gap));
    upperPipe.setPosition(x, 0);

    lowerPipe.setSize(sf::Vector2f(width, gapSize - gap));
    lowerPipe.setPosition(x, gap);
}

void Pipe::move() {
    upperPipe.move(-speed, 0);
    lowerPipe.move(-speed, 0);
}

sf::FloatRect Pipe::getBounds() const {
    return upperPipe.getGlobalBounds();
}

void Pipe::draw(sf::RenderWindow& window) {
    window.draw(upperPipe);
    window.draw(lowerPipe);
}