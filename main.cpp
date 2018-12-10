
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Snake.h"

// Variables used in the program
float speed = 1.f;
float size  = 25.f;
float startingX = 100.f;
float startingY = 100.f;
sf::Color color = sf::Color::Green;
float fps = 60.f;

int main()
{
    sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Snake", style);
    window.setFramerateLimit(fps);

    Snake snake(size, speed, color, startingX, startingY);
    std::list<sf::RectangleShape> c = snake.getBody();

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
                    break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            snake.move(0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            snake.move(1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            snake.move(2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            snake.move(3);
        }

        /*if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            player.setPosition((float)pos.x, (float)pos.y);
        }*/

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        window.clear();

        for (sf::RectangleShape x : c) {
            window.draw(x);
        }
        //window.draw(player);
        window.display();
    }

    return 0;
}