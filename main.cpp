

#include <SFML/Graphics.hpp>
#include <iostream>
#include<unistd.h> 

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(1024, 768, desktop.bitsPerPixel), "SFML works!");
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
    bool gameOver = false;
    sf::FloatRect windowBounds(sf::Vector2f(0.f, 0.f), window.getDefaultView().getSize());
    while (window.isOpen()) //game loop
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
        if (sprite.getPosition().y > windowBounds.top + windowBounds.height) {
            sprite.setPosition(400, 300);
            gameOver = true;
        } else if (sprite.getPosition().y < windowBounds.top - 40) {
            sprite.setPosition(400, windowBounds.top - 40);
        }
        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
        if (gameOver) {
            sleep(2);
            gameOver = false;
            velocity.y = 0;
        }
    }

    return 0;
}
