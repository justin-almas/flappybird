#include <SFML/Graphics.hpp>

class Pipe {

    public:
        Pipe(float x, float gap, float gapSize, float width, float speed);

        void move();

        sf::FloatRect getBounds() const;

        void draw(sf::RenderWindow& window);

    private:
        sf::RectangleShape upperPipe;
        sf::RectangleShape lowerPipe;
        float speed;
};