#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define COLOR_DEPTH 32
#define SPEED 5
#define HITBOX_RADIUS 40
#define SPEED_UP_MAX 7
#define PROPULSION_STRENGHT 2.1f
#define PROPULSION_SMOOTHER 1.0f
#define GRAVITY_STRENGHT 0.6f
#define GRAVITY_SMOOTHER 0.01f
#define OBSTACLE_WIDTH 50
#define OBSTACLE_COLOR sf::Color::Red
#define INITIAL_Y_POS 450
#define RUNNER_X_POS 200

#include "gameOver.hpp"
#include <vector>
#include "Character.hpp"
#include "score.hpp"


int main()
{

    Runner player("../Assets/Character/NightBorne.png", sf::Vector2f(RUNNER_X_POS, window.getSize().y-HITBOX_RADIUS*2-INITIAL_Y_POS));
    // {"../Assets/Character/NightBorne.png", Vector2f(00, 00)};
    // Character obstacle{"../Assets/Character/NightBorne.png", Vector2f(00, 00)};

    std::vector<Obstacle> obstacles;
    Score score(window);

    // INIT
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(60);
    int speed = SPEED; // number of pixels per frame
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

    // MAIN LOOP
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        // BACKGROUND INIT
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
                score.increment();
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
                score.draw(window);
                while (true)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                    {
                        // window.close();
                        main();
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    {
                        window.close();
                        exit(0);
                    }
                }
            }
        }

        player.update();
        player.draw();

        for (auto &obstacle : obstacles)
        {
            obstacle.draw();
        }

        score.draw(window);
        window.display();
    }
    return 0;
}