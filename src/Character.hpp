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
    float speed=3;
    Character(String ImagePath, Vector2f Position)
    {
        texture.loadFromFile(ImagePath);
        position = Position;

        texture.setSmooth(true);
        texture.setRepeated(false);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(20,0,100,100));
        sprite.setScale(1.2,1.2);
        hitbox.setSize(Vector2f(65, 65));
    }
    void draw()
    {
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
        sprite.move(velocity.x,velocity.y);
    }
};