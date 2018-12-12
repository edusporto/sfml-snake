
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"

// Variables used in the program
float speed = 5.f;
float size  = 10.f;
int growth  = 20;
float startingX = 100.f;
float startingY = 100.f;
sf::Color color = sf::Color::Green;
float fps = 60.f;

int main()
{
    sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Snake", style);
    window.setFramerateLimit(fps);

    Snake snake(size, speed, growth, color, startingX, startingY);
    Snake::Direction nextMove = Snake::Right;

    Food food(1280, 720, size, sf::Color::White);

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
                        food = Food(1280, 720, size, sf::Color::White);
                    break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            //snake.move(0);
            nextMove = Snake::Up;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            //snake.move(1);
            nextMove = Snake::Left;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            //snake.move(2);
            nextMove = Snake::Down;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            //snake.move(3);
            nextMove = Snake::Right;
        }

        /*if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            player.setPosition((float)pos.x, (float)pos.y);
        }*/

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        // Game loop
        snake.move(nextMove);


        window.clear();

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