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
class Character
{
public:
    RectangleShape hitbox;
    Texture texture;
    Sprite sprite;
    Vector2f position;
    Vector2f velocity;
    float speed;

    Character(String ImagePath, Vector2f Position)
    {
        texture.loadFromFile(ImagePath);
        position = Position;

        texture.setSmooth(true);
        texture.setRepeated(false);
        sprite.setTexture(texture);
        hitbox.setSize(Vector2f(40, 40));
    }
    void draw()
    {
        sprite.setPosition(position);
        window.draw(sprite);
    }
};

class Runner : public Character
{
public:
    Runner(const std::string &path, const sf::Vector2f &position)
        : Character(path, position) {}
    void update()
    {
        if (Keyboard::isKeyPressed(Keyboard::Up) && position.y > 0)
        {
            velocity.y = -speed;
        }
        else if (position.y < window.getSize().y - hitbox.getSize().y)
        {
            velocity.y = speed;
        }
        else
        {
            velocity.y = 0;
        }

        position += velocity;
        sprite.setPosition(position);
    }
};