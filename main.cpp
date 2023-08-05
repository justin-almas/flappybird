

#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(1024, 768, desktop.bitsPerPixel), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Texture bird;
    if (!bird.loadFromFile("bird.png")) {
        return -1;
    }
    sf::Sprite sprite;
    sprite.setTexture(bird);
    sprite.setScale(0.1,0.1);
    sprite.setPosition(400, 300);
    sf::Vector2f velocity (0.0f, 0.0f);
    const float gravity = 0.000003f;
    const float changeY = -0.03f;
    bool isJumping = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                if (!isJumping) {
                    velocity.y = changeY;
                    isJumping = true;
                }
            }
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W) {
                isJumping = false;
            }
        }
        sprite.move(velocity);
        velocity.y += gravity;
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
