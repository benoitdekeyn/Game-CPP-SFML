#include "definitions.hpp"

int main()
{
    //------------------ INITIALIZATIONS ------------------

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
            obstacles.clear();
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
            if (animationStarted && deathClock.getElapsedTime().asSeconds() >= 3.23)
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
                        while (true)
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
            //obstacles.push_back(Obstacle(window));
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
                death = true;
            }
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

        for (auto &obstacle : obstacles)
        {
            obstacle.draw(window);
        }

        score.draw(window);
        window.display();
    }
    return 0;
}
