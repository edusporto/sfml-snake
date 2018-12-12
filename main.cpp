
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"

// Variables used in the program
int windowWidth = 1280;
int windowHeight = 720;
float speed = 10.f;
float size  = 10.f;
int growth  = 20;
float startingX = 100.f;
float startingY = 100.f;
sf::Color color = sf::Color::Green;
float fps = 30.f;

Snake snake(size, speed, growth, color, startingX, startingY);
Food food(windowWidth, windowHeight, size, sf::Color::White);

void restart()
{
    snake = Snake(size, speed, growth, color, startingX, startingY);
    food  = Food(windowWidth, windowHeight, size, sf::Color::White);
}

int main()
{
    sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Snake", style);
    window.setFramerateLimit(fps);

    //Snake snake(size, speed, growth, color, startingX, startingY);
    Snake::Direction nextMove = Snake::Right;
    Snake::Direction lastMove = Snake::Right;

    //Food food(windowWidth, windowHeight, size, sf::Color::White);

    while (window.isOpen())
    {
        sf::Event e;

        while (window.pollEvent(e))
        {
            switch (e.type)
            {
                case e.Closed:
                    window.close();
                    break;
                case e.TextEntered:
                    if (e.text.unicode == 'p')
                        std::cout << snake.getBody().size() << std::endl;
                    if (e.text.unicode == 'g')
                        snake.grow();
                    if (e.text.unicode == 'f')
                        food = Food(windowWidth, windowHeight, size, sf::Color::White);
                    break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            //snake.move(0);
            if (lastMove != Snake::Down)
                nextMove = Snake::Up;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            //snake.move(1);
            if (lastMove != Snake::Right)
                nextMove = Snake::Left;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            //snake.move(2);
            if (lastMove != Snake::Up)
                nextMove = Snake::Down;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            //snake.move(3);
            if (lastMove != Snake::Left)
                nextMove = Snake::Right;
        }

        /*if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            player.setPosition((float)pos.x, (float)pos.y);
        }*/

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        window.clear();

        // Game loop
        snake.move(nextMove);
        lastMove = nextMove;

        if (snake.intersectsWithItself())
            restart();

        if (snake.intersects(food.getBody())) {
            food = Food(windowWidth, windowHeight, size, sf::Color::White);
            snake.grow();
        }

        // Drawing objects on the screen
        for (sf::RectangleShape piece : snake.getBody()) {
            window.draw(piece);
        }
        window.draw(food.getBody());

        //window.draw(player);
        window.display();
    }

    return 0;
}
