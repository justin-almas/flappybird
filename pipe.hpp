#include <SFML/Graphics.hpp>

class Pipe {

    public:
        Pipe(float x, float gap, const float gapSize, const float width, const float speed);

        void move();

        sf::FloatRect getBounds() const;

        void draw(sf::RenderWindow& window) const;

    private:
        sf::RectangleShape upperPipe;
        sf::RectangleShape lowerPipe;
        float speed;
};