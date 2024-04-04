#ifndef _CHAR_
#define _CHAR_

/**
 * The character class to manage every entity on screen
 * @param Position (sf::Vector2f): the X and Y position of the character
 */
class Runner
{
public:
    // VARAIABLES FOR THE GRAVITY AND PROPULSION
    int speedUpMax = SPEED_UP_MAX;
    float propulsion_strenght = PROPULSION_STRENGHT;
    float propulsion_smoother = PROPULSION_SMOOTHER;
    float gravity_strenght = GRAVITY_STRENGHT;
    float gravity_smoother = GRAVITY_SMOOTHER;

    RectangleShape hitbox;
    Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f propulsion;
    sf::Vector2f gravity;
    sf::Vector2f preprocess_position;
    float propulsionFactor = propulsion_smoother; // Add a factor to decrease propulsion over time
    float deceleration = gravity_smoother;        // Deceleration factor
    float currentY;

    float bottom_offset = BOTTOM_OFFSET;
    float top_offset = TOP_OFFSET;

    Runner(Vector2f Position, sf::RenderWindow &window)
    {
        position = Position;
        texture.loadFromFile("../Assets/Character/NightBorne.png");

        texture.setSmooth(true);
        texture.setRepeated(false);
        sprite.setTexture(texture);
        sprite.setScale(1.4, 1.4);
        sprite.setPosition(position);

        gravity = sf::Vector2f(0, gravity_strenght);
        propulsion = sf::Vector2f(0, -propulsion_strenght);

        hitbox.setSize(sf::Vector2f(HITBOX_WIDTH, HITBOX_HEIGHT));
        hitbox.setPosition(position);
        hitbox.move(HITBOX_OFFSET);
    }

    void update(sf::RenderWindow &window)
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (velocity.y > -speedUpMax)
            {
                velocity.y += propulsion.y * propulsionFactor;
            }
            else
            {
                velocity.y = -speedUpMax;
            }
            deceleration = gravity_smoother; // Reset the deceleration factor when pressing the up key
            gravity.y = gravity_strenght;    // Reset the gravity when pressing the up key
        }
        else
        {
            velocity.y += gravity.y - deceleration;
            deceleration += gravity_smoother;    // Increase the deceleration factor over time
            propulsionFactor = 1.0f;             // Reset the propulsion factor when not pressing the up key
            propulsion.y = -propulsion_strenght; // Reset the propulsion when not pressing the up key
        }

        preprocess_position = sprite.getPosition() + velocity;

        if (preprocess_position.y > window.getSize().y - HITBOX_HEIGHT + bottom_offset)
        {
            velocity.y = 0;
            deceleration = gravity_smoother; // Reset the deceleration factor when pressing the up key
            gravity.y = gravity_strenght;    // Reset the gravity when pressing the up key
        }
        if (preprocess_position.y < 0 - top_offset)
        {
            velocity.y = 0;
            deceleration = gravity_smoother;     // Increase the deceleration factor over time
            propulsionFactor = 1.0f;             // Reset the propulsion factor when not pressing the up key
            propulsion.y = -propulsion_strenght; // Reset the propulsion when not pressing the up key
        }
        sprite.move(velocity.x, velocity.y);
        hitbox.move(velocity.x, velocity.y);
    }

    void draw(sf::RenderWindow &window)
    {
        // window.draw(hitbox);
        window.draw(sprite);
    }
};

// OBSTACLES

class Obstacle
{
public:
    // The obstacle has a y position that is randomly generated and comes from the right of the screen to the left until it is off the screen or collides with the player.

    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;

    Obstacle(sf::RenderWindow &window)
    {
        shape.setSize(sf::Vector2f(OBSTACLE_WIDTH, OBSTACLE_WIDTH));
        shape.setFillColor(OBSTACLE_COLOR);
        position = sf::Vector2f(window.getSize().x, rand() % window.getSize().y);
        shape.setPosition(position);
    }

    void update(sf::RenderWindow &window)
    {
        position.x -= speed;
        shape.setPosition(position);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
    }
};

#endif
