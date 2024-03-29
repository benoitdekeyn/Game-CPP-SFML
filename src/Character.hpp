#ifndef _CHAR_
#define _CHAR_
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

// Define gridSize globally
sf::RenderWindow window(sf::VideoMode(1600, 900, 32), "SFML works!");

/**
 * The character class to manage every entity on screen
 * @param ImagePath (string): load an image's path to use a texture
 * @param Position (sf::Vector2f): the X and Y position of the character
 */
class Runner
{
public:
    RectangleShape hitbox;
    Texture texture;
    Sprite sprite;
    Vector2f position;
    Vector2f velocity;
    float speed = 3;
    Runner(String ImagePath, Vector2f Position)
    {
        texture.loadFromFile(ImagePath);
        position = Position;

        texture.setSmooth(true);
        texture.setRepeated(false);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(20, 0, 100, 100));
        sprite.setScale(1.2, 1.2);
        hitbox.setSize(Vector2f(65, 65));
    }
    void update()
    {
        if (Keyboard::isKeyPressed(Keyboard::Up) && sprite.getPosition().y > 0)
        {
            velocity.y = -speed;
        }
        else if (sprite.getPosition().y < window.getSize().y - hitbox.getSize().y)
        {
            velocity.y = speed;
        }
        else
        {
            velocity.y = 0;
        }
        sprite.move(velocity.x, velocity.y);
    }
    void draw()
    {
        window.draw(sprite);
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

#endif