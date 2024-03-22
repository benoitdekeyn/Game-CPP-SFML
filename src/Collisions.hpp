#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <unistd.h>
#include <iostream>

using namespace sf;
// using namespace std;

// Define gridSize globally
sf::RenderWindow window(sf::VideoMode(1600, 900, 32), "SFML works!");

class Player
{
public:
    
    // The player will be moved with the up arrow key. They go up when the up arrow key is held down. Otherwise they go down.
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    int speed = 3;

    Player()
    {
        shape.setSize(sf::Vector2f(50, 50));
        shape.setFillColor(sf::Color::Green);
        position = sf::Vector2f(window.getSize().x * 0.1f, window.getSize().y - shape.getSize().y);
        shape.setPosition(position);
    }

    void update()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && position.y > 0)
        {
            velocity.y = -speed;
        }
        else if (position.y < window.getSize().y - shape.getSize().y)
        {
            velocity.y = speed;
        }
        else
        {
            velocity.y = 0;
        }

        position += velocity;
        shape.setPosition(position);
    }

    // void update()
    // {
    //     if (position.y >= (0 + shape.getSize().y) / 2 && position.y <= window.getSize().y - (0 + shape.getSize().y) / 2)
    //     {
    //         move();
    //     }
    //     else if (position.y < (0 + shape.getSize().y) / 2)
    //     {
    //         position.y = (0 + shape.getSize().y) / 2;
    //     }
    //     else if (position.y > window.getSize().y - (0 + shape.getSize().y) / 2)
    //     {
    //         position.y = window.getSize().y - (0 + shape.getSize().y) / 2;
    //     }
    // }

    void draw()
    {
        window.draw(shape);
    }
};

class Obstacle
{
    public:

    // The obstacle has a y position that is randomly generated and comes from the right of the screen to the left until it is off the screen or collides with the player.

    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    int speed = 5;

    Obstacle()
    {
        shape.setSize(sf::Vector2f(50, 50));
        shape.setFillColor(sf::Color::Red);
        position = sf::Vector2f(window.getSize().x, rand() % window.getSize().y);
        shape.setPosition(position);
    }

    void update()
    {
        position.x -= speed;
        shape.setPosition(position);
    }

    void draw()
    {
        window.draw(shape);
    }
};

// void collisionWithObstacles(Player player, Obstacle obstacle)
// {
//     if(player.shape.getGlobalBounds().intersects(obstacle.shape.getGlobalBounds()))
//     {
//         draw
//     }
// }