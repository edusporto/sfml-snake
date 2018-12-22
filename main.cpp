
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

unsigned int points = 0;

enum GameState {
    Start, Playing, Paused, Over
};
GameState state = Start;

Snake snake(windowWidth, windowHeight, size, speed, growth, color, startingX, startingY);
Food food(windowWidth, windowHeight, size, sf::Color::White);

Snake::Direction nextMove = Snake::Right;
Snake::Direction lastMove = Snake::Right;


// Helper functions

void restart()
{
    points = 0;
    lastMove = Snake::Right;
    nextMove = Snake::Right;
    snake = Snake(windowWidth, windowHeight, size, speed, growth, color, startingX, startingY);
    food  = Food(windowWidth, windowHeight, size, sf::Color::White);
}

void gameLoop()
{
	snake.move(nextMove);
    lastMove = nextMove;

    // Checking if the snake's head intersects with itself
    if (snake.intersectsWithItself()) {
        state = Over;
        // restart();
    }

    // Checking if the snake is intersecting a food piece
    if (snake.intersects(food.getBody())) {
        food = Food(windowWidth, windowHeight, size, sf::Color::White);
        points += 100;
        snake.grow();
    }
}



int main()
{
    sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Snake", style);
    window.setFramerateLimit(fps);

    //Snake snake(size, speed, growth, color, startingX, startingY);

    //Food food(windowWidth, windowHeight, size, sf::Color::White);

    // Setting different texts showed on the screen
    sf::Font font;
    if (!font.loadFromFile("resources/fonts/arial.ttf")) {
        std::cout << "Could not load resources/fonts/arial.ttf" << std::endl;
        return 0;
    }
    // Paused text
    sf::Text pausedText;
    pausedText.setFont(font);
    pausedText.setString("Paused. Press [SPACE] to unpause");
    pausedText.setFillColor(sf::Color::Blue);
    pausedText.setCharacterSize(30);
    // Text shown at the start of the game
    sf::Text startText("Press [SPACE] to start", font, 30);
    startText.setFillColor(sf::Color::Yellow);
    // Text shown in game over
    sf::Text gameOverText("Game Over. Press [SPACE] to restart", font, 30);
    gameOverText.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        window.setTitle("Snake. Points: " + std::to_string(points));

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
                    if (e.text.unicode == ' ') {
                        switch (state)
                        {
                            case Start:   state = Playing; break;
                            case Playing: state = Paused;  break;
                            case Paused:  state = Playing; break;
                            case Over:    state = Start; restart(); break;
                        }
                    }
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
        if (state == Playing) {
            gameLoop();
        }
        else {
            if (state == Paused)
                window.draw(pausedText);
            if (state == Start)
                window.draw(startText);
            if (state == Over)
                window.draw(gameOverText);
        }

        // Drawing objects on the screen
		sf::RectangleShape previous;
        for (sf::RectangleShape piece : snake.getBody()) {
        	// Preventes pieces of the snake that are in the same position be drawn
        	// Helps in performance of really big snakes
            if (previous.getPosition() == piece.getPosition())
           	    break;
            previous = piece;

            window.draw(piece);
        }
        window.draw(food.getBody());

        //window.draw(player);
        window.display();
    }

    return 0;
}
