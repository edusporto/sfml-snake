
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
    public:
        Snake(float=25.f, float=0.05f, int=5, sf::Color=sf::Color::Green, float=100.f, float=100.f);
        virtual ~Snake();
        std::vector<sf::RectangleShape>& getBody();
        float getSize()   { return this->size; };
        float getSpeed()  { return this->speed; };
        int   getGrowth() { return this->growth; };
        void grow();
        enum Direction {
            Up, Left, Down, Right
        };
        void move(Direction);
};

#endif //SNAKEGAME_SNAKE_H
