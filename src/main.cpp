#include "gameOver.hpp"
#include <vector>
#include "Character.hpp"

int main()
{

    Runner player("../Assets/Character/NightBorne.png", sf::Vector2f(0, 830));
    // {"../Assets/Character/NightBorne.png", Vector2f(00, 00)};
    // Character obstacle{"../Assets/Character/NightBorne.png", Vector2f(00, 00)};

    std::vector<Obstacle> obstacles;

    // INIT
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(60);
    int speed = 5; // number of pixels per frame
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("data/backgrounds/background.png");
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
            player.draw();

            for (auto &obstacle : obstacles)
            {
                obstacle.draw();
            }

            window.display();
        }
        return 0;
    }
}