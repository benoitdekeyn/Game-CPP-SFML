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

    // VARAIABLES FOR THE GRAVITY AND PROPULSION
    int speedUpMax = 10;
    float propulsion_strenght = 2.1f;
    float propulsion_smoother = 1.0f;
    float gravity_strenght = 0.8f;
    float gravity_smoother = 0.01f;

    CircleShape hitbox;
    Texture texture;
    Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f propulsion;
    sf::Vector2f gravity;
    int speed = 3;
    float propulsionFactor = propulsion_smoother; // Add a factor to decrease propulsion over time
    float deceleration = gravity_smoother; // Deceleration factor

    Runner(String ImagePath, Vector2f Position)
    {
        texture.loadFromFile(ImagePath);
        position = Position;

        texture.setSmooth(true);
        texture.setRepeated(false);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(20, 0, 100, 100));
        sprite.setScale(1.2, 1.2);
        sprite.setPosition(position);

        gravity = sf::Vector2f(0, gravity_strenght);
        propulsion = sf::Vector2f(0, -propulsion_strenght);

        hitbox.setRadius(40);
        hitbox.setPosition(position);
        hitbox.move(20, 0);
    }
    void update()
    {
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && position.y > 0)
        {
            if (velocity.y > -speedUpMax){
                velocity.y += propulsion.y * propulsionFactor;
            }else{
                velocity.y = -speedUpMax;
            }
            deceleration = gravity_smoother; // Reset the deceleration factor when pressing the up key
            gravity.y = gravity_strenght; // Reset the gravity when pressing the up key
            
        }
        else if (position.y < window.getSize().y - hitbox.getRadius())
        {
            velocity.y += gravity.y - deceleration;
            deceleration += gravity_smoother; // Increase the deceleration factor over time
            propulsionFactor = 1.0f; // Reset the propulsion factor when not pressing the up key
            propulsion.y = -propulsion_strenght; // Reset the propulsion when not pressing the up key
        }
        else
        {
            velocity.y = 0;
        }
        position += velocity;
         if (position.y > window.getSize().y - hitbox.getRadius())
        {
            position.y = window.getSize().y - hitbox.getRadius();
        }
        if (position.y < 0)
        {
            position.y = 0;
        }
        sprite.move(velocity.x, velocity.y);
        hitbox.move(velocity.x, velocity.y);
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