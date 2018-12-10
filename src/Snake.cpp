
#include "Snake.h"
#include <iostream>

Snake::Snake(float size, float speed, sf::Color color, float startingX, float startingY)
{
    const sf::Vector2f startingPosition(startingX, startingY);

    sf::RectangleShape head(sf::Vector2f(size, size));

    head.setFillColor(color);
    head.setOrigin(size / 2, size / 2);
    head.setPosition(startingPosition);

    this->speed = speed;
    this->size  = size;
    this->color = color;

    this->body.push_front(head);
}

Snake::~Snake()
{
    this->body.clear();
}

void Snake::grow()
{
    // Grows the snake by 5 pieces
    for (int i=0; i<5; i++) {
        sf::RectangleShape newPiece(sf::Vector2f(size,size));
        newPiece.setPosition(body.back().getPosition().x, body.back().getPosition().x);
        newPiece.setOrigin(size / 2, size / 2);
        this->body.push_back(newPiece);
    }
}

void Snake::move(char direction)
{
    sf::RectangleShape head = body.front();
    std::cout << head.getPosition().x << " " << head.getPosition().y << std::endl;
    switch (direction)
    {
        case 0:
            head.move(speed, 0.f);
            break;
        case 1:
            head.move(0.f, speed);
            break;
        case 2:
            head.move(-speed, 0.f);
            break;
        case 3:
            head.move(0.f, -speed);
            break;
    }
}

std::list<sf::RectangleShape>& Snake::getBody()
{
    return this->body;
}
