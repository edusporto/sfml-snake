
#ifndef SNAKEGAME_FOOD_H
#define SNAKEGAME_FOOD_H

#include <SFML/Graphics.hpp>

class Food {
    protected:
        sf::RectangleShape body;
        float size;
        sf::Color color;
    public:
        Food(int, int, float=25.f, sf::Color=sf::Color::White);
        virtual ~Food();
        sf::RectangleShape& getBody() { return this->body; };
        float getSize() { return this->size; } ;
        sf::Color getColor() { return this->color; };
};

#endif //SNAKEGAME_FOOD_H
