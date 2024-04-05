#ifndef _CHAR_
#define _CHAR_

#include <unistd.h>

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

    // VARIABLES FOR THE HITBOX AND THE DISPLAY
    RectangleShape hitbox;
    Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;

    // VARIABLES FOR THE MOVEMENT
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
        window.draw(sprite);
    }
};

vector<Texture> obstacleTextures;

// Load obstacle textures function
void loadObstacleTextures()
{
    Texture texture;
    if (texture.loadFromFile("../Assets/enemies/ShadowForest.png", sf::IntRect(10, 10, 25, 35))) // Adjust path if needed
    {
        obstacleTextures.push_back(texture);
    }
    else
    {
        // std::cout << "Error loading texture" << std::endl;
    }
}

// OBSTACLES
class Obstacle
{
public:
    sf::RectangleShape hitbox;
    sf::Vector2f position;
    sf::Sprite sprite; // Use sf::Sprite instead of sf::RectangleShape
    bool scored;

    Obstacle(sf::RenderWindow &window)
    {
        if (!obstacleTextures.empty())
        {
            sprite.setTexture(obstacleTextures[0]); // Use the globally loaded texture
        }

        position = sf::Vector2f(window.getSize().x, rand() % window.getSize().y);
        while (position.y > window.getSize().y - 100)
        {
            position = sf::Vector2f(window.getSize().x, rand() % window.getSize().y);
        }

        // set sprite scale and position
        sprite.setScale(4, 4);
        sprite.setPosition(position);

        // set hitbox size and position
        hitbox.setSize(sf::Vector2f(20, 20));
        hitbox.setPosition(position.x, position.y + 50);
    }

    void move(float offsetX, float offsetY)
    {
        position.x += offsetX;
        position.y += offsetY;
        sprite.setPosition(position);
        hitbox.setPosition(position.x+40, position.y + 70);
    }

    sf::Vector2f getPosition() const
    {
        return sprite.getPosition();
    }

    void update()
    {
        position.x -= speed;
        sprite.setPosition(position);
        hitbox.setPosition(position);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite); // Draw the sprite instead of the shape
    }

    bool hasScored() const
    {
        return scored;
    }

    void setScored(bool value)
    {
        scored = value;
    }
};

vector<Texture> coinTextures;

// Load textures function
void loadCoinTextures()
{
    Texture texture;
    if (texture.loadFromFile("../Assets/Objects/coin.png")) // Adjust path if needed
    {
        coinTextures.push_back(texture);
    }
    else
    {
        // std::cout << "Error loading texture" << std::endl;
    }
}

class Coin
{
public:
    sf::RectangleShape hitbox;
    sf::Vector2f position;
    sf::Sprite sprite;
    float speed;
    bool hasCollided = false;
    int opacity = sprite.getColor().a;

    // Constructor
    Coin(sf::RenderWindow &window, vector<Obstacle> &obstacles)
    {
        if (!coinTextures.empty())
        {
            sprite.setTexture(coinTextures[0]); // Use the globally loaded texture
        }
        // set a y position that doesn't overlap with obstacles
        position = sf::Vector2f(window.getSize().x, rand() % window.getSize().y);
        for (Obstacle &obstacle : obstacles)
        {
            while (position.y > obstacle.getPosition().y - 100 && position.y < obstacle.getPosition().y + 100 || position.y > window.getSize().y - 100)
            {
                position = sf::Vector2f(window.getSize().x, rand() % window.getSize().y);
            }
        }

        // set sprite scale and position
        sprite.setScale(0.08f, 0.08f);
        sprite.setPosition(position);
        // set hitbox size and position
        hitbox.setSize(sf::Vector2f(60, 60));
        hitbox.setPosition(position);
    }

    // Method to update the coin's position
    void move(float offsetX, float offsetY)
    {
        position.x += offsetX;
        position.y += offsetY;
        sprite.setPosition(position);
        hitbox.setPosition(position);
    }

    // Method to get the coin's position
    sf::Vector2f getPosition() const
    {
        return position;
    }

    // Method to fade the coin by decreasing its opacity
    void fade()
    {
        if (opacity > 0)
        {
            opacity -= 40;
            sprite.setColor(sf::Color(255, 255, 255, opacity));
        }
    }
    
    void update()
    {
        position.x -= speed;
        sprite.setPosition(position);
        hitbox.setPosition(position);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }
};

#endif
