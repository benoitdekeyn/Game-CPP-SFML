#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <unistd.h>
#include <iostream>

using namespace sf;
// using namespace std;

// Define gridSize globally
sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

class Player
{
public:
    
    // The player will be moved with the up arrow key. They go up when the up arrow key is held down. Otherwise they go down.
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed = 0.1f;

    Player()
    {
        shape.setSize(sf::Vector2f(50, 50));
        shape.setFillColor(sf::Color::Green);
        position = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
        shape.setPosition(position);
    }

    void update()
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            velocity.y = -speed;
        }
        else
        {
            velocity.y = speed;
        }

        position += velocity;
        shape.setPosition(position);
    }

    void draw()
    {
        window.draw(shape);
    }
};

class Obstacle
{
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed = 0.1f;

    sf::Sprite sprite;
    sf::Texture texture;

    // Constructor
    Obstacle()
    {
        if (!texture.loadFromFile("test.JPG")) 
        {
            std::cout << "Error loading texture" << std::endl;
        }
        sprite.setTexture(texture);

        sprite.setScale(0.1f, 0.1f);
        position = sf::Vector2f(window.getSize().x, rand() % window.getSize().y);
        sprite.setPosition(position);
    }

    void update()
    {
        position.x -= speed;
        sprite.setPosition(position);
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }
};

void checkCollision(Player player, Obstacle obstacle)
{
    if(player.shape.getGlobalBounds().intersects(obstacle.sprite.getGlobalBounds()))
    {
        exit(0);
    }
}

int main()
{
    Player player;
    Obstacle obstacle;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        checkCollision(player, obstacle);

        window.clear(); // Clear the window before drawing anything

        player.update();
        player.draw();

        obstacle.update();
        obstacle.draw(window);

        window.display();
        
        usleep(1000);
    }
}
