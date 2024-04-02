#ifndef _OVER_
#define _OVER_
#include "Character.hpp"
#include "score.hpp"

class GameOver
{
    sf::Texture texture;
    sf::Sprite gameOver;
    sf::Font font;
    sf::Text scoreText;

public:
    GameOver(sf::RenderWindow &window, int finalScore)
    {
        texture.loadFromFile("../Assets/Backgrounds/exit.png");
        gameOver.setTexture(texture);
        //set scale
        float scale_x = window.getSize().x / gameOver.getLocalBounds().width;
        float scale_y = window.getSize().y / gameOver.getLocalBounds().height;
        gameOver.setScale(scale_x, scale_y);

        // Set the position
        float pos_x = (window.getSize().x - gameOver.getLocalBounds().width * scale_x) / 2;
        float pos_y = (window.getSize().y - gameOver.getLocalBounds().height * scale_y) / 2;
        gameOver.setPosition(pos_x, pos_y);
        if (!font.loadFromFile("Arial font/arial_light.ttf")) // Make sure the path to your font is correct
        {
            // Handle error
           //std::cout << "Error loading font" << std::endl;
        }

        // Set up the score text
        scoreText.setFont(font);
        scoreText.setString("SCORE: "+ std::to_string(finalScore)); // Convert the score to string and set it
        scoreText.setCharacterSize(100); // Example character size
        scoreText.setFillColor(sf::Color::White); // Example color
        scoreText.setPosition(window.getSize().x / 2 - scoreText.getLocalBounds().width / 2, window.getSize().y / 3 - scoreText.getLocalBounds().height / 2);
    }

    void drawGameOver(sf::RenderWindow &window)
    {
        window.draw(gameOver);
        window.draw(scoreText);
    }
};

bool collisionWithObstacles(Runner player, Obstacle obstacle, sf::RenderWindow &window)
{
    if (player.hitbox.getGlobalBounds().intersects(obstacle.shape.getGlobalBounds()))
    {
        return true;
    }
    return false;
}

class Menu
{
    sf::Texture texture;
    sf::Sprite menu;

public:
    Menu(sf::RenderWindow &window)
    {
        texture.loadFromFile("../Assets/Backgrounds/menu.png");
        menu.setTexture(texture);
        menu.setScale(window.getSize().x / menu.getLocalBounds().width, window.getSize().y / menu.getLocalBounds().height);
    }

    void drawMenu(sf::RenderWindow &window)
    {
        window.draw(menu);
    }
};

#endif