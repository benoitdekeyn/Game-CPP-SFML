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

#define OBJECT_WIDTH 50
#define OBSTACLE_INTERVAL 0.5f

#define OBSTACLE_COLOR sf::Color::Red
#define COIN_COLOR sf::Color::Yellow

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

using namespace sf;
using namespace std;

#include "background.hpp"
#include "gameOver.hpp"
#include "character.hpp"
#include "score.hpp"

//INTIALIZE WINDOW
void initializeWindow(sf::RenderWindow& window)
{
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_DEPTH), "SFML works!");
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(FPS);
    int window_width = window.getSize().x;
    int window_height = window.getSize().y;
}

void handleWindowEvent(sf::RenderWindow& window, sf::Event& event)
{
    if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        window.close();
}

int main()
{
    int i = 0;
    sf::RenderWindow window;
    initializeWindow(window);

    //INITIALIZE BACKGROUND
    Background background("../Assets/Backgrounds/background.png",window);

    //INITIALIZE PLAYER
    Runner player("../Assets/Character/NightBorne.png", sf::Vector2f(RUNNER_X_POS, window.getSize().y-INITIAL_Y_POS), window);
    
    //INITIALIZE OBSTACLES
    vector<Obstacle> obstacles;
    // obstacles.reserve(100);

    //INITIALIZE SCORE
    Score score(window);

    //INITIALIZE COINS
    // std::vector<Coin> coins;

    // Start a timer
    sf::Clock clock;


    // MAIN LOOP
    // In the main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            handleWindowEvent(window, event); // Close the window if ESC is pressed
        }

        background.updateBackground(window);
        window.clear();
        background.drawBackground(window);

        // generate obstacles and push them to the array
        if (clock.getElapsedTime().asSeconds() > OBSTACLE_INTERVAL) {
			int r = rand() % 275 + 75;
			int gap = 150;

            Obstacle obstacle(window);
			
            if (!obstacle.texture.loadFromFile("../Assets/coin.png")) 
            {
                std::cout << "Error loading texture" << std::endl;
            }
			obstacle.sprite.setTexture(obstacle.texture);
			obstacle.sprite.setPosition(obstacle.position);
			obstacle.sprite.setScale(0.1f, 0.1f);

			// push to the array
			obstacles.push_back(obstacle);
		}

		// move obstacles
		if (!obstacles.empty()) {
			for (vector<Obstacle>::iterator itr = obstacles.begin(); itr != obstacles.end(); itr++) {
				(*itr).move(-3, 0);
			}
		}

		// remove obstacles if offscreen
		if (!obstacles.empty() && obstacles.front().getPosition().x < -104) {
			vector<Obstacle>::iterator startitr = obstacles.begin();
			vector<Obstacle>::iterator enditr = obstacles.begin();

			for (; enditr != obstacles.end(); enditr++) {
				if ((*enditr).getPosition().x > -104) {
					break;
				}
			}

			obstacles.erase(startitr, enditr);
		}

        for (vector<Obstacle>::iterator itr = obstacles.begin(); itr != obstacles.end(); itr++) {
			window.draw((*itr).sprite);
		}

        // if (rand() % 100 == 0)
        // {
        //     coins.push_back(Coin(window, "../Assets/Character/NightBorne.png"));
        // }

        // if (clock.getElapsedTime().asSeconds() > OBSTACLE_INTERVAL)
        // {
        //     Obstacle obstacle(window);
        //     obstacle.texture.loadFromFile("../Assets/coin.png");
        //     obstacle.sprite.setTexture(obstacle.texture);
        //     obstacle.sprite.setScale(0.1f, 0.1f);
        //     obstacles.push_back(obstacle);
        //     clock.restart();
        //     //std::cout<<"maaaa biteee" << std::endl;
        // }

        // for (auto it = obstacles.begin(); it != obstacles.end();)
        // {
        //     std::cout<<"maaaa biteee" << std::endl;

        //     it->update(); // Update each obstacle
        //     if (it->position.x + it->sprite.getGlobalBounds().width < 0)
        //     {
        //         it = obstacles.erase(it); // Remove obstacle if it goes off the screen
        //     }
        //     else
        //     {
        //         ++it;
        //     }
        // }

        // for (auto it = coins.begin(); it != coins.end();)
        // {
        //     it->update(window);
        //     if (it->position.x + it->shape.getSize().x < 0)
        //     {
        //         it = coins.erase(it);
        //     }
        //     else
        //     {
        //         ++it;
        //     }
        // }

        // for (auto &obstacle : obstacles)
        // {
        //     if (collisionWithObstacles(player, obstacle, window))
        //     {
        //         GameOver gameOver(window);
        //         gameOver.drawGameOver(window);
        //         window.display();
        //         score.draw(window);
        //         while (true)
        //         {
        //             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        //             {
        //                 // window.close();
        //                 main();
        //             }
        //             if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        //             {
        //                 // window.close();
        //                 Menu menu(window);
        //                 menu.drawMenu(window);
        //                 window.display();
        //                 while (true)
        //                 {
        //                     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        //                     {
        //                         main();
        //                     }
        //                     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        //                     {
        //                         window.close();
        //                         exit(0);
        //                     }
        //                 }
        //             }
        //             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        //             {
        //                 window.close();
        //                 exit(0);
        //             }
        //         }
        //     }
        // }

        player.update(window);
        player.draw(window);

        // if (!obstacles.empty()) {
        //    // obstacles[i].draw(window);
        //     std::cout << "i = " << i << std::endl;
        //     i++;
        // }

        // for (auto& coin : coins)
        // {
        //     coin.draw(window); // Draw coins
        // }

        score.draw(window);
        window.display();
    }

    return 0;
}