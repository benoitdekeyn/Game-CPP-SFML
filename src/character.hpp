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

vector<Texture> obstacleTextures;

// Load obstacle textures function
void loadObstacleTextures()
{
    Texture texture;
    if (texture.loadFromFile("../Assets/Objects/obstacle.png")) // Adjust path if needed
    {
        obstacleTextures.push_back(texture);
    }
    else
    {
        // std::cout << "Error loading texture" << std::endl;
    }
}

// OBSTACLES
class Obstacle {
public:
    sf::RectangleShape hitbox;
    sf::Vector2f position;
    sf::Sprite sprite; // Use sf::Sprite instead of sf::RectangleShape
    float speed;
    bool scored;

    Obstacle(sf::RenderWindow &window)
    {
        if(!obstacleTextures.empty()) {
            sprite.setTexture(obstacleTextures[0]); // Use the globally loaded texture
        }
        position = sf::Vector2f(window.getSize().x, rand() % window.getSize().y);

        // set sprite scale and position
        sprite.setScale(0.15f, 0.15f);
        sprite.setPosition(position);

        // set hitbox size and position
        hitbox.setSize(sf::Vector2f(60, 60));
        hitbox.setPosition(position);
        hitbox.setFillColor(sf::Color::Red);
    }

    void move(float offsetX, float offsetY)
    {
        position.x += offsetX;
        position.y += offsetY;
        sprite.setPosition(position);
        hitbox.setPosition(position);
    }

    sf::Vector2f getPosition()
    {
        return position;
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
        // window.draw(hitbox);
    }

    bool hasScored() const {
        return scored;
    }

    void setScored(bool value) {
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

class Coin {
public:

    sf::RectangleShape hitbox;
    sf::Vector2f position;
    sf::Sprite sprite;
    float speed;
    // Constructor
    Coin(sf::RenderWindow& window) {
        if(!coinTextures.empty()) {
            sprite.setTexture(coinTextures[0]); // Use the globally loaded texture
        }
        position = sf::Vector2f(window.getSize().x, rand() % window.getSize().y);
        // set sprite scale and position
        sprite.setScale(0.08f, 0.08f);
        sprite.setPosition(position);
    }


    // Method to update the coin's position
    void move(float offsetX, float offsetY)
    {
        position.x += offsetX;
        position.y += offsetY;
        sprite.setPosition(position);
        // hitbox.setPosition(position);
    }

    // Method to get the coin's position
    sf::Vector2f getPosition() const
    {
        return position;
    }
    
    void update()
    {
        position.x -= speed;
        sprite.setPosition(position);
        // hitbox.setPosition(position);
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
        // window.draw(hitbox);
    }
};

#endif
