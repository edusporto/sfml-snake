
#include "Food.h"
#include <cstdlib>

Food::Food(int windowWidth, int windowHeight, float size, sf::Color color)
{
    //srand(time(NULL));
    const float startingX = rand() % (int)(windowWidth - size);
    const float startingY = rand() % (int)(windowHeight - size);

    sf::RectangleShape body(sf::Vector2f(size, size));

    body.setFillColor(color);
    body.setPosition(startingX, startingY);

    this->body  = body;
    this->size  = size;
    this->color = color;
}

Food::~Food()
{

}
