#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;
RenderWindow window(VideoMode(1600, 900), "SFML works!");

class character
{
public:
    RectangleShape hitbox;
    Texture texture;
    Sprite sprite;
    Vector2f position;
    Vector2f velocity;
    float speed;

    character(Texture a, Sprite b, Vector2f c, Vector2f d)
    {
        texture = a;
        sprite = b;
        position = c;
        velocity = d;
        texture.setSmooth(true);
        texture.setRepeated(false);
        hitbox.setSize(Vector2f(40,40));
    }
    void draw()
    {
        sprite.setPosition(position);
        window.draw(sprite);
    }

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

class Player : character
{

    void collisionWithObstacles(Player player, character obstacle)
    {
        if (player.hitbox.getGlobalBounds().intersects(obstacle.hitbox.getGlobalBounds()))
        {
            exit(0);
        }
    }
};