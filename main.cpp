

#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream> 
#include "pipe.hpp"
#include <random>

class HitboxSprite : public sf::Sprite {
    public:
        void setHitbox(const sf::FloatRect& hitbox) {
            myHitbox = hitbox;
        }

        sf::FloatRect getGlobalHitBox() const {
            return getTransform().transformRect(myHitbox);
        }
    private:
        sf::FloatRect myHitbox;
};


int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(1024, 768, desktop.bitsPerPixel), "SFML works!");

    sf::Clock clock;

    sf::Texture bird;
    if (!bird.loadFromFile("bird.png")) {
        return -1;
    }
    HitboxSprite sprite;
    sprite.setTexture(bird);
    sprite.setScale(0.1,0.1);
    sprite.setPosition(400, 300);
    sprite.setHitbox({ 15.f, 8.f, 38.f, 33.f });

    // sf::RectangleShape test(sf::Vector2f(38.f,33.f));
    // test.setPosition(415, 308);
    // test.setFillColor(sf::Color::Green);
    //here to test hitbox


    sf::Vector2f velocity (0.0f, 0.0f);
    const float gravity = 0.000003f;
    const float changeY = -0.02f;
    bool isJumping = false;
    bool gameOver = false;
    sf::FloatRect windowBounds(sf::Vector2f(0.f, 0.f), window.getDefaultView().getSize());

    const float pipeWidth = 80.0f;
    const float gapSize = 150.0f;
    const float pipeSpeed = 0.01f;
    Pipe initPipe(1024.f, 100.f, gapSize, pipeWidth, pipeSpeed);
    std::vector<Pipe> pipes;
    pipes.push_back(initPipe);

    //random pipe postion
    std::random_device dev;
    std::mt19937 rng(dev());
    std::vector<float> possibleGapLocations = {100.f, 200.f, 300.f, 400.f, 500.f, 600.f};
    std::uniform_int_distribution<std::mt19937::result_type> distrib(0,5); // distribution in range [1, 6]
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

        if (clock.getElapsedTime().asSeconds() > 3) {
            clock.restart();
            float gap = possibleGapLocations[distrib(rng)];
            Pipe pipe(window.getSize().x, gap, gapSize, pipeWidth, pipeSpeed);
            pipes.push_back(pipe);
        }

        if (sprite.getPosition().y > windowBounds.top + windowBounds.height) {
            sprite.setPosition(400, 300);
            window.close();
        } else if (sprite.getPosition().y < windowBounds.top) {
            sprite.setPosition(400, windowBounds.top);
        }

        for (auto i = pipes.begin(); i != pipes.end();)
        {
            i->move();
            if (sprite.getGlobalHitBox().intersects(i->getTopBounds()) || sprite.getGlobalHitBox().intersects(i->getBottomBounds())) {
                window.close();
            }
            if (i->getTopBounds().left + pipeWidth < 0)
            {
                i = pipes.erase(i);
            }
            else
            {
                ++i;
            }
        }
        
        sprite.move(velocity);
        velocity.y += gravity;

        window.clear(sf::Color::White);

        window.draw(sprite);
        //window.draw(test); hitbox test

        for (const auto& pipe : pipes)
        {
            pipe.draw(window);
        }

        window.display();
    }

    return 0;
}
