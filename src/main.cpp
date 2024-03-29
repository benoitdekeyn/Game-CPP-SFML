#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define COLOR_DEPTH 32
#define FPS 60

#define SPEED 5


#define INITIAL_Y_POS 450
#define RUNNER_X_POS 200
#define TOP_OFFSET 3
#define BOTTOM_OFFSET -2

#define HITBOX_WIDTH 55
#define HITBOX_HEIGHT 60
#define HITBOX_OFFSET sf::Vector2f(40, 6)

#define SPEED_UP_MAX 7
#define PROPULSION_STRENGHT 2.1f
#define PROPULSION_SMOOTHER 1.0f
#define GRAVITY_STRENGHT 0.6f
#define GRAVITY_SMOOTHER 0.01f

#define OBSTACLE_WIDTH 50
#define OBSTACLE_COLOR sf::Color::Red
#define OBSTACLE_INTERVAL 0.5f

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

using namespace sf;
using namespace std;

#include "background.hpp"
#include "gameOver.hpp"
#include "Character.hpp"
#include "score.hpp"



int main()
{
    //INTIALIZE WINDOW
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_DEPTH), "SFML works!");   
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(FPS);
    int window_width = window.getSize().x;
    int window_height = window.getSize().y;

    //INITIALIZE BACKGROUND
    Background background("../Assets/Backgrounds/background.png",window);

    //INITIALIZE PLAYER
    Runner player("../Assets/Character/NightBorne.png", sf::Vector2f(RUNNER_X_POS, window.getSize().y-INITIAL_Y_POS), window);
    
    //INITIALIZE OBSTACLES
    std::vector<Obstacle> obstacles;
    Score score(window);

    sf::Clock clock;               // Start a timer


    // MAIN LOOP
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

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
                        // window.close();
                        main();
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                    {
                        // window.close();
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

        for (auto &obstacle : obstacles)
        {
            obstacle.draw(window);
        }

        score.draw(window);
        window.display();
    }
    return 0;
}