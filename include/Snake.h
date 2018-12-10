
#ifndef SNAKEGAME_SNAKE_H
#define SNAKEGAME_SNAKE_H

#include <list>
#include <SFML/Graphics.hpp>

class Snake {
    protected:
        std::list<sf::RectangleShape> body;
        float size;
        float speed;
        sf::Color color;
    public:
        Snake(float=25.f, float=0.05f, sf::Color=sf::Color::Green, float=100.f, float=100.f);
        virtual ~Snake();
        std::list<sf::RectangleShape>& getBody();
        float getSize()  { return this->size; };
        float getSpeed() { return this-> size; };
        void grow();
        void move(char);
};

#endif //SNAKEGAME_SNAKE_H
