
#ifndef SNAKEGAME_SNAKE_H
#define SNAKEGAME_SNAKE_H

#include <vector>
#include <SFML/Graphics.hpp>

class Snake {
    protected:
        std::vector<sf::RectangleShape> body;
        float size;
        float speed;
        int growth;
        sf::Color color;
        int windowWidth;
        int windowHeight;
    public:
        Snake(int, int, float=25.f, float=0.05f, int=5, sf::Color=sf::Color::Green, float=100.f, float=100.f);
        virtual ~Snake();
        std::vector<sf::RectangleShape>& getBody();
        float getSize()   { return this->size; };
        float getSpeed()  { return this->speed; };
        int   getGrowth() { return this->growth; };
        sf::Color getColor() { return this->color; };
        int   getWindowWidth() { return this->windowWidth; };
        int   getWindowHeight() { return this->windowHeight; };

        void setSize(float newSize) { size = newSize; };
        void setSpeed(float newSpeed) { speed = newSpeed; };
        void setGrowth(int newGrowth) { growth = newGrowth; };
        void setColor(sf::Color newColor) { color = newColor; };
        void setWindowWidth(int newWindowWidth) { windowWidth = newWindowWidth; };
        void setWindowHeight(int newWindowHeight) { windowHeight = newWindowHeight; };

        void grow();
        enum Direction {
            Up, Left, Down, Right
        };
        void move(Direction);
        bool intersects(const sf::RectangleShape&);
        bool intersectsWithItself();
};

#endif //SNAKEGAME_SNAKE_H
