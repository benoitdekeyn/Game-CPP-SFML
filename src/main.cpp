#include "definitions.hpp"

int main()
{
    //------------------ INITIALIZATIONS ------------------
    loadObstacleTextures();
    loadCoinTextures();

    //---------- WINDOW ----------
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(FPS);
    int window_width = window.getSize().x;
    int window_height = window.getSize().y;

    //-------- BACKGROUND --------
    Background background(window);

    //----------- MENU -----------
    Menu menu(window);
    // bool menuOn = true;

    //---------- PLAYER ----------
    Runner player(sf::Vector2f(RUNNER_X_POS, window.getSize().y - INITIAL_Y_POS), window);

    //--------- ANIMATION --------
    Animation runAnim(player.sprite);
    Animation jumpAnim(player.sprite);
    Animation fallAnim(player.sprite);
    Animation deathAnim(player.sprite);

    addRunFrames(&runAnim);
    addJumpFrames(&jumpAnim);
    addFallFrames(&fallAnim);
    addDeathFrames(&deathAnim);

    Animation animations[3] = {runAnim, jumpAnim, fallAnim};
    //--------- OBSTACLES --------
    std::vector<Obstacle> obstacles;

    //----------- COINS -----------
    std::vector<Coin> coins;

    //---------- SCORE -----------
    Score score(window);

    //---------- CLOCK -----------
    sf::Clock clock;      // Start a timer
    sf::Clock animClock;  // Timer for animations
    sf::Clock deathClock; // Timer for the death animation

    //---------- MUSIC -----------
    GameMusic music;

    //--------------------- MAIN LOOP ---------------------
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                exit(0);
                window.close();
            }
        }

        while (menuOn == true)
        {
            menu.draw(window);
            window.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                menuOn = false;
                
                break;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                exit(0);
                window.close();
            }
        }

        
        //UPDATE BACKGROUND and speed and music
        background.update(window, music);
        

        if (death)
        {
            // obstacles.clear();
            if (!animationStarted)
            {
                deathAnim.progress = 0.0;
                animationStarted = true;
                auto elapsed = deathClock.restart();
            }
            else
            {
                auto elapsed = animClock.restart();
                deathAnim.update(elapsed.asSeconds());
            }
            if (animationStarted && deathClock.getElapsedTime().asSeconds() >= 2.3)
            {
                int sco = score.getScore();
                background.reset(window);
                speedReset();
                GameOver gameOver(window, sco);
                gameOver.drawGameOver(window);
                window.display();
                score.draw(window);
                sf::Event event;
                while (window.waitEvent(event))
                {

                    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
                    {
                        death = false;
                        animationStarted = false;
                        music.stop();
                        main();
                    }
                    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::M))
                    {
                        Menu menu(window);
                        menu.draw(window);
                        window.display();
                        music.playMenu();
                        sf::Event secondEvent;
                        while (window.waitEvent(secondEvent))
                        {
                            if ((secondEvent.type == sf::Event::KeyPressed) && (secondEvent.key.code == sf::Keyboard::Enter))
                            {
                                death = false;
                                animationStarted = false;
                                music.stop();
                                main();
                            }
                            if ((secondEvent.type == sf::Event::KeyPressed) && (secondEvent.key.code == sf::Keyboard::Escape))
                            {
                                exit(0);
                                window.close();
                            }
                        }
                    }
                    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                    {
                        exit(0);
                        window.close();
                    }
                }
            }
        }
        
        if (clock.getElapsedTime().asSeconds() > OBSTACLE_INTERVAL && !death)
        {
            // push a new obstacle to the array
            obstacles.push_back(Obstacle(window));

            // push a new coin to the array
			coins.push_back(Coin(window, obstacles));

            clock.restart();
        }

        // move obstacles
        if (!obstacles.empty())
        {
            for (vector<Obstacle>::iterator itr = obstacles.begin(); itr != obstacles.end(); itr++)
            {
                (*itr).move(-3, 0);
            }
        }

        // move coins
		if (!coins.empty()) 
        {
			for (vector<Coin>::iterator itr = coins.begin(); itr != coins.end(); itr++) 
            {
				(*itr).move(-3, 0);
			}
		}


        // remove obstacles if offscreen
        if (!obstacles.empty() && obstacles.front().getPosition().x < -104)
        {
            vector<Obstacle>::iterator startitr = obstacles.begin();
            vector<Obstacle>::iterator enditr = obstacles.begin();

            for (; enditr != obstacles.end(); enditr++)
            {
                if ((*enditr).getPosition().x > -104)
                {
                    break;
                }
            }

            obstacles.erase(startitr, enditr);
        }

        // remove coins if offscreen
        if (!coins.empty() && coins.front().getPosition().x < -104) 
        {
			vector<Coin>::iterator startitr = coins.begin();
			vector<Coin>::iterator enditr = coins.begin();

			for (; enditr != coins.end(); enditr++) 
            {
				if ((*enditr).getPosition().x > -104) 
                {
					break;
				}
			}

			coins.erase(startitr, enditr);
		}

        // Check for collisions and increment score
        for (vector<Obstacle>::iterator itr = obstacles.begin(); itr != obstacles.end(); itr++)
        {
            // Check if obstacle has passed the player without collision
            if ((*itr).hitbox.getPosition().x + OBSTACLE_WIDTH < player.hitbox.getPosition().x && !(*itr).hasScored())
            {
                // score.increment();
                (*itr).setScored(true);
            }

            // Check for collision with player
            if (collisionWithObstacles(player, *itr, window))
            {
                death = true;
                music.stop();
                break;
            }
        }

        // Check for coin collisions
        for (vector<Coin>::iterator itr = coins.begin(); itr != coins.end(); itr++) 
        {
            if (collisionsWithCoins(player, *itr, window)) 
            {
                score.increment();
                coins.erase(itr);
                break;
            }
        }

        // draw obstacles
        for (vector<Obstacle>::iterator itr = obstacles.begin(); itr != obstacles.end(); itr++) {
			// draw with the function from the class
            (*itr).draw(window);
		}

        // draw coins
        for (vector<Coin>::iterator itr = coins.begin(); itr != coins.end(); itr++) {
			// draw with the function from the class
            (*itr).draw(window);
		}

        //-------------------- ANIMATION UPDATE  --------------------
        if (!death)
        {
            player.update(window);
            auto elapsed = animClock.restart();
            animationUpdate(elapsed.asSeconds(), player, window, animations);
        }
        //------------------ END ANIMATION UPDATE  ------------------
        player.draw(window);

        score.draw(window);
        window.display();
    }
    return 0;
}