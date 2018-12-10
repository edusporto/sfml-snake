
#include "Snake.h"
#include <SFML/Graphics.hpp>

Snake::Snake(float size, float speed, sf::Color color, float startingX, float startingY)
{
    const sf::Vector2f startingPosition(startingX, startingY);

    sf::RectangleShape head(sf::Vector2f(size, size));

    head.setFillColor(color);
    head.setOrigin(head.getSize().x / 2, head.getSize().y / 2);
    head.setPosition(startingPosition);

    this->speed = speed;

    this->body.push_front(head);
}

Snake::~Snake()
{
    this->body.clear();
}

std::list<sf::RectangleShape>& Snake::getBody()
{
    return this->body;
}