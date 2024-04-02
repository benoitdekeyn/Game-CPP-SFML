#include "gameOver.hpp"
#include <vector>
#include "Character.hpp"
#include "Animation.hpp"
int main()
{

    Runner player(sf::Vector2f(100, 830));

    //-------------------- ANIMATION SETUP --------------------

    // Create animations
    Animation jumpAnim(player.sprite);
    Animation runAnim(player.sprite);
    Animation fallAnim(player.sprite);
    Animation deathAnim(player.sprite);

    // Add frames to the running animation
    runAnim.addFrame({sf::IntRect(0, 0, 66, 66), 0.06});
    runAnim.addFrame({sf::IntRect(80, 0, 66, 66), 0.06});
    runAnim.addFrame({sf::IntRect(160, 0, 66, 66), 0.06});
    runAnim.addFrame({sf::IntRect(240, 0, 66, 66), 0.06});
    runAnim.addFrame({sf::IntRect(320, 0, 66, 66), 0.06});
    runAnim.addFrame({sf::IntRect(400, 0, 66, 66), 0.06});

    // Add frames to the jumping animation
    jumpAnim.addFrame({sf::IntRect(0, 50, 66, 66), 0.1});
    jumpAnim.addFrame({sf::IntRect(80, 50, 66, 66), 0.2});
    jumpAnim.addFrame({sf::IntRect(0, 50, 66, 66), 0.2});
    jumpAnim.addFrame({sf::IntRect(80, 50, 66, 66), 0.1});

    // Add frames to the fall animation
    fallAnim.addFrame({sf::IntRect(160, 142, 66, 66), 0.1});

    // Add frames to the death animation
    deathAnim.addFrame({sf::IntRect(0, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(80, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(160, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(240, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(320, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(400, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(480, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(560, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(640, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(720, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(800, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(880, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(950, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(1030, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(1110, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(1190, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(1270, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(1350, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(1430, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(1520, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(1600, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(1680, 142, 66, 66), 0.1});
    deathAnim.addFrame({sf::IntRect(1760, 142, 66, 66), 0.1});
    //-------------------- END ANIMATION  --------------------

    std::vector<Obstacle> obstacles;

    // INIT
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(60);
    int speed = 5; // number of pixels per frame
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../Assets/Backgrounds/background.png");
    sf::Sprite background1(backgroundTexture);
    sf::Sprite background2(backgroundTexture);
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    background1.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);
    background2.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);
    background2.setPosition(windowSize.x, 0);
    int x_width_window = windowSize.x;

    sf::Clock clock;               // Start a timer
    float obstacleInterval = 0.5f; // Time in seconds between obstacles

    // // MAIN LOOP
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        //     // BACKGROUND INIT
        background1.move(-speed, 0);
        background2.move(-speed, 0);
        if (background1.getPosition().x <= -x_width_window)
        {
            background1.setPosition(x_width_window, 0);
        }
        if (background2.getPosition().x <= -x_width_window)
        {
            background2.setPosition(x_width_window, 0);
        }
        window.clear();
        window.draw(background1);
        window.draw(background2);

        if (clock.getElapsedTime().asSeconds() > obstacleInterval)
        {
            obstacles.push_back(Obstacle());
            clock.restart();
        }

        for (auto it = obstacles.begin(); it != obstacles.end();)
        {
            it->update();
            if (it->position.x + it->shape.getSize().x < 0)
            {
                it = obstacles.erase(it);
            }
            else
            {
                ++it;
            }
        }

        for (auto &obstacle : obstacles)
        {
            if (collisionWithObstacles(player, obstacle, window))
            {
                GameOver gameOver(window);
                gameOver.drawGameOver(window);
                window.display();
                sf::sleep(sf::seconds(2));
                window.close();
            }
        }

        player.update();

        // Insert conditions for the animations here (in a function)
        sf::Time elapsed = clock.restart();
        fallAnim.update(elapsed.asSeconds());

        player.draw();

        for (auto &obstacle : obstacles)
        {
            obstacle.draw();
        }

        window.display();
    }
    return 0;
}
