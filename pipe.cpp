#include "pipe.hpp"

Pipe::Pipe(float x, float gap, const float gapSize, const float width, const float speed) : speed(speed) {

    upperPipe.setSize(sf::Vector2f(width, gap));
    upperPipe.setPosition(x, 0);
    upperPipe.setFillColor(sf::Color::Green);

    lowerPipe.setSize(sf::Vector2f(width, 1000.f)); //super big number cause I don't want to calculate it
    lowerPipe.setPosition(x, gap + gapSize);
    lowerPipe.setFillColor(sf::Color::Green);
}

void Pipe::move() {
    upperPipe.move(-speed, 0);
    lowerPipe.move(-speed, 0);
}

sf::FloatRect Pipe::getTopBounds() const {
    return upperPipe.getGlobalBounds();
}

sf::FloatRect Pipe::getBottomBounds() const {
    return lowerPipe.getGlobalBounds();
}

void Pipe::draw(sf::RenderWindow& window) const{
    window.draw(upperPipe);
    window.draw(lowerPipe);
}