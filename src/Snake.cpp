
#include "Snake.h"
#include <iostream>

Snake::Snake(float size, float speed, int growth, sf::Color color, float startingX, float startingY)
{
    const sf::Vector2f startingPosition(startingX, startingY);

    sf::RectangleShape head(sf::Vector2f(size, size));

    head.setFillColor(color);
    //head.setOrigin(size / 2, size / 2);
    head.setPosition(startingPosition);

    this->speed  = speed;
    this->size   = size;
    this->growth = growth;
    this->color  = color;

    this->body.push_back(head);
}

Snake::~Snake()
{
    this->body.clear();
}

void Snake::grow()
{
    // Grows the snake by growth pieces
    for (int i=0; i<this->growth; i++)
    {
        sf::RectangleShape newPiece(sf::Vector2f(size, size));
        newPiece.setFillColor(color);
        //newPiece.setOrigin(size / 2, size / 2);
        newPiece.setPosition(body[body.size()-1].getPosition().x, body[body.size()-1].getPosition().y);

        body.push_back(newPiece);
    }
}

void Snake::move(Direction direction)
{
    sf::RectangleShape& head = body.front();

    for (int i = body.size() - 1; i > 0; i--)
        body[i] = body[i - 1];

    switch (direction)
    {
        case 0:
            head.move(0.f, -speed);
            break;
        case 1:
            head.move(-speed, 0.f);
            break;
        case 2:
            head.move(0.f, speed);
            break;
        case 3:
            head.move(speed, 0.f);
            break;
    }
}

std::vector<sf::RectangleShape>& Snake::getBody()
{
    return this->body;
}

bool Snake::intersects(const sf::RectangleShape& square)
{
    sf::Vector2f halfSizeMyHead = body[0].getSize() / 2.f;
    sf::Vector2f halfSizeSquare = square.getSize()  / 2.f;
    sf::Vector2f posMyHead = body[0].getPosition() + halfSizeMyHead;
    sf::Vector2f posSquare = square.getPosition()  + halfSizeSquare;

    sf::Vector2f delta = posMyHead - posSquare;
    float intersectX = abs(delta.x)  - (halfSizeMyHead.x + halfSizeSquare.x);
    float intersectY = abs(delta.y)  - (halfSizeMyHead.y + halfSizeSquare.y);

    if (intersectX < 0.f && intersectY < 0.f)
        return true;

    return false;
}

bool Snake::intersectsWithItself()
{
    // starts at 2 so the head wont collide with the first body part
    for (int i=3; i<body.size(); i++) {
        if (intersects(body[i]))
            return true;
    }
    return false;
}