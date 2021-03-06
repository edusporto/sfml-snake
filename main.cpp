
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"
#include <config4cpp/Configuration.h>
using namespace config4cpp;

/* ========== Variables used in the program ========== */
// Window configuration
unsigned int fps = 60;
int windowWidth = 1280;
int windowHeight = 720;

// Snake configuration
float speed = 10.f;
float size  = 9.f;
int growth  = 20;
float startingX = 100.f;
float startingY = 100.f;
sf::Color snakeColor = sf::Color::Green;
sf::Color foodColor  = sf::Color::White;
sf::Color backgroundColor = sf::Color(40,40,40);

Snake snake(windowWidth, windowHeight, size, speed, growth, snakeColor, startingX, startingY);
Food food(windowWidth, windowHeight, size, foodColor);
Snake::Direction nextMove = Snake::Right;
Snake::Direction lastMove = Snake::Right;

// Point configuration
unsigned int points = 0;

// States that the game can be in
enum GameState {
    Start, Playing, Paused, Over
};
GameState state = Start;



/* ========== Helper functions ========== */

void restart()
{
    points = 0;
    lastMove = Snake::Right;
    nextMove = Snake::Right;
    snake = Snake(windowWidth, windowHeight, size, speed, growth, snakeColor, startingX, startingY);
    food  = Food(windowWidth, windowHeight, size, foodColor);
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
        food = Food(windowWidth, windowHeight, size, foodColor);
        points += 100;
        snake.grow();
    }
}

// Function executed whenever the player presses the space bar
void spaceBarPressed()
{
    switch (state)
    {
        case Start:   state = Playing; break;
        case Playing: state = Paused;  break;
        case Paused:  state = Playing; break;
        case Over:    state = Start; restart(); break;
    }
}

bool configure()
{
    // TODO: treat exceptions

    Configuration* cfg = Configuration::create();
    const char *   configFile = "config.cfg";
    const char *   scope = "";

    try {
        cfg->parse(configFile);
        fps          = cfg->lookupInt(scope, "fps");
        windowWidth  = cfg->lookupInt(scope, "windowWidth");
        windowHeight = cfg->lookupInt(scope, "windowHeight");
        speed        = cfg->lookupFloat(scope, "speed");
        size         = cfg->lookupFloat(scope, "size");
        growth       = cfg->lookupInt(scope, "growth");
        startingX    = cfg->lookupInt(scope, "startingX");
        startingY    = cfg->lookupInt(scope, "startingY");

        std::string color;
        color = cfg->lookupString(scope, "snakeColor");
        std::string red   = color.substr(0, color.find("r"));
        std::string green = color.substr(color.find("r")+1, color.find("g"));
        std::string blue  = color.substr(color.find("g")+1, color.find("b"));
        snakeColor = sf::Color(atoi(red.c_str()), atoi(green.c_str()), atoi(blue.c_str()));
        
        color = cfg->lookupString(scope, "foodColor");
        red   = color.substr(0, color.find("r"));
        green = color.substr(color.find("r")+1, color.find("g"));
        blue  = color.substr(color.find("g")+1, color.find("b"));
        foodColor = sf::Color(atoi(red.c_str()), atoi(green.c_str()), atoi(blue.c_str()));

        color = cfg->lookupString(scope, "backgroundColor");
        red   = color.substr(0, color.find("r"));
        green = color.substr(color.find("r")+1, color.find("g"));
        blue  = color.substr(color.find("g")+1, color.find("b"));
        backgroundColor = sf::Color(atoi(red.c_str()), atoi(green.c_str()), atoi(blue.c_str()));

    } catch(const ConfigurationException & ex) {
        std::cerr << ex.c_str() << std::endl;
        std::cout << "Error with configuration file. Using default settings" << std::endl;
        return false;
    } catch (const std::exception ex2) {
        std::cerr << ex2.what() << std::endl;
        return true;
    }

    cfg->destroy();
    return true;
}

int main()
{
    // Configuring the game and its elements
    // Configuration can be found in config.cfg
    configure();
    restart();

    /* ========== Configuring UI elements ========== */

    // Configuring the window
    sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Snake", style);
    window.setFramerateLimit(fps);

    // Setting different texts showed on the screen
    sf::Font font;
    if (!font.loadFromFile("resources/fonts/arial.ttf")) {
        std::cout << "Could not load resources/fonts/arial.ttf" << std::endl;
        return 0;
    }
    // Text shown at the start of the game
    sf::Text startText("Press [SPACE] to start", font, 30);
    startText.setFillColor(sf::Color::Yellow);
    // Paused text
    sf::Text pausedText("Paused. Press [SPACE] to unpause", font, 30);
    pausedText.setFillColor(sf::Color::Blue);
    // Text shown in game over
    sf::Text gameOverText("Game Over. Press [SPACE] to restart", font, 30);
    gameOverText.setFillColor(sf::Color::Red);

	unsigned int previousPoints = points;
    while (window.isOpen())
    {
        // Shows the current amount of points in the title bar
        if (previousPoints != points) {
        	window.setTitle("Snake. Points: " + std::to_string(points));
        	previousPoints = points;
        }

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
                        food = Food(windowWidth, windowHeight, size, foodColor);
                    if (e.text.unicode == ' ') {
                        spaceBarPressed();
                    }
                    break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            if (lastMove != Snake::Down)
                nextMove = Snake::Up;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            if (lastMove != Snake::Up)
                nextMove = Snake::Down;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            if (lastMove != Snake::Right)
                nextMove = Snake::Left;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            if (lastMove != Snake::Left)
                nextMove = Snake::Right;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        window.clear(backgroundColor); // darkslategray

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
        for (sf::RectangleShape& piece : snake.getBody()) {
        	// Prevents pieces of the snake that are in the same position be drawn
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
