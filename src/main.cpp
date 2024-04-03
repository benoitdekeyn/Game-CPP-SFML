#include "definitions.hpp"

int main()
{
    // INTIALIZE WINDOW
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_DEPTH), "SFML works!");
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(FPS);
    int window_width = window.getSize().x;
    int window_height = window.getSize().y;

    // INITIALIZE BACKGROUND
    Background background("../Assets/Backgrounds/background.png", window);
    Background menu("../Assets/Backgrounds/menunew.png", window);

    // INITIALIZE PLAYER
    Runner player(sf::Vector2f(RUNNER_X_POS, window.getSize().y - INITIAL_Y_POS), window);

    //-------------------- ANIMATION SETUP --------------------
    // Create animations
    Animation jumpAnim(player.sprite);
    Animation runAnim(player.sprite);
    Animation fallAnim(player.sprite);
    Animation deathAnim(player.sprite);

    addRunFrames(&runAnim);
    addJumpFrames(&jumpAnim);
    addFallFrames(&fallAnim);
    addDeathFrames(&deathAnim);
    //----------------- END ANIMATION SETUP  ------------------

    // INITIALIZE OBSTACLES
    std::vector<Obstacle> obstacles;
    Score score(window);

    bool menuOn = true;

    sf::Clock clock; // Start a timer

    // // MAIN LOOP
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        while (menuOn == true)
        {
            menu.drawBackground(window);
            window.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                menuOn = false;
                break;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
                exit(0);
            }
        }

        // UPDATE SPEED
        speedUp();

        // UPDATE BACKGROUND
        background.updateBackground(window);
        window.clear();
        background.drawBackground(window);

        if (clock.getElapsedTime().asSeconds() > OBSTACLE_INTERVAL)
        {
            obstacles.push_back(Obstacle(window));
            clock.restart();
        }

        for (auto it = obstacles.begin(); it != obstacles.end();)
        {
            it->update(window);
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
                        main();
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                    {
                        Menu menu(window);
                        menu.drawMenu(window);
                        window.display();
                        while (true)
                        {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                            {
                                main();
                            }
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                            {
                                window.close();
                                exit(0);
                            }
                        }
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    {
                        window.close();
                        exit(0);
                    }
                }
            }
        }

        player.update(window);
        player.draw(window);

        //-------------------- ANIMATION UPDATE  --------------------
        auto elapsed = clock.restart();
        runAnim.update(elapsed.asSeconds());
        //------------------ END ANIMATION UPDATE  ------------------

        for (auto &obstacle : obstacles)
        {
            obstacle.draw(window);
        }

        score.draw(window);
        window.display();
    }
    return 0;
}
