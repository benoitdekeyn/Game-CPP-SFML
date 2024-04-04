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
    bool menuOn = true;

    //---------- PLAYER ----------
    Runner player(sf::Vector2f(RUNNER_X_POS, window.getSize().y - INITIAL_Y_POS), window);

    //--------- ANIMATION --------
    Animation jumpAnim(player.sprite);
    Animation runAnim(player.sprite);
    Animation fallAnim(player.sprite);
    Animation deathAnim(player.sprite);

    addRunFrames(&runAnim);
    addJumpFrames(&jumpAnim);
    addFallFrames(&fallAnim);
    addDeathFrames(&deathAnim);

    //--------- OBSTACLES --------
    std::vector<Obstacle> obstacles;

    //---------- SCORE -----------
    Score score(window);

    //---------- CLOCK -----------
    sf::Clock clock; // Start a timer
    sf::Clock animClock;
    
     //---------- MUSIC -----------
    GameMusic music;
    
    
    //--------------------- MAIN LOOP ---------------------
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)){
                exit(0);
                window.close();
                
            }
        }
        if (menuOn == true){music.playMenu();}
        while(menuOn == true){
            
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
                int sco = score.getScore();
                background.reset(window);
                speedReset();
                GameOver gameOver(window, sco);
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
                        menu.draw(window);
                        window.display();
                        //music.playMenu();
                        while (true)
                        {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                            {
                                main();
                            }
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                            {
                                exit(0);
                                window.close();
                            }
                        }
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    {
                        exit(0);
                        window.close();
                    }
                }
            }
        }

        player.update(window);
        

        //-------------------- ANIMATION UPDATE  --------------------
        auto elapsed = animClock.restart();
        runAnim.update(elapsed.asSeconds());
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
